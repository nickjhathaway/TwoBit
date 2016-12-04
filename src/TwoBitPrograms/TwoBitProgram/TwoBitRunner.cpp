
    
#include "TwoBitRunner.hpp"
#include <iostream>
#include <exception>
#include <cppitertools/range.hpp>
#include "TwoBit/objects/TwoBitSequence.hpp"
#include "TwoBit/IO.h"
#include "TwoBitSetUp.hpp"
namespace TwoBit {

TwoBitRunner::TwoBitRunner()
    : bib::progutils::programRunner ({
	addFunc("twoBitToFa", twoBitToFa, false),
  addFunc("faToTwoBit", faToTwoBit, false)},
                    "TwoBit",  "3", "0", "0-dev") {}

int TwoBitRunner::twoBitToFa(const bib::progutils::CmdArgs & inputCommands){
	TwoBitSetUp setUp(inputCommands);
	std::string inputFilename = "";
	uint32_t width = 80;
	std::string outFilename = "";
	bool overWrite = false;
	setUp.setOption(inputFilename, "--in,-i", "Input 2bit filename",true );
	setUp.setOption(width, "--width,-w", "Character Width for output fasta file");
	setUp.setOption(outFilename, "--out,-o", "Name of an output file, if left blank will default to stdout");
	setUp.setOption(overWrite, "--overWrite", "Whether to overwrite the file if one is given by --out");
	setUp.finishSetUp(std::cout);
	try {
		TwoBitFile f(inputFilename);
		std::string buffer;
		std::ofstream outfile;
		std::ostream out(bib::files::determineOutBuf(outfile,outFilename, ".fasta", overWrite, false, true));
		for (const std::string& s : f.sequenceNames()) {
			f[s].getSequence(buffer);
			out << ">" << s << std::endl;
			for (uint32_t i = 0; i < buffer.size(); i += width) {
				out << buffer.substr(i, width) << '\n';
			}
			out.flush();
		}
	} catch (std::exception& e) {
		throw;
	}
	return 0;
}


int TwoBitRunner::faToTwoBit(const bib::progutils::CmdArgs & inputCommands) {
	TwoBitSetUp setUp(inputCommands);
	std::string inputFilename = "";
	std::string outFilename = "";
	bool overWrite = false;
	bool leaveWhitespaceInName = false;
	setUp.setOption(inputFilename, "--in,-i", "Input fasta filename, can be several files seperated by commas", true);
	setUp.setOption(outFilename, "--out,-o",
			"Name of an output file", true);
	setUp.setOption(overWrite, "--overWrite",
			"Whether to overwrite the file if one is given by --out");
	setUp.setOption(overWrite, "--overWrite",
			"Whether to overwrite the file if one is given by --out");
	setUp.setOption(leaveWhitespaceInName, "--leaveWhitespaceInName",
				"Whether to trim the names of the fasta records at the first whitespace");
	setUp.finishSetUp(std::cout);
	bib::appendAsNeeded(outFilename, ".2bit");
	std::ofstream out;
	//check if output file exists
	if (!overWrite && bib::files::bfs::exists(outFilename)) {
		throw Exception(__PRETTY_FUNCTION__,
				"File " + outFilename
						+ " already exists, use --overWrite to over write");
	}
	//read in seqs
	std::vector<std::unique_ptr<FastaRecord>> seqs;
	auto toks = bib::tokenizeString(inputFilename, ",");
	for(const auto & fName : toks){
		std::ifstream in(fName);
		std::unique_ptr<FastaRecord> seq;
		while (readNextFasta(in, seq, !leaveWhitespaceInName)) {
			seqs.emplace_back(std::move(seq));
		}
	}
	out.open(outFilename, std::ios::binary | std::ios::out);
	//write out header
	twoBitWriteHeader(seqs, out);
	//write out sequences
	for (const auto & seq : seqs) {
		seq->twoBitWriteOne(out);
	}
	return 0;
}

                    
} // namespace bibseq
