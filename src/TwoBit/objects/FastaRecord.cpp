#include "FastaRecord.hpp"



namespace TwoBit {


std::vector<unsigned char> FastaRecord::data()const{
	std::vector<unsigned char> ret;
	ret.reserve(seq_.size()/4);
	uint32_t i;
	for(i = 0; i < seq_.size() - 4; i += 4){
		ret.push_back(packDna4(seq_, i));
	}
	std::string last('T',4);
	for(uint32_t j = 0; i < seq_.size(); ++j, ++i){
		last[j] = seq_[i];
	}
	ret.push_back(packDna4(last,0));
	return ret;
}


void FastaRecord::storeBlocksOfN() {
	nSizes_.clear();
	nStarts_.clear();
	bool isN, lastIsN = false;
	int startN = 0;
	for(auto pos : iter::range(seq_.size())){
		auto c = seq_[pos];
		isN = (c == 'n' || c == 'N');
		if (isN) {
			if (!lastIsN){
				startN = pos;
			}
		} else {
			if (lastIsN) {
				nStarts_.push_back(startN);
				nSizes_.push_back(pos - startN);
			}
		}
		lastIsN = isN;
	}
	if (lastIsN) {
		nStarts_.push_back(startN);
		nSizes_.push_back(seq_.size() - startN);
	}
}

void FastaRecord::storeBlocksOfLower() {
	bool isLower, lastIsLower = false;
	int startLower = 0;
	for(auto pos : iter::range(seq_.size())){
		isLower = islower(seq_[pos]);
		if (isLower) {
			if (!lastIsLower){
				startLower = pos;
			}
		} else {
			if (lastIsLower) {
				maskStarts_.push_back(startLower);
				maskSizes_.push_back(pos - startLower);
			}
		}
		lastIsLower = isLower;
	}
	if (lastIsLower) {
		maskStarts_.push_back(startLower);
		maskSizes_.push_back(seq_.size() - startLower);
	}
}

int FastaRecord::twoBitSizeInFile()const{
	int ret = packedSize(seq_.size());
	ret += sizeof(uint32_t); //size of seq
	ret += sizeof(uint32_t); //number of n blocks
	ret += sizeof(uint32_t) * nStarts_.size(); // for starts of n blocks
	ret += sizeof(uint32_t) * nStarts_.size(); // for sizes of n blocks
	ret += sizeof(uint32_t); //number of mask blocks
	ret += sizeof(uint32_t) * maskStarts_.size(); // for starts of mask blocks
	ret += sizeof(uint32_t) * maskStarts_.size(); // for sizes of mask blocks
	ret += sizeof(uint32_t); //for reserved
	return ret;
}


void FastaRecord::twoBitWriteOne(std::ofstream & out) const {
	writeData(out, static_cast<uint32_t>(seq_.size()));
	writeData(out, static_cast<uint32_t>(nStarts_.size()));
	if (nStarts_.size() > 0) {
		writeDataVec(out, nStarts_);
		writeDataVec(out, nSizes_);
	}
	writeData(out, static_cast<uint32_t>(maskStarts_.size()));
	if (maskStarts_.size() > 0) {
		writeDataVec(out, maskStarts_);
		writeDataVec(out, maskSizes_);
	}
	writeData(out, reserved_);
	writeDataVec(out, data(), packedSize(seq_.size()));
}

}  // namespace TwoBit
