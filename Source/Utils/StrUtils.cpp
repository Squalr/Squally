#include "StrUtils.h"

std::vector<std::string>* StrUtils::tokenize(std::string str, std::string delimiters)
{
	std::vector<std::string>* tokens = new std::vector<std::string>();

	// Skip delimiters at beginning
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// Find first non-delimiter
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	// Insert leading delimiter token
	if (pos != std::string::npos && lastPos != std::string::npos && lastPos > 0)
	{
		tokens->push_back(str.substr(lastPos, pos - lastPos));
	}

	while (pos != std::string::npos || pos != lastPos)
	{
		// Found a standard token, add it to the vector
		tokens->push_back(str.substr(lastPos, pos - lastPos));

		// Skip delimiters
		lastPos = str.find_first_not_of(delimiters, pos);

		// Insert delimiter token
		if (lastPos != std::string::npos && pos != std::string::npos)
		{
			tokens->push_back(str.substr(pos, lastPos - pos));
		}

		// Find next non-delimiter
		pos = str.find_first_of(delimiters, lastPos);
	}

	// Insert trailing delimter token
	pos = str.find_last_of(delimiters);

	if (pos != std::string::npos && str.find_first_not_of(delimiters, pos) == std::string::npos)
	{
		// Adjust start position to start of trailing delimiter span
		pos = str.find_last_not_of(delimiters, pos);

		if (pos == std::string::npos)
		{
			pos = 0;
		}
		else
		{
			pos += 1;
		}

		tokens->push_back(str.substr(pos, str.size() - pos));
	}

	return tokens;
}

std::string StrUtils::replaceAll(std::string str, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;

	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}

	return str;
}
