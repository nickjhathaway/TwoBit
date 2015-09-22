

#include "fasta.hpp"

namespace TwoBit {




bool readNextFasta(std::istream & in, std::unique_ptr<FastaRecord> & seq) {
	if (!in.good()) {
		return false;
	}
	std::string name = "";
	std::string buildingSeq = "";
	std::string line = "";
	if (in.peek() == '>') {
		std::getline(in, name);
		while (in.peek() != std::ifstream::eofbit && in.good() && in.peek() != '>') {
			std::getline(in, line);
			buildingSeq.append(line);
		}
		seq = TwoBit::make_unique<FastaRecord>(name.substr(1), std::move(buildingSeq));
		return true;
	} else {
		std::stringstream ss;
		ss << "error in reading fasta file, line doesn't begin with >, starts with: "
			 << std::endl;
		ss << in.peek() << std::endl;
		throw std::runtime_error { ss.str() };
		return false;
	}
}


}  // namespace TwoBit
