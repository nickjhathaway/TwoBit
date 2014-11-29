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

#include <iostream>
#include <algorithm>

#include "TwoBitSequence.hpp"
#include "TwoBitFile.hpp"
#include "TwoBitUtil.hpp"

namespace TwoBit
{

TwoBitSequence::TwoBitSequence(const std::string& name, const uint32_t offset,
		TwoBitFile& file) :
		name_(name), offset_(offset), filename_(file.filename_), swapped_(
				file.swapped_), dnaSize_(0), dnaBytes_(0), packedpos_(0)
{
	open();
}

TwoBitSequence::~TwoBitSequence()
{
	close();
}

void TwoBitSequence::readRegions(std::vector<Region>& out)
{
	uint32_t count;
	count = nextInt(file_, swapped_);
	std::vector<uint32_t> starts;
	std::vector<uint32_t> lengths;

	for (uint32_t i = 0; i < count; ++i)
	{
		starts.emplace_back(nextInt(file_, swapped_));
	}
	for (uint32_t i = 0; i < count; ++i)
	{
		lengths.emplace_back(nextInt(file_, swapped_));
	}

	out.clear();
	out.reserve(count * 2);
	out.emplace_back(0, 0); // filler, makes logic a little easier
	for (uint32_t i = 0; i < count; ++i)
	{
		out.emplace_back(starts[i], 1);
		out.emplace_back(starts[i] + lengths[i], -1);
	}

	std::sort(out.begin(), out.end(), [](const Region& a, const Region& b)
	{
		return a.pos_ < b.pos_;
	});
}

void TwoBitSequence::open()
{
	// open file, seek to offset and read sequence meta data
	file_.open(filename_, std::ios::in | std::ios::binary);
	file_.seekg(offset_);
	dnaSize_ = nextInt(file_, swapped_); // length of sequence
	dnaBytes_ = dnaSize_ / 4 + (dnaSize_ % 4 > 0);

	// read nRegions
	readRegions(nRegions); // N-regions
	readRegions(mRegions); // mask regions

	// check. this number should be zero
	if (0 != nextInt(file_, swapped_))
	{
		throw Exception("Unexpected data. Bad 2-bit file.");
	}

	// store start of packed data
	packedpos_ = file_.tellg();
}

void TwoBitSequence::close()
{
	file_.close();
}

void TwoBitSequence::test()
{
	std::cout << "name_: " << name_ << std::endl;
	std::cout << "offset_: " << offset_ << std::endl;
	std::cout << "swapped_: " << swapped_ << std::endl;
	std::cout << "filename_: " << filename_ << std::endl;
}

void TwoBitSequence::getSequence(std::vector<char>& buffer, uint32_t start, uint32_t end)
{
	const char upper[5] = {'T', 'C', 'A', 'G', 'N'};
	const char lower[5] = {'t', 'c', 'a', 'g', 'n'};

	int m = 0;
	int n = 0;
	uint32_t prevm = 0;
	uint32_t prevn = 0;

	uint32_t startNuc = std::min(dnaSize_ - 1, start);
	uint32_t endNuc = std::max(startNuc + 1, std::min(dnaSize_, end)); // < dnaSize, > startNuc.
	uint32_t startByte = packedpos_ + (startNuc / 4);
	uint32_t endByte = packedpos_ + (endNuc / 4) + (endNuc % 4 > 0);

	// update start and end nucleotide to the ones we're actually reading
	startNuc = (startByte - packedpos_) * 4;
	endNuc = (endByte - packedpos_) * 4;
	uint32_t spos = startNuc;
	uint32_t gpos = startByte;

	buffer.clear();
	buffer.reserve(endNuc - startNuc);

	file_.seekg(gpos);
	while (gpos < endByte) {
		file_.read(buffer_, std::min(endByte - gpos, BUFFER_SIZE));
		gpos += BUFFER_SIZE;

		// obtain sequence
		for (uint32_t i = 0; i < file_.gcount(); ++i)
		{
			for (uint32_t j = 0; j < 8; j += 2)
			{

				while (prevn < nRegions.size() && nRegions[prevn].pos_ <= spos)
				{
					n += nRegions[prevn++].action_;
				}
				while (prevm < mRegions.size() && mRegions[prevm].pos_ <= spos)
				{
					m += mRegions[prevm++].action_;
				}

				if (m == 0 && n == 0)
				{
					buffer.push_back(upper[(buffer_[i] >> (6 - j)) & 0x03]);
				}
				else if (m == 0 && n > 0)
				{
					buffer.push_back(upper[4]);
				}
				else if (m > 0 && n == 0)
				{
					buffer.push_back(lower[(buffer_[i] >> (6 - j)) & 0x03]);
				}
				else if (m > 0 && n > 0)
				{
					buffer.push_back(lower[4]);
				} else {
					throw Exception("Error parsing regions.");
				}
				spos++;
			}
		}
	}
}

} // namespace TwoBit
