#pragma once

#include <njhcpp.h>

namespace TwoBit {

class TwoBitRunner : public njh::progutils::ProgramRunner {
 public:
  TwoBitRunner();
  
  static int twoBitToFa(const njh::progutils::CmdArgs & inputCommands);
  static int getTwobitNames(const njh::progutils::CmdArgs & inputCommands);
  static int faToTwoBit(const njh::progutils::CmdArgs & inputCommands);

};
} // namespace TwoBit
