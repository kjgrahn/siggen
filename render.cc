/* Copyright (c) 2024 Jörgen Grahn
 * All rights reserved.
 *
 */
#include "render.h"

#include <vector>
#include <algorithm>

#include "split.h"

namespace {

    /* In [sa, sb) which is a sequence of strings, find the largest
     * prefix which could fit, space-separated, into N characters.
     */
    template <class It>
    It fit(const size_t N, It sa, It sb)
    {
	unsigned n = 0;
	unsigned pad = 0;
	while (sa != sb) {
	    if (n + pad + sa->size() <= N) {
		n += pad + sa->size();
		pad = 1;
		sa++;
	    }
	    else {
		break;
	    }
	}
	return sa;
    }

    /* Fill [a, b) with s (which is guaranteed to fit) and pad with
     * spaces as needed.
     */
    template <class It>
    void fill(It a, It b, const std::string& s)
    {
	for (char ch : s) *a++ = ch;
	std::fill(a, b, ' ');
    }

    template <class It>
    void render(It a, It b,
		const std::vector<std::string>& v)
    {
	auto    hash = [] (char ch) { return ch=='#'; };
	auto nonhash = [] (char ch) { return ch!='#'; };

	auto sa = begin(v);
	const auto sb = end(v);

	while (a!=b) {
	    a = std::find_if(a, b, hash);
	    It c = std::find_if(a, b, nonhash);
	    auto sc = fit(c-a, sa, sb);
	    fill(a, c, join(' ', sa, sc));
	    a = c;
	    sa = sc;
	}
    }
}

/**
 * In 'fmt', consider all blocks of "###...#, and fill them with words
 * from 's' as far as possible.
 *
 * Blocks which cannot be completely filled with words are filled with
 * space. Words are anything separated by whitespace, and never get
 * split.
 *
 * The returned resulting string is the same as 'fmt', except the ###
 * blocks have been eliminated. If a tail of 's' doesn't fit, it's
 * simply discarded.
 */
std::string render(std::string fmt, const std::string& s)
{
    render(begin(fmt), end(fmt), split(s));
    return fmt;
}

