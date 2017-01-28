#pragma once
/*
 * TwoBitOut.hpp
 *
 *  Created on: Sep 21, 2015
 *      Author: nick
 */


#include "TwoBit/objects/FastaRecord.hpp"
#include "TwoBit/pars/faToTwoBitPars.hpp"
#include <memory>

namespace TwoBit {


/**@brief  Write out header portion of twoBit file, including initial index
 *
 * @param seqs The sequences that will be going into the file
 * @param out The file to write to
 */
void twoBitWriteHeader(const std::vector<std::unique_ptr<FastaRecord>> & seqs, std::ofstream & out);

/**@brief Write fasta files to output 2bit file
 *
 * @param pars Parameters to use, contains input name and output name
 */
void fastasToTwoBit(const faToTwoBitPars & pars);


}  // namespace TwoBit




