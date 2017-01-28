#pragma once
/*
 * utils.hpp
 *
 *  Created on: Sep 21, 2015
 *      Author: nick
 */


#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>
#include "TwoBit/constants.h"

namespace TwoBit{

namespace bfs = boost::filesystem;

#if (defined(__clang__) && __cplusplus < 201305L) || ((defined(__GNUC__) || defined(__GNUG__)) && __cplusplus < 201300L)
// forward declare until using c++14
// http://stackoverflow.com/q/7038357
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#else
using std::make_unique;
#endif


/**@brief Write out data to an ofstream form a single variable
 *
 * @param out the ofstream to write to
 * @param t the data to write, determing the size with sizeof()
 */
template<typename T>
void writeData(std::ofstream & out, const T & t){
	auto* cstr = reinterpret_cast<const char *>(&t);
	out.write(cstr, sizeof(T));
}

/**@brief Write out data to an ofstream from a single variable, forcing size
 *
 * @param out The ofstream to write to
 * @param t the data to write out
 * @param size forcing the size being written out
 */
template<typename T>
void writeData(std::ofstream & out, const T & t, uint64_t size){
	auto* cstr = reinterpret_cast<const char *>(&t);
	out.write(cstr, size);
}

/**@brief Write out the data of a vector to an ofstream
 *
 * @param out The ofstream to write out
 * @param d The vector to write out
 */
template<typename T>
void writeDataVec(std::ofstream & out, const std::vector<T> & d){
  uint64_t numBytes = d.size() * sizeof(T);
  auto* cstr = reinterpret_cast<const char*>(d.data());
  out.write(cstr, numBytes);
}

/**@brief Write out the data of a vector to an ofstream, forcing the size to write
 *
 * @param out The ofstream to write out
 * @param d The vector to write out
 * @param size the size to write out
 */
template<typename T>
void writeDataVec(std::ofstream & out, const std::vector<T> & d, uint64_t size){
  auto* cstr = reinterpret_cast<const char*>(d.data());
  out.write(cstr, size);
}

/**@brief Write a 255 or less character string to a file
 * This will write the length of the string in the first
 * byte then the string itself.
 * @param out the file to write to
 * @param str the string to write
 */
void writeString(std::ofstream & out, std::string str);


/**@brief Return size when packed, rounding up
 *
 * @param unpackedSize The size to pack
 * @return the packed size
 */
inline int packedSize(int unpackedSize){
	return ((unpackedSize + 3) >> 2);
}


/**@brief Pack 4 bases into a unsigned char, assumes there's at least 4 bases including pos from pos in str
 *
 * @param str the string to the get bases from
 * @param pos the position from which to start
 * @return the four bases starting from pos packed into a unsigned char
 */
unsigned char packDna4(const std::string & str, uint32_t pos);

/**Convert non ACGT characters to N in a string
 *
 * @param s the string to convert
 */
void unknownToN(std::string & s);


} //namespace TwoBit




