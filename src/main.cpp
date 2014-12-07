#include "TwoBitFile.hpp"
#include "TwoBitSequence.hpp"

#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
	try
	{
		TwoBit::TwoBitFile tbf("/Users/vanderva/.ucscgenome/hg19.2bit");

		TwoBit::TwoBitSequence tbs = tbf["chr1"];

		std::cout << tbs << std::endl;

		std::string bla;

		tbs.getSequence(bla, 9990, 21000, false, false);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;
		std::cout << std::string(bla.begin(), bla.end()) << std::endl;

		tbs.getSequence(bla, 9990, 21000, true, false);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;
		std::cout << std::string(bla.begin(), bla.end()) << std::endl;

		tbs.getSequence(bla);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;

		tbs.getSequence(bla, 9991, 21017, true, false);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;
		std::cout << std::string(bla.begin(), bla.end()) << std::endl;

		tbs.getSequence(bla, 9990, 10005, false, false);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;
		std::cout << std::string(bla.begin(), bla.end()) << std::endl;

		tbs.getSequence(bla, 9990, 10005, true, false);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;
		std::cout << std::string(bla.begin(), bla.end()) << std::endl;

		for (const std::string& s : tbf.sequenceNames())
		{
			std::cout << s << " ";
		}
		std::cout << std::endl;

		std::cout << tbf.size() << std::endl;

		std::cout << "mRegions:" << std::endl;
		for (const auto& r : tbs.getMetadata().getMaskedRegions())
		{
			std::cout << r.pos_ << ", " << r.action_ << std::endl;
		}

	} catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

