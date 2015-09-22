#include "utils.hpp"
#include <string.h>


namespace TwoBit {

void writeString(std::ofstream & out, std::string str) {
	unsigned char bLen;
	int len = strlen(str.c_str());
	if (len > 255) {
		std::cerr << "String too long in writeString (" << len << "chars):\n" << str << std::endl;
		len = 255;
		str = str.substr(0,len);
		str.shrink_to_fit();
	}

	bLen = len;
	writeData(out, bLen);
	//writeData(out, str.c_str());
	out.write(str.c_str(), len);
	//writeData(out, str.c_str(), len);
}



unsigned char packDna4(const std::string & str, uint32_t pos){
	unsigned char out = 0;
	int bVal;
	for(int count = 0; count < 4; ++count){
		bVal = ntValNoN[static_cast<int>(str[pos + count])];
		out <<= 2;
		out += bVal;
	}
	return out;
}


void unknownToN(std::string & s){
	for(auto & c : s){
		if(ntChars[c] == 0){
			if(isupper(c)){
				c = 'N';
			}else{
				c = 'n';
			}
		}
	}
}

}  // namespace TwoBit
