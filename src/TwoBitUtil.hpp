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

#include "Exception.hpp"

namespace TwoBit
{

// read a uint32_t from file handle and swap bytes if required.
inline const uint32_t nextInt(std::ifstream& file, const bool swapped)
{
	union aligned
	{
		uint32_t uint;
		char bytes[4];
	} in, out;

	if (file.read(reinterpret_cast<char*>(&in), 4))
	{
		if (swapped)
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
		throw Exception("Error reading from file.");
	}
}

// read one char from file handle
inline const unsigned char nextChar(std::ifstream& file)
{
	char out;
	if (file.read(reinterpret_cast<char*>(&out), 1))
	{
		return out;
	}
	else
	{
		throw Exception("Error reading from file.");
	}
}

} // namespace TwoBit
