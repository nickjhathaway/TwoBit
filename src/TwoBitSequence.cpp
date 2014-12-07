/*
 Copyright 2014 Arjan van der Velde, vandervelde.ag [at] gmail

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "TwoBitSequence.hpp"
#include "Exception.hpp"

#include <vector>

namespace TwoBit
{

const uint32_t TwoBitSequence::BUFFER_SIZE;

std::string& TwoBitSequence::getSequence(std::string& buffer,
		const uint32_t& start, const uint32_t& end,
		const bool reverseComplement, const bool doMask)
{

	// alphabet for masked and unmasked sequence.
	const char upperfw[5] =
	{ 'T', 'C', 'A', 'G', 'N' };
	const char upperrv[5] =
	{ 'A', 'G', 'T', 'C', 'N' };
	const char lowerfw[5] =
	{ 't', 'c', 'a', 'g', 'n' };
	const char lowerrv[5] =
	{ 'a', 'g', 't', 'c', 'n' };

	uint32_t startNuc;
	uint32_t endNuc;

	// clean start and end (that is: start < end <= dnasize)
	if (start == 0 && end == 0)
	{
		startNuc = 0; // if both are 0, take entire sequence
		endNuc = meta_.dnaSize_;
	}
	else
	{
		startNuc = std::min(meta_.dnaSize_ - 1, start);
		endNuc = std::max(startNuc + 1, std::min(meta_.dnaSize_, end)); // < dnaSize, > startNuc
	}

	// calculate byte positions in file.
	uint32_t startByte = meta_.packedPos_ + (startNuc / 4);
	uint32_t endByte = meta_.packedPos_ + (endNuc / 4) + (endNuc % 4 > 0);

	// resize buffer
	buffer.resize(endNuc - startNuc);

	// reading starts here.
	uint32_t seqPos = (startByte - meta_.packedPos_) * 4; // we start at a byte position
	uint32_t filePos = startByte;

	// counters for N and mask regions
	int m = 0;
	int n = 0;
	uint32_t prevm = 0;
	uint32_t prevn = 0;
	const uint32_t mregionsize = meta_.mRegions.size();
	const uint32_t nregionsize = meta_.nRegions.size();

	file_.seekg(filePos);
	while (filePos < endByte)
	{
		file_.read(buffer_, std::min(endByte - filePos, BUFFER_SIZE));
		filePos += BUFFER_SIZE;

		if (!file_)
		{
			throw Exception("I/O error.");
		}

		// obtain sequence.
		for (uint32_t i = 0; i < file_.gcount(); ++i)
		{
			for (uint32_t j = 0; j < 8; j += 2)
			{
				// fast-forward N-regions to figure out whether we need to return N's or sequence.
				while (prevn < nregionsize
						&& meta_.nRegions[prevn].pos_ <= seqPos)
				{
					n += meta_.nRegions[prevn++].action_;
				}
				// fast-forward mask-regions to figure out whether or not we need to mask.
				while (prevm < mregionsize
						&& meta_.mRegions[prevm].pos_ <= seqPos)
				{
					m += meta_.mRegions[prevm++].action_;
				}

				// if we are within the requested range, insert sequence into output vector
				if (seqPos >= startNuc && seqPos < endNuc)
				{
					// translate 2-bit to sequence.
					if (m == 0 && doMask && n == 0)
					{
						// no mask, no N
						if (reverseComplement)
						{
							buffer[endNuc - seqPos - 1] = upperrv[(buffer_[i]
									>> (6 - j)) & 0x03];
						}
						else
						{
							buffer[seqPos - startNuc] = upperfw[(buffer_[i]
									>> (6 - j)) & 0x03];
						}
					}
					else if (m == 0 && doMask && n > 0)
					{
						// no mask, but N
						if (reverseComplement)
						{
							buffer[endNuc - seqPos - 1] = upperrv[4];
						}
						else
						{
							buffer[seqPos - startNuc] = upperfw[4];
						}
					}
					else if ((m > 0 || !doMask) && n == 0)
					{
						// mask, no N
						if (reverseComplement)
						{
							buffer[endNuc - seqPos - 1] = lowerrv[(buffer_[i]
									>> (6 - j)) & 0x03];
						}
						else
						{
							buffer[seqPos - startNuc] = lowerfw[(buffer_[i]
									>> (6 - j)) & 0x03];
						}
					}
					else if ((m > 0 || !doMask) && n > 0)
					{
						// masked N (should not happen I guess)
						if (reverseComplement)
						{
							buffer[endNuc - seqPos - 1] = lowerrv[4];
						}
						else
						{
							buffer[seqPos - startNuc] = lowerfw[4];
						}
					}
					else
					{
						// negative values for m or n means something's not quite right.
						throw Exception("Error parsing regions.");
					}
				}
				++seqPos;
			}
		}
	}
	return buffer;
}

} // namespace TwoBit

std::ostream& operator<<(std::ostream& s, const TwoBit::TwoBitSequence& x)
{
	s << x.meta_;
	return s;
}
