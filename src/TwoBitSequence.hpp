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

#include "TwoBitSequenceMeta.hpp"

#include <fstream>
#include <iostream>

namespace TwoBit
{
class TwoBitSequence;
}

std::ostream& operator<<(std::ostream& s, const TwoBit::TwoBitSequence& x);

namespace TwoBit
{

class TwoBitSequence
{
private:

	static const uint32_t BUFFER_SIZE = 0x80000; //512k

	std::ifstream file_;
	const TwoBitSequenceMeta& meta_;
	char buffer_[BUFFER_SIZE];

	friend class TwoBitFile;

	// make it "printable"
	friend std::ostream& ::operator<<(std::ostream& s, const TwoBitSequence& x);

	TwoBitSequence(const TwoBitSequenceMeta& meta) :
			meta_(meta)
	{
		file_.open(meta_.filename_, std::ios::in | std::ios::binary);
	}

public:

	virtual ~TwoBitSequence()
	{
		file_.close();
	}

	TwoBitSequence(const TwoBitSequence& other) :
			TwoBitSequence(other.meta_)
	{
	}

	// delete some stuff.
	TwoBitSequence() = delete;
	TwoBitSequence& operator=(const TwoBitSequence& other) = delete;

	// get sequence, from start to end, optionally in reverse-complement
	std::string& getSequence(std::string& buffer, const uint32_t& start = 0,
			const uint32_t& end = 0, const bool reverseComplement = false,
			const bool doMask = true);


	// delegated getters and setter


	uint32_t getDnaBytes() const
	{
		return meta_.dnaBytes_;
	}
	uint32_t getDnaSize() const
	{
		return meta_.dnaSize_;
	}
	const std::string& getFilename() const
	{
		return meta_.filename_;
	}
	const std::vector<TwoBitSequenceMeta::Region>& getMaskedRegions() const
	{
		return meta_.mRegions;
	}
	const std::string& getName() const
	{
		return meta_.name_;
	}
	const std::vector<TwoBitSequenceMeta::Region>& getNRegions() const
	{
		return meta_.nRegions;
	}
	uint32_t getOffset() const
	{
		return meta_.offset_;
	}
	uint32_t getPackedPos() const
	{
		return meta_.packedPos_;
	}
	bool isSwapped() const
	{
		return meta_.swapped_;
	}


};

} // namespace TwoBit

