
#include <iostream>
#include <memory>
#include <sstream>

#include "TwoBit/objects/FastaRecord.hpp"

namespace TwoBit {





/**@brief Method to read from a fasta file piece-wise
 *
 * @param in The input stream to read from
 * @param seq A pointer to a seqInfo to replace with the info with the next read in the fasta file
 * @return A bool whether the function was able to read from the file
 */
bool readNextFasta(std::istream & in, std::unique_ptr<FastaRecord> & seq, bool trimNameAtWhitespace = false);

}  // namespace TwoBit
