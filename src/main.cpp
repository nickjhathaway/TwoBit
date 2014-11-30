#include "TwoBitFile.hpp"
#include "utils.hpp"

int main(int argc, char** argv)
{
	TwoBit::TwoBitFile tb("/Users/vanderva/.ucscgenome/hg19.2bit");
	tb.init();
//	tb.test();
	return 0;
}

