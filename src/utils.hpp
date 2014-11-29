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

//
// This code is courtesy of Michael Purcaro.
// https://github.com/purcaro/
//
#pragma once

#include <boost/optional.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <sstream>

#include <zi/time/time.hpp>

namespace bfs = boost::filesystem;

#define likely(x) __builtin_expect ((x), 1)
#define unlikely(x) __builtin_expect ((x), 0)

namespace bamcuts
{

class TicToc: public zi::wall_timer
{
private:
	const std::string prefix_;
	const bool tab_;

public:
	TicToc() :
			prefix_(""), tab_(true)
	{
	}

	TicToc(const std::string s, bool tab = true) :
			prefix_(s), tab_(tab)
	{
	}

	~TicToc()
	{
		print();
	}

	void print()
	{
		if (tab_)
		{
			std::cerr << "\t";
		}
		if (prefix_ != "")
		{
			std::cerr << prefix_ << " ";
		}
		std::cerr << "(" << elapsed<zi::in_usecs>() / 1000000. << " secs)"
				<< std::endl;
	}

	void print(const std::string& msg)
	{
		if (tab_)
		{
			std::cerr << "\t";
		}
		if (prefix_ != "")
		{
			std::cerr << prefix_ << " ";
		}
		std::cerr << "(" << elapsed<zi::in_usecs>() / 1000000. << " secs): "
				<< msg << std::endl;
	}
};

template<class C>
uint32_t len(const C& c)
{
	return static_cast<uint32_t>(c.size());
}

template<class C, class UnaryFunction>
UnaryFunction for_each(const C& c, UnaryFunction f)
{
	return std::for_each(c.begin(), c.end(), f);
}

template<class C>
auto min_element(const C& c) -> decltype(c.begin())
{
	return std::min_element(c.begin(), c.end());
}

template<class C, class Compare>
auto min_element(const C& c, Compare comp) -> decltype(c.begin())
{
	return std::min_element(c.begin(), c.end(), comp);
}

template<class C>
auto max_element(const C& c) -> decltype(c.begin())
{
	return std::max_element(c.begin(), c.end());
}

template<class C, class Compare>
auto max_element(const C& c, Compare comp) -> decltype(c.begin())
{
	return std::max_element(c.begin(), c.end(), comp);
}

} // namespace bamcuts

// from http://stackoverflow.com/a/389901
/// ASSERT(condition) checks if the condition is met, and if not, calls
/// ABORT with an error message indicating the module and line where
/// the error occurred.
#ifndef ASSERT
#define ASSERT(x)                                                      \
    if (!(x)) {                                                         \
        char buf[2048];                                                 \
        snprintf (buf, 2048, "Assertion failed in \"%s\", line %d\n"    \
                 "\tProbable bug in software.\n",                       \
                 __FILE__, __LINE__);                                   \
        throw std::runtime_error(buf);                                  \
    }                                                                   \
    else   // This 'else' exists to catch the user's following semicolon
#endif
/// DASSERT(condition) is just like ASSERT, except that it only is
/// functional in DEBUG mode, but does nothing when in a non-DEBUG
/// (optimized, shipping) build.
#ifdef DEBUG
# define DASSERT(x) ASSERT(x)
#else
# define DASSERT(x) /* DASSERT does nothing when not debugging */
#endif

#ifdef DEBUG
#define DPRINT(x) std::cerr << (x) << std::endl;
#else
#define DPRINT(x)
#endif

namespace utility
{
static inline std::string exec(const std::string& cmd)
{
	// from http://stackoverflow.com/a/478960
	FILE* pipe = popen(cmd.c_str(), "r");
	if (!pipe)
	{
		return "ERROR opening pipe";
	}
	char buffer[128];
	std::string result = "";
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}
} // namespace utility

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

namespace str
{
static inline boost::optional<std::string> regex_first_match(
		const std::string& str, const boost::regex e)
{
	boost::match_results<std::string::const_iterator> results;
	if (boost::regex_match(str, results, e))
	{
		return boost::optional<std::string>(results[1]);
	}
	return boost::optional<std::string>();
}

static inline std::string toLower(const std::string& str)
{
	return boost::algorithm::to_lower_copy(str);
}

template<class T>
static std::string pluralize(T n, std::string singular, std::string plural = "")
{
	std::string r = std::to_string(n) + " ";
	if (1 == n)
	{
		return r + singular;
	}
	if ("" == plural)
	{
		return singular + "s";
	}
	return r + plural;
}

static inline std::string replace(const std::string& s, std::string f,
		std::string t)
{
	return boost::replace_all_copy(s, f, t);
}

template<class T>
static inline std::string join(const T& c, const std::string delim = " ")
{
	return boost::algorithm::join(c, delim);
}

static inline std::string join(const std::vector<std::string> c,
		const std::string delim = " ")
{
	return boost::algorithm::join(c, delim);
}
static inline void trim(std::string& s)
{
	boost::trim(s);
}
static inline bool startswith(const std::string& s, const std::string& pred)
{
	return boost::starts_with(s, pred);
}
static inline bool endswith(const std::string& s, const std::string& pred)
{
	return boost::ends_with(s, pred);
}

static inline bool endswith(const boost::filesystem::path& e,
		const std::string& pred)
{
	return endswith(e.filename().string(), pred);
}

template<typename RangeT, typename PredicateT>
static inline std::vector<std::string> split(const std::string& s,
		const RangeT& r, PredicateT p = boost::token_compress_off)
{
	std::vector<std::string> ret;
	boost::split(ret, s, r, p);
	return ret;
}

static inline std::vector<std::string> split(const std::string& s, char r)
{
	std::vector<std::string> ret;
	// hint from http://stackoverflow.com/q/9653155
	boost::split(ret, s, std::bind2nd(std::equal_to<char>(), r));
	return ret;
}

} // namespace str
