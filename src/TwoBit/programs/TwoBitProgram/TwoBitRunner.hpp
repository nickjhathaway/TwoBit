#pragma once

#include <cppprogutils/programRunner.hpp>

namespace TwoBit {

class TwoBitRunner : public cppprogutils::programRunner {
 public:
  TwoBitRunner();
  
  static int twoBitToFa(std::map<std::string, std::string> inputCommands);
  static int faToTwoBit(std::map<std::string, std::string> inputCommands);

};
} // namespace TwoBit
