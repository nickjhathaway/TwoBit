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

class TwoBitSequence : public SequenceMeta
{
private:

	static const uint32_t BUFFER_SIZE = 0x80000; //512k

	std::ifstream file_;
	char buffer_[BUFFER_SIZE];

	friend class TwoBitFile;

	TwoBitSequence(const SequenceMeta& other) : SequenceMeta(other)
	{
		file_.open(filename_, std::ios::in | std::ios::binary);
	}

public:

	TwoBitSequence(const TwoBitSequence& other) : SequenceMeta(other)
	{
		file_.open(filename_, std::ios::in | std::ios::binary);
	}

	virtual ~TwoBitSequence()
	{
		file_.close();
	}

	// delete some stuff.
	TwoBitSequence() = delete;
	TwoBitSequence& operator=(const TwoBitSequence& other) = delete;

	// get sequence, from start to end, optionally in reverse-complement
	std::string& getSequence(std::string& buffer, const uint32_t& start = 0,
			const uint32_t& end = 0, const bool reverseComplement = false,
			const bool doMask = true);

};

} // namespace TwoBit

