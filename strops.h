//SPDX-License-Identifier:         MIT

#pragma once
#include <string>
#include <vector>

namespace eis
{

std::vector<std::string> tokenize(const std::string& str, const char delim = ' ', const char ignBracketStart = '\0',
								  const char ignBracketEnd = '\0', const char escapeChar = '\0');
std::vector<std::string> tokenizeBinaryIgnore(const std::string& str, const char delim, const char ignoreBraket = '\0',
											  const char escapeChar = '\0');

std::string stripWhitespace(const std::string& in);

void stripQuotes(std::string& in);

}
