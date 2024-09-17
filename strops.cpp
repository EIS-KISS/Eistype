//SPDX-License-Identifier:         MIT

#include "strops.h"
#include <algorithm>
#include <cassert>

namespace eis
{

std::vector<std::string> tokenize(const std::string& str, const char delim, const char ignBracketStart, const char ignBracketEnd, const char escapeChar)
{
	std::vector<std::string> tokens;

	std::string token;
	size_t bracketCounter = 0;
	for(size_t i = 0; i < str.size(); ++i)
	{
		if(str[i] == delim && bracketCounter == 0 && (i == 0 || str[i-1] != escapeChar))
		{
			tokens.push_back(token);
			token.clear();
		}
		else
		{
			token.push_back(str[i]);
		}

		if(ignBracketStart == str[i])
			++bracketCounter;
		else if(ignBracketEnd == str[i])
			--bracketCounter;
	}
	if(bracketCounter == 0)
		tokens.push_back(token);
	return tokens;
}

std::vector<std::string> tokenizeBinaryIgnore(const std::string& str, const char delim, const char ignoreBraket, const char escapeChar)
{
	std::vector<std::string> tokens;

	std::string token;
	bool inBaracket = false;
	for(size_t i = 0; i < str.size(); ++i)
	{
		if(str[i] == delim && !inBaracket && (i == 0 || str[i-1] != escapeChar))
		{
			tokens.push_back(token);
			token.clear();
		}
		else
		{
			token.push_back(str[i]);
		}

		if(ignoreBraket == str[i])
			inBaracket = !inBaracket;
	}
	if(!inBaracket)
		tokens.push_back(token);
	return tokens;
}

void stripQuotes(std::string& in)
{
	in.erase(std::remove_if(in.begin(), in.end(), [](unsigned char ch){return ch == '"' || ch == '\'';}), in.end());
	if(in[in.size()-1] == '"' || in[in.size()-1] == '\'')
		in.pop_back();
}

std::string stripWhitespace(const std::string& in)
{
	std::string out;
	out.reserve(in.size());
	for(char ch : in)
	{
		if(ch <= 32 || ch == 127)
			continue;
		out.push_back(ch);
	}
	return out;
}

}
