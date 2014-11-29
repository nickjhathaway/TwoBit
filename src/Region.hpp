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

class Region
{ // zero-based, open-ended region
private:
	uint32_t start_;
	uint32_t end_;

public:

	Region(const uint32_t start, const uint32_t end) :
			start_(start), end_(end)
	{
		if (start >= end)
		{
			throw Exception("Region cannot be of zero or negative length.");
		}
	}

	const bool comp(const Region& a, const Region& b) const
	{
		return (a.start_ < b.start_);
	}

	const bool equiv(const Region& a, const Region& b) const
	{
		return (!comp(a, b) && !comp(b, a));
	}

	const bool operator<(const Region& other) const
	{
		return comp(*this, other);
	}

	const bool operator>(const Region& other) const
	{
		return comp(other, *this);
	}

	const bool operator==(const Region& other) const
	{
		return equiv(*this, other);
	}

	const bool overlap(const Region& other) const
	{
		return (other.start_ >= start_ && other.start_ < end_) ||
			(start_ >= other.start_ && start_ < other.end_);
	}

	const uint32_t start() const
	{
		return start_;
	}

	const uint32_t end() const
	{
		return end_;
	}

};

} // namespace TwoBit
