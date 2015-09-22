#include "Exception.hpp"




namespace TwoBit {

Exception::Exception(const std::string & funcName, const std::string & s) :
		what_(funcName + ": " + s) {
}
Exception::Exception(const std::string & s) :
		what_(s) {
}


const char* Exception::what() const throw () {
	return what_.c_str();
}

}  // namespace TwoBit
