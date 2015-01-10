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

#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
	try
	{
		// TODO: it would be convenient and efficient to have TwoBitSequence be an input stream.

		TwoBit::TwoBitFile f("/home/vanderva/.ucscgenome/hg19.2bit");
		std::string buffer;
		for (const std::string& s : f.sequenceNames())
		{
			f[s].getSequence(buffer);
			std::cout << ">" << s << std::endl;
			for (uint32_t i = 0; i < buffer.size(); i += 80)
			{
				std::cout << buffer.substr(i, 80) << '\n';
			}
			std::cout.flush();
		}

	} catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

