#pragma once

#include <bibcpp.h>

namespace TwoBit {

class TwoBitRunner : public bib::progutils::programRunner {
 public:
  TwoBitRunner();
  
  static int twoBitToFa(const bib::progutils::CmdArgs & inputCommands);
  static int getTwobitNames(const bib::progutils::CmdArgs & inputCommands);
  static int faToTwoBit(const bib::progutils::CmdArgs & inputCommands);

};
} // namespace TwoBit
