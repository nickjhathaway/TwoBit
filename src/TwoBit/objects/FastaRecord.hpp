#pragma once
/*
 * FastaRecord.hpp
 *
 *  Created on: Sep 21, 2015
 *      Author: nick
 */

#include "TwoBit/utils.h"
#include <cppitertools/range.hpp>

namespace TwoBit {

class FastaRecord {
public:
	/**@brief Constructor with universal reference so that large strings can be moved from
	 *
	 * @param name The name of the sequene
	 * @param seq The seqeunce to store, can be a lvalue or rvalue reference to optimize not having to copy large strings
	 */
	template<typename T>
	FastaRecord(const std::string & name, T && seq) :
			name_(name), seq_(std::forward<T>(seq)) {
		static_assert(std::is_constructible<std::string, T>::value,
				"Parameter seq can't be used to construct a std::string in constructing seqInfo");
		unknownToN(seq_);
		//determine masks and ns
		storeBlocksOfLower();
		storeBlocksOfN();
	}

	std::string name_;/**< The name of the sequence*/
	std::string seq_;/**< The sequence */
	std::vector<uint32_t> nStarts_;/**< The start sites of the n regions*/
	std::vector<uint32_t> nSizes_;/**< The sizes of the n regions*/
	std::vector<uint32_t> maskStarts_;/**< The start sites of the masked regions*/
	std::vector<uint32_t> maskSizes_;/**< The sizes of the masked regions*/
	uint32_t reserved_ = 0;/**< Reserved for future use in the twobit format*/
	/**@brief convert seq_ into a vector of unsinged char with two bits per base
	 *
	 * @return seq_ converted into a vec of unsigned char with two bits per base info
	 */
	std::vector<unsigned char> data()const;
private:
	/**@brief Store starts and sizes of blocks of N's
	 *
	 * @param str The string to analyze
	 * @param starts The vec to store start positions
	 * @param sizes The vec to store sizes of blocks
	 */
	void storeBlocksOfN();
	/**@brief Store starts and sizes of blocks of lower case letters
	 *
	 * @param str The string to analyze
	 * @param starts The vec to store start positions
	 * @param sizes The vec to store sizes of blocks
	 */
	void storeBlocksOfLower();
public:
	/**@brief Figure out size structure will take in file
	 *
	 * @return The size the sequence is going to take up
	 */
	int twoBitSizeInFile()const;

	/**@brief Write out one twoBit sequence to binary file
	 * Note this does not include the name, which is
	 * stored only in index
	 * @param out The file to write to
	 */
	void twoBitWriteOne(std::ofstream & out) const;
};

}  // namespace TwoBit
