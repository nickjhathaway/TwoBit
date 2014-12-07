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

// see http://genome.ucsc.edu/FAQ/FAQformat#format7
#pragma once

#include "TwoBitSequenceMeta.hpp"
#include "Exception.hpp"

#include <string>
#include <fstream>
#include <unordered_map>

namespace TwoBit
{

class TwoBitSequenceMeta;
class TwoBitSequence;

class TwoBitFile
{
private:

	static const uint32_t MAGIC_NUMBER = 0x1A412743;
	static const uint32_t REVERSE_MAGIC_NUMBER = 0x4327411A;
	static const uint32_t VERSION = 0;
	static const uint32_t RESERVED = 0;
	static const uint32_t SEQNAME_MAX_LEN = 256; // represented by one byte so, ...

	bool swapped_;
	uint32_t magic_;
	uint32_t version_;
	uint32_t sequenceCount_;
	uint32_t reserved_;
	std::string filename_;
	std::ifstream file_;
	std::unordered_map<std::string, TwoBitSequenceMeta> sequences_;
	std::vector<std::string> sequenceNames_;

	// util

	// read a uint32_t from file handle and swap bytes if required.
	inline const uint32_t nextInt()
	{
		union aligned
		{
			uint32_t uint;
			char bytes[4];
		} in, out;

		if (file_.read(reinterpret_cast<char*>(&in), 4))
		{
			if (swapped_)
			{
				for (uint32_t i = 0; i < 4; ++i)
				{
					out.bytes[3 - i] = in.bytes[i];
				}
				return out.uint;
			}
			else
			{
				return in.uint;
			}
		}
		else
		{
			throw Exception("Error reading file.");
		}
	}

	// read one char from file handle
	inline const unsigned char nextChar()
	{
		char out;
		if (file_.read(&out, 1))
		{
			return out;
		}
		else
		{
			throw Exception("Error reading file.");
		}
	}

	// read 16 header bytes from file.
	void readTwoBitHeader();

	// create sequences from file
	void createSequenceMeta();
	void populateSequenceMeta(TwoBitSequenceMeta& meta);
	void readRegions(std::vector<TwoBitSequenceMeta::Region>& out);

public:
	// no-copy
	TwoBitFile(const TwoBitFile& other) = delete;
	TwoBitFile() = delete;
	TwoBitFile& operator=(const TwoBitFile& other) = delete;

	TwoBitFile(const std::string& filename);
	TwoBitSequence operator[](const std::string& s) const;
	const std::vector<std::string>& sequenceNames() const;
	const uint32_t size() const;

};

} // namespace TwoBit
