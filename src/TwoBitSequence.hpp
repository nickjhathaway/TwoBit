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
//#pragma once
//
//#include <fstream>
//
//namespace TwoBit
//{
//
//class TwoBitSequence
//{
//private:
//	static const uint32_t BUFFER_SIZE = 0x10000; // 64k
//	const TwoBitSequenceMeta& meta_;
//	std::string filename_;
//	std::ifstream file_;
//	char buffer_[BUFFER_SIZE];
//	TwoBitSequence(const TwoBitSequenceMeta& meta);
//public:
//	void getSequence(std::vector<char>& buffer, const uint32_t& start,
//			const uint32_t& end, const bool revcomp = false);
//};
//
//} // namespace TwoBit
