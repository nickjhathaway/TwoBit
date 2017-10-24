#pragma once
/*
 * faToTwoBitPars.hpp
 *
 *  Created on: Jan 26, 2017
 *      Author: nick
 */



#include "TwoBit/utils.h"

namespace TwoBit {

struct faToTwoBitPars {
	std::string inputFilename = "";
	std::string outFilename = "";
	bool overWrite = false;
	bool leaveWhitespaceInName = false;
};


}  // namespace TwoBit




