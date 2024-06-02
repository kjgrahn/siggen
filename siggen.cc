/*
 * Copyright (c) 2024 Jörgen Grahn
 * All rights reserved.
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

#include <getopt.h>

#include "fortune.h"
#include "render.h"

namespace {

    /* Read a whole file (hopefully a shortish one) into a string.
     */
    std::string read(std::istream& is)
    {
	char buf[10];
	std::string s;
	while (1) {
	    is.read(buf, sizeof buf);
	    s.append(buf, is.gcount());
	    if (!is) break;
	}
	return s;
    }
}

int main(int argc, char ** argv)
{
    const std::string prog = argv[0] ? argv[0] : "siggen";
    const std::string usage = "usage: "
	+ prog +
	" -f quotes ..."
	" signature\n"
	"       "
	+ prog + " --help\n" +
	"       "
	+ prog + " --version";
    const char optstring[] = "f:";
    const struct option long_options[] = {
	{"help",    	 0, 0, 'h'},
	{"version", 	 0, 0, 'v'},
	{0, 0, 0, 0}
    };

    std::vector<std::string> qpaths;
    std::string spath;

    int ch;
    while ((ch = getopt_long(argc, argv,
			     optstring, &long_options[0], 0)) != -1) {
	switch(ch) {
	case 'f':
	    qpaths.push_back(optarg);
	    break;
	case 'h':
	    std::cout << usage << '\n';
	    return 0;
	case 'v':
	    std::cout << "siggen 2.0\n"
		      << "Copyright (c) 2006 - 2024 Jörgen Grahn\n";
	    return 0;
	    break;
	case ':':
	case '?':
	    std::cerr << usage << '\n';
	    return 1;
	    break;
	default:
	    break;
	}
    }

    if (optind + 1 == argc) spath = argv[optind];

    if (qpaths.empty() || spath.empty()) {
	std::cerr << "error: required argument missing\n"
		  << usage << '\n';
	return 1;
    }

    const std::string fs = fortune(std::cerr, qpaths);

    std::ifstream f {spath};
    if (!f) {
	std::cerr << "error: cannot open " << spath
		  << "for writing: " << std::strerror(errno) << '\n';
	return 1;
    }

    const auto src = read(f);
    std::cout << render(src, fs);

    return 0;
}
