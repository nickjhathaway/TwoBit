

#include "TwoBitOut.hpp"
#include <sstream>
#include <string.h>
#include <cstdint>
#include <limits>


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

}  // namespace TwoBit
