

#include "constants.hpp"
#include <atomic>

namespace TwoBit {

void initNtChars() {
	static std::atomic<bool> initted(false);
	if (!initted) {
		ntChars.fill(0);
		ntChars['A'] = 'A';
		ntChars['a'] = 'a';
		ntChars['C'] = 'C';
		ntChars['c'] = 'c';
		ntChars['G'] = 'G';
		ntChars['g'] = 'g';
		ntChars['T'] = 'T';
		ntChars['t'] = 't';
		ntChars['N'] = 'N';
		ntChars['n'] = 'n';
		ntChars['U'] = 'U';
		ntChars['u'] = 'u';
		ntChars['-'] = 'n';
		initted = true;
	}
}


void initNtValNoN(){
	static std::atomic<bool> initted(false);
	if (!initted) {
		ntValNoN.fill(0);
		ntValNoN['a'] = ntValNoN['A'] = 2;
		ntValNoN['c'] = ntValNoN['C'] = 1;
		ntValNoN['g'] = ntValNoN['G'] = 3;
		ntValNoN['t'] = ntValNoN['T'] = 0;
		ntValNoN['u'] = ntValNoN['U'] = 0;
		initted = true;
	}
}

}  // namespace TwoBit
