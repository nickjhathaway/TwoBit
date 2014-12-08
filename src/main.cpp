#include "TwoBitFile.hpp"
#include "TwoBitSequence.hpp"

#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
	try
	{
/*
		TwoBit::TwoBitFile twobitFile("/Users/vanderva/.ucscgenome/hg19.2bit");
		TwoBit::TwoBitSequence twobitSequence = twobitFile["chr1"];
		std::cout << twobitSequence << std::endl; // print meta

		std::string buffer;

		twobitSequence.getSequence(buffer, 9990, 21000);
		std::cout << buffer << std::endl;

		twobitSequence.getSequence(buffer, 9990, 21000, false, false);
		std::cout << buffer << std::endl;

		twobitSequence.getSequence(buffer, 9990, 21000, true, false);
		std::cout << buffer << std::endl;

		twobitSequence.getSequence(buffer);
		std::cout << "buffer.size(): " << buffer.size() << std::endl;
		std::cout << "buffer.capacity(): " << buffer.capacity() << std::endl;

		std::cout << twobitFile.size() << std::endl;
		for (const std::string& s : twobitFile.sequenceNames())
		{
			std::cout << s << " ";
		}
		std::cout << std::endl;

		std::cout << "Masked regions:" << std::endl;
		for (const auto& r : twobitSequence.getMaskedRegions())
		{
			if (r.action_ > 0)
			{
				std::cout << twobitSequence.getName() << ":" << r.pos_ << "-";
			}
			else if (r.action_ < 0)
			{
				std::cout << r.pos_ << std::endl;
			}
		}
		std::cout << std::endl;

		std::cout << "N-regions:" << std::endl;
		for (const auto& r : twobitSequence.getNRegions())
		{
			if (r.action_ > 0)
			{
				std::cout << twobitSequence.getName() << ":" << r.pos_ << "-";
			}
			else if (r.action_ < 0)
			{
				std::cout << r.pos_ << std::endl;
			}
		}
		std::cout << std::endl;
*/
		// TODO: it would be convenient and efficient to have TwoBitSequence be an input stream.

		TwoBit::TwoBitFile f("/Users/vanderva/.ucscgenome/hg19.2bit");
		std::string buffer;
		for (const std::string& s : f.sequenceNames())
		{
			f[s].getSequence(buffer);
			std::cout << ">" << s << std::endl;
			for (uint32_t i = 0; i < buffer.size(); i += 80)
			{
				std::cout << buffer.substr(i, 80) << '\n';
			}
			std::cout.flush();
		}

	} catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

