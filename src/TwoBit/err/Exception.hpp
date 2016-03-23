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

#include <exception>
#include <string>

namespace TwoBit
{

/**@brief General exception
 *
 */
class Exception: public std::exception {
protected:
	const std::string what_;	/**< error message*/
public:
	/**@brief Construct with a function name and an error message
	 *
	 * @param funcName The function name, normally given by __PRETTY_FUNCTION__
	 * @param s An error message
	 */
	Exception(const std::string & funcName, const std::string & s);
	/**@brief Construct with an error message
	 *
	 * @param s
	 */
	Exception(const std::string & s);

	virtual ~Exception() {
	}
	/**@brief Report error message
	 *
	 * @return The error message
	 */
	virtual const char* what() const throw ();
};

} // namespace TwoBit
