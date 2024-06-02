/* Copyright (c) 2024 Jörgen Grahn
 * All rights reserved.
 *
 */
#include "fortune.h"

#include "files...h"

#include <random>

namespace {

    /**
     * Pick an entry from a container at random.
     */
    template <class V>
    auto pick(const V& v)
    {
        std::random_device rd;
	std::mt19937 gen {rd()};
	using Distribution = std::uniform_int_distribution<typename V::size_type>;
	Distribution distrib {0, v.size()-1};

	auto n = distrib(gen);
	return v[n];
    }
}

/**
 * Selecting a line of text at random, from one or more text files.
 */
std::string fortune(std::ostream&,
		    const std::vector<std::string>& paths)
{
    Files files {begin(paths), end(paths), false};

    std::string s;
    std::vector<std::string> v;
    while (files.getline(s)) {
	v.push_back(s);
    }

    return pick(v);
}
