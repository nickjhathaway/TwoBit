#include "TwoBitFile.hpp"
#include "TwoBitSequence.hpp"

#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
	try
	{
		TwoBit::TwoBitFile tbf("/Users/vanderva/.ucscgenome/hg19.2bitje");

		TwoBit::TwoBitSequence tbs = tbf["chr1"];

		std::cout << tbs << std::endl;

		std::vector<char> bla;

		tbs.getSequence(bla, 9990, 11000);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;
		std::cout << std::string(bla.begin(), bla.end()) << std::endl;

		tbs.getSequence(bla, 9990, 11000, true);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;
		std::cout << std::string(bla.begin(), bla.end()) << std::endl;

		tbs.getSequence(bla, 0, 2000000000);
		std::cout << "bla.size(): " << bla.size() << std::endl;
		std::cout << "bla.capacity(): " << bla.capacity() << std::endl;

	} catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

