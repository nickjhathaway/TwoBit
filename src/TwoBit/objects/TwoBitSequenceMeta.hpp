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

#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace TwoBit
{
class TwoBitSequenceMeta;
class TwoBitSequence;
class TwoBitFile;
}

std::ostream& operator<<(std::ostream& s, const TwoBit::TwoBitSequenceMeta& x);

namespace TwoBit
{

class TwoBitSequenceMeta
{

	// Contains enough information to open a two-bit file and read a specific
	// sequence, without having to read in any meta data. This class exists
	// for the purpose of making TwoBitSequence lightweight (it has a const
	// reference to a TwoBitSequenceMeta object).

private:

	class Region
	{
	public:
		uint32_t pos_;
		int action_; // start or end
		Region() :
				pos_(0), action_(0)
		{
		}
		Region(const uint32_t& pos, const int& action) :
				pos_(pos), action_(action)
		{
		}
	};

	friend class TwoBitFile;
	friend class TwoBitSequence;

	// make it "printable"
	friend std::ostream& ::operator<<(std::ostream& s,
			const TwoBitSequenceMeta& x);

	std::string name_;
	uint32_t offset_;
	std::string filename_;
	bool swapped_;
	uint32_t dnaSize_;
	uint32_t dnaBytes_;
	uint32_t packedPos_;
	std::vector<Region> nRegions; // N-s
	std::vector<Region> mRegions; // Masked

	TwoBitSequenceMeta(const std::string& name, const uint32_t offset,
			const std::string& filename, const bool swapped)
	{
		name_ = name;
		offset_ = offset;
		filename_ = filename;
		swapped_ = swapped;
		dnaSize_ = 0;
		dnaBytes_ = 0;
		packedPos_ = 0;
	}

	TwoBitSequenceMeta()
	{
		name_ = "";
		offset_ = 0;
		filename_ = "";
		swapped_ = false;
		dnaSize_ = 0;
		dnaBytes_ = 0;
		packedPos_ = 0;
	}

};

} // namespace TwoBit

