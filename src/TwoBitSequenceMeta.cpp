///*
// Copyright 2014 Arjan van der Velde, vandervelde.ag [at] gmail
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// */
//
//#include <iostream>
//#include <algorithm>
//
//#include "TwoBitSequenceMeta.hpp"
//#include "TwoBitFile.hpp"
//#include "TwoBitUtil.hpp"
//
//namespace TwoBit
//{
//
//TwoBitSequenceMeta::TwoBitSequenceMeta(const std::string& name,
//		const uint32_t offset, const std::string& filename, const bool swapped) :
//		name_(name), offset_(offset), filename_(filename), swapped_(swapped), dnaSize_(
//				0), dnaBytes_(0), packedpos_(0)
//{
//	file_.open(filename_, std::ios::in | std::ios::binary);
//	readSequenceMeta();
//	file_.close();
//}
//
//TwoBitSequenceMeta::~TwoBitSequenceMeta()
//{
//}
//
//void TwoBitSequenceMeta::readRegions(std::vector<Region>& out)
//{
//	uint32_t count;
//	std::vector<uint32_t> starts;
//	std::vector<uint32_t> lengths;
//
//	count = nextInt(file_, swapped_);
//	for (uint32_t i = 0; i < count; ++i)
//	{
//		// read starts of regions
//		starts.emplace_back(nextInt(file_, swapped_));
//	}
//	for (uint32_t i = 0; i < count; ++i)
//	{
//		// read lengths of regions
//		lengths.emplace_back(nextInt(file_, swapped_));
//	}
//
//	// transform into a usable structure.
//	// {(0, 0), (start, 1), (end, -1), (start, 1), (end, -1), ...}
//	out.clear();
//	out.reserve(count * 2);
//	out.emplace_back(0, 0); // filler, makes logic a little easier
//	for (uint32_t i = 0; i < count; ++i)
//	{
//		out.emplace_back(starts[i], 1);
//		out.emplace_back(starts[i] + lengths[i], -1);
//	}
//	std::sort(out.begin() + 1, out.end(), [](const Region& a, const Region& b)
//	{
//		return a.pos_ < b.pos_;
//	});
//}
//
//void TwoBitSequenceMeta::readSequenceMeta()
//{
//	// open file, seek to offset and read sequence meta data.
//	file_.seekg(offset_);
//	dnaSize_ = nextInt(file_, swapped_); // length of sequence
//	dnaBytes_ = dnaSize_ / 4 + (dnaSize_ % 4 > 0);
//
//	// read nRegions.
//	readRegions(nRegions); // N-regions
//	readRegions(mRegions); // mask regions
//
//	// check. this number should be zero as per the spec.
//	if (0 != nextInt(file_, swapped_))
//	{
//		throw Exception("Unexpected data. Bad 2-bit file.");
//	}
//
//	// store start of packed data
//	packedpos_ = file_.tellg();
//}
//
//void TwoBitSequenceMeta::test()
//{
//	std::cout << "name_: " << name_ << std::endl;
//	std::cout << "offset_: " << offset_ << std::endl;
//	std::cout << "swapped_: " << swapped_ << std::endl;
//	std::cout << "filename_: " << filename_ << std::endl;
//	std::cout << "len(mRegions): " << mRegions.size() << std::endl;
//	std::cout << "len(nRegions): " << nRegions.size() << std::endl;
//	std::cout << std::endl;
//}
//
//} // namespace TwoBit
