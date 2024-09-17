//SPDX-License-Identifier:         MIT

#include "type.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "strops.h"

using namespace eis;

std::pair<std::valarray<fvalue>, std::valarray<fvalue>> eis::eisToValarrays(const std::vector<eis::DataPoint>& data)
{
	std::valarray<fvalue> real(data.size());
	std::valarray<fvalue> imag(data.size());

	for(size_t i = 0; i < data.size(); ++i)
	{
		real[i] = data[i].im.real();
		imag[i] = data[i].im.imag();
	}

	return {real, imag};
}

void eis::Range::print() const
{
	std::cout<<"Range "<<start<<'-'<<end<<' '<<count<<" steps"<<(log ? " Log" : "");
}

std::vector<fvalue> eis::Range::getRangeVector() const
{
	std::vector<fvalue> out(count, 0);
	for(size_t i = 0; i < count; ++i)
		out[i] = at(i);
	return out;
}

eis::Range eis::Range::fromString(std::string str, size_t count)
{
	bool log = false;
	std::vector<std::string> tokens = tokenize(str, '~');
	eis::Range out;

	if(str.back() == 'l' || str.back() == 'L')
	{
		log = true;
		str.pop_back();
	}

	try
	{
		if(tokens.size() == 1)
		{
			out = Range(std::stod(tokens[0]), std::stod(tokens[0]), 1, log);
		}
		else
		{
			out = Range(std::stod(tokens[0]), std::stod(tokens[1]), count, log);
			if(tokens.size() > 2)
				throw std::invalid_argument("");
		}

	}
	catch(const std::invalid_argument& ia)
	{
		throw std::invalid_argument("invalid parameter \""+ str + "\"");
	}

	return out;
}

std::vector<Range> eis::Range::rangesFromParamString(const std::string& paramStr, size_t count)
{
	std::vector<std::string> tokens = tokenize(paramStr, ',');

	std::vector<Range> ranges(tokens.size());
	for(size_t i = 0; i < tokens.size(); ++i)
	{
		std::string& token = tokens[i];
		try
		{
			ranges[i] = fromString(token, count);
		}
		catch(const std::invalid_argument& ia)
		{
			throw std::invalid_argument("invalid parameter string \"{"+ paramStr + "}\"");
		}
	}
	return ranges;
}

std::string eis::Range::getString() const
{
	std::stringstream ss;

	ss<<start;
	if(count > 1)
	{
		ss<<'~'<<end;
		if(log)
			ss<<'L';
	}

	return ss.str();
}

bool eis::Range::isSane() const
{
	if(log && (start == 0 || end == 0))
		return false;
	if(end < start)
		return false;
	return true;
}


std::ostream &operator<<(std::ostream &s, Range const& range)
{
	s<<range.getString();
	return s;
}

const VersionFixed getVersion()
{
	return eis_get_version();
}

std::ostream &operator<<(std::ostream &s, DataPoint const& dp)
{
	s<<dp.im;
	return s;
}
