#include <catch.hpp>
#include "../src/TwoBit/utils/utils.hpp"

/*
TEST_CASE("Basic tests for make_unique", "[std::unique_ptr<T> make_unique (Args& args)]" ){
  SECTION("GIVE SECTION NAME"){
      YOUR CODE GOES HERE
        NORMALLY END WITH A REQUIRE STATEMENT e.g.
        REQUIRE(TESTVAL1 == YOURVAL);
  }
}
*/

/*
TEST_CASE("Basic tests for writeData", "[void writeData (std::ofstream& out,T& t)]" ){
  SECTION("GIVE SECTION NAME"){
      YOUR CODE GOES HERE
        NORMALLY END WITH A REQUIRE STATEMENT e.g.
        REQUIRE(TESTVAL1 == YOURVAL);
  }
}
*/

/*
TEST_CASE("Basic tests for writeData", "[void writeData (std::ofstream& out,T& t,uint64_t size)]" ){
  SECTION("GIVE SECTION NAME"){
      YOUR CODE GOES HERE
        NORMALLY END WITH A REQUIRE STATEMENT e.g.
        REQUIRE(TESTVAL1 == YOURVAL);
  }
}
*/

/*
TEST_CASE("Basic tests for writeDataVec", "[void writeDataVec (std::ofstream& out,std::vector<T>& d)]" ){
  SECTION("GIVE SECTION NAME"){
      YOUR CODE GOES HERE
        NORMALLY END WITH A REQUIRE STATEMENT e.g.
        REQUIRE(TESTVAL1 == YOURVAL);
  }
}
*/

/*
TEST_CASE("Basic tests for writeDataVec", "[void writeDataVec (std::ofstream& out,std::vector<T>& d,uint64_t size)]" ){
  SECTION("GIVE SECTION NAME"){
      YOUR CODE GOES HERE
        NORMALLY END WITH A REQUIRE STATEMENT e.g.
        REQUIRE(TESTVAL1 == YOURVAL);
  }
}
*/

/*
TEST_CASE("Basic tests for writeString", "[void writeString (std::ofstream& out,std::string str)]" ){
  SECTION("GIVE SECTION NAME"){
      YOUR CODE GOES HERE
        NORMALLY END WITH A REQUIRE STATEMENT e.g.
        REQUIRE(TESTVAL1 == YOURVAL);
  }
}
*/

/*
TEST_CASE("Basic tests for packedSize", "[inline int packedSize (int unpackedSize)]" ){
  SECTION("GIVE SECTION NAME"){
      YOUR CODE GOES HERE
        NORMALLY END WITH A REQUIRE STATEMENT e.g.
        REQUIRE(TESTVAL1 == YOURVAL);
  }
}
*/

/*
TEST_CASE("Basic tests for packDna4", "[unsigned char packDna4 (std::string& str,uint32_t pos)]" ){
  SECTION("GIVE SECTION NAME"){
      YOUR CODE GOES HERE
        NORMALLY END WITH A REQUIRE STATEMENT e.g.
        REQUIRE(TESTVAL1 == YOURVAL);
  }
}
*/


TEST_CASE("Basic tests for unknownToN", "[void unknownToN (std::string& s)]" ){
  SECTION("GIVE SECTION NAME"){
  	std::string testStr = "AAGGACGGTTSSsz";
  	const std::string ans = "AAGGACGGTTNNnn";
  	TwoBit::unknownToN(testStr);
  	REQUIRE(ans == testStr);
  }
}

