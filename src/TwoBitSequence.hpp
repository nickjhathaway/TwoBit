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

	static const uint32_t BUFFER_SIZE = 0x10000; // 64k

	std::ifstream file_;
	const SequenceMeta& meta_;
	char buffer_[BUFFER_SIZE];

	friend class TwoBitFile;

	TwoBitSequence(const SequenceMeta& meta) :
			meta_(meta)
	{
		file_.open(meta_.filename_, std::ios::in | std::ios::binary);
	}

	// make it "printable"
	friend std::ostream& ::operator<<(std::ostream& s, const TwoBitSequence& x);

public:

	virtual ~TwoBitSequence()
	{
		file_.close();
	}

	TwoBitSequence(const TwoBitSequence& other) :
			TwoBitSequence(other.meta_)
	{
	}
	;

	// delete some stuff.
	TwoBitSequence() = delete;
	TwoBitSequence& operator=(const TwoBitSequence& other) = delete;

	void getSequence(std::vector<char>& buffer, const uint32_t& start,
			const uint32_t& end, const bool revcomp = false);

	const SequenceMeta& getMeta() const;

};

} // namespace TwoBit

