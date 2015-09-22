#pragma once
/*
 * constants.hpp
 *
 *  Created on: Sep 21, 2015
 *      Author: nick
 */

#include <array>
#include <stdint.h>

namespace TwoBit {

 /**@brief Signature into 2bit file (2 bits per nucleotide DNA file) plus
 * information on N and masked bases. */
const static uint32_t twoBitSig = 0x1A412743;

/**@brief  A little array to help us decide if a character is a
 * nucleotide, and if so convert it to lower case.
 *
 */
static std::array<char, 256> ntChars;

/**@brief A table that gives values 0 for t
			     1 for c
			     2 for a
			     3 for g
 * (which is order aa's are in biochemistry codon tables)
 * and gives -1 for all others.
 *
 */
static std::array<int, 256> ntValNoN;

/**@brief Initialize the nucleotide array of nucleotide to two bit value
 *A table that gives values 0 for t
 *			     1 for c
 *			     2 for a
 *			     3 for g
 *
 */
void initNtValNoN();


/**@brief Initialize the nucleotide characters array
 *
 */
void initNtChars() ;

}  // namespace TwoBit
