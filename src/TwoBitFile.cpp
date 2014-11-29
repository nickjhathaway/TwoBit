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

#include "TwoBitFile.hpp"
#include "TwoBitSequence.hpp"
#include "TwoBitUtil.hpp"

#include "Exception.hpp"
#include <iostream>
#include <algorithm>

namespace TwoBit
{

TwoBitFile::TwoBitFile(const std::string& filename) :
		swapped_(false), magic_(0), version_(0), sequenceCount_(0), reserved_(
				0), filename_(filename)
{
}

void TwoBitFile::readHeader()
{
	if (file_.read(reinterpret_cast<char*>(&magic_), 4))
	{
		if (magic_ == MAGIC_NUMBER)
		{
			swapped_ = false;
		}
		else if (magic_ == REVERSE_MAGIC_NUMBER)
		{
			swapped_ = true;
		}
		else
		{
			throw Exception("Invalid magic number. Bad 2-bit file.");
		}
	}
	else
	{
		throw Exception("Error reading from file.");
	}
	version_ = nextInt(file_, swapped_);
	sequenceCount_ = nextInt(file_, swapped_);
	reserved_ = nextInt(file_, swapped_);

	// integrity check
	if (VERSION != version_)
	{
		throw Exception("Unexpected version number. Bad 2-bit file.");
	}
	if (RESERVED != reserved_)
	{
		throw Exception("Unexpected data. Bad 2-bit file.");
	}
}

void TwoBitFile::createSequences()
{
	uint32_t seqNameLen, offset;
	char seqName[256]; // length field is one byte.
	for (uint32_t i = 0; i < sequenceCount_; ++i)
	{
		seqNameLen = nextChar(file_); // length
		file_.read(seqName, seqNameLen); // sequence name
		offset = nextInt(file_, swapped_); // offset
		sequences_.emplace(std::string(seqName, seqNameLen),
				std::make_shared<TwoBitSequence>(
						std::string(seqName, seqNameLen), offset, *this));
	}
}

void TwoBitFile::init()
{
	file_.open(filename_, std::ios::in | std::ios::binary);
	try
	{
		readHeader();
	} catch (Exception& e)
	{
		file_.close();
		throw(e);
	}
	createSequences();
	file_.close();
}

void TwoBitFile::test()
{
	for (auto& i : sequences_)
	{
		i.second->test();
	}
	printf("magic: 0x%X\n", magic_);
	std::cout << "version_: " << version_ << std::endl;
	printf("sequenceCount: 0x%X\n", sequenceCount_);
	std::cout << "reserved: " << reserved_ << std::endl;

	std::vector<char> myseq;
//	sequences_["chrUn_gl000215"]->getSequence(myseq, 0, 20000);
	sequences_["chr1"]->getSequence(myseq, 20000, 20100, false);
//	sequences_["chrXIII"]->getSequence(myseq, 0, 2000000000);
	//std::cout << std::string(myseq.begin(), myseq.end()) << std::endl;

	std::cout << "myseq.size(): " << myseq.size() << std::endl;
	std::cout << "myseq.capacity(): " << myseq.capacity() << std::endl;

	//std::reverse(myseq.begin(), myseq.end());


	sequences_["chr1"]->getSequence(myseq, 15000, 15020, false);
	std::cout << std::string(myseq.begin(), myseq.end()) << std::endl;
	sequences_["chr1"]->getSequence(myseq, 15000, 15020, true);
	std::cout << std::string(myseq.begin(), myseq.end()) << std::endl;


	unsigned char x = 6;
	std::cout << (x << 2) << std::endl;
}

} // namespace TwoBit

