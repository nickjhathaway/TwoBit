
    
#include "TwoBitRunner.hpp"
#include <iostream>
#include <exception>
#include <cppitertools/range.hpp>
#include "TwoBit/objects/TwoBitSequence.hpp"
#include "TwoBit/IO.h"
#include "TwoBitSetUp.hpp"

namespace TwoBit {

TwoBitRunner::TwoBitRunner()
    : njh::progutils::ProgramRunner ({
	addFunc("twoBitToFa", twoBitToFa, false),
  addFunc("faToTwoBit", faToTwoBit, false),
	addFunc("getTwobitNames", getTwobitNames, false)},
                    "TwoBit",  "2", "0", "9-dev") {}


int TwoBitRunner::getTwobitNames(const njh::progutils::CmdArgs & inputCommands){
	std::string inputFilename = "";
	TwoBitSetUp setUp(inputCommands);

	setUp.setOption(inputFilename, "--in,-i", "Input 2bit filename",true );
	setUp.finishSetUp(std::cout);
	TwoBitFile f(inputFilename);
	auto names  = f.sequenceNames();
	for(const auto & name : names){
		std::cout << name << std::endl;
	}
	return 0;
}

int TwoBitRunner::twoBitToFa(const njh::progutils::CmdArgs & inputCommands){
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
		std::ostream out(njh::files::determineOutBuf(outfile,outFilename, ".fasta", overWrite, false, true));
		for (const std::string& s : f.sequenceNames()) {
			f[s]->getSequence(buffer);
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


int TwoBitRunner::faToTwoBit(const njh::progutils::CmdArgs & inputCommands) {
	faToTwoBitPars pars;
	TwoBitSetUp setUp(inputCommands);

	setUp.setOption(pars.inputFilename, "--in,-i", "Input fasta filename, can be several files seperated by commas", true);
	setUp.setOption(pars.outFilename, "--out,-o",
			"Name of an output file", true);
	setUp.setOption(pars.overWrite, "--overWrite",
			"Whether to overwrite the file if one is given by --out");
	setUp.setOption(pars.leaveWhitespaceInName, "--leaveWhitespaceInName",
				"Whether to trim the names of the fasta records at the first whitespace");
	setUp.finishSetUp(std::cout);

	fastasToTwoBit(pars);
	return 0;
}

                    
} // namespace njhseq
