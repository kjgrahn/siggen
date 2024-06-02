/* -*- c++ -*-
 *
 * Copyright (c) 2024 Jörgen Grahn
 * All rights reserved.
 */
#ifndef SIGGEN_FORTUNE_H
#define SIGGEN_FORTUNE_H

#include <iosfwd>
#include <string>
#include <vector>

std::string fortune(std::ostream& err,
		    const std::vector<std::string>& paths);

#endif
