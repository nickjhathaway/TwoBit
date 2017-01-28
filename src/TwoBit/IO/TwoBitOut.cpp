

#include "TwoBitOut.hpp"
#include <sstream>
#include <string.h>
#include <cstdint>
#include <limits>
#include <bibcpp.h>
#include "TwoBit/err/Exception.hpp"
#include "TwoBit/IO/fasta.hpp"

namespace TwoBit {

void twoBitWriteHeader(const std::vector<std::unique_ptr<FastaRecord>> & seqs, std::ofstream & out){
	unsigned sig = twoBitSig;
	unsigned version = 0;
	unsigned seqCount = seqs.size();
	unsigned reserved = 0;
	unsigned offset = 0;
	long long counter = 0; /* check for 32 bit overflow */

	/* Write out fixed parts of header. */
	writeData(out, sig);
	writeData(out, version);
	writeData(out, seqCount);
	writeData(out, reserved);

	/* Figure out location of first byte past index.
	 * Each index entry contains 4 bytes of offset information
	 * and the name of the sequence, which is variable length. */

	offset = sizeof(sig) + sizeof(version) + sizeof(seqCount) + sizeof(reserved);
	for(const auto & seq : seqs){
		int nameLen = strlen(seq->name_.c_str());
		if(nameLen > 255){
			throw std::runtime_error{"name " + seq->name_ + " is too long"};
		}
		offset += nameLen + 1 + sizeof(unsigned);
	}
	for(const auto & seq : seqs){
		int size = seq->twoBitSizeInFile();
		writeString(out, seq->name_);
		writeData(out, offset);
		offset += size;
		counter += static_cast<long long>(size);
		if(counter > std::numeric_limits<uint32_t>::max()){
			std::stringstream ss;
			ss << "Error in faToTwoBit, index overflow at " << seq->name_ << ". The 2bit format "
					"does not support indexes larger than " << std::numeric_limits<uint32_t>::max() / 1000000000<< "Gb, \n"
					"please split up into smaller files.\n";
			throw std::runtime_error{ss.str()};
		}
	}
}

void fastasToTwoBit(const faToTwoBitPars & pars){
	std::string outName = bib::appendAsNeededRet(pars.outFilename, ".2bit");

	std::ofstream out;
	//check if output file exists
	if (!pars.overWrite && bfs::exists(outName)) {
		throw Exception(__PRETTY_FUNCTION__,
				"File " + outName
						+ " already exists, use --overWrite to over write");
	}
	//read in seqs
	//input file name can be multiple files to combine into one 2bit, should be comma separated
	std::vector<std::unique_ptr<FastaRecord>> seqs;
	auto toks = bib::tokenizeString(pars.inputFilename, ",");
	for(const auto & fName : toks){
		if(!bfs::exists(fName)){
			std::stringstream ss;
			ss << __PRETTY_FUNCTION__ << ", Error input file name " << fName << " doesn't exist" << std::endl;
			throw std::runtime_error{ss.str()};
		}
		std::ifstream in(fName);
		std::unique_ptr<FastaRecord> seq;
		while (readNextFasta(in, seq, !pars.leaveWhitespaceInName)) {
			seqs.emplace_back(std::move(seq));
		}
	}
	out.open(outName, std::ios::binary | std::ios::out);
	//write out header
	twoBitWriteHeader(seqs, out);
	//write out sequences
	for (const auto & seq : seqs) {
		seq->twoBitWriteOne(out);
	}
}

}  // namespace TwoBit
