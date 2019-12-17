//
// Created by User on 15.12.2019.
//

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

void	getInput(uint8_t &stones, uint8_t &heaps)
{
	unsigned long	num;
	std::vector<std::string>	numbers;
	std::string line;

	std::cout << "Enter number of stones and heaps (separated by space):\n";
	std::getline(std::cin, line, '\n');

	numbers = split(line, ' ');
	if (numbers.size() == 2)
	{
		num = strtoul(numbers.at(0).c_str(), nullptr, 10);
		if (num < 10 || num > 100)
			throw "The stones count must be between 10 and 100 included";
		stones = static_cast<uint8_t>(num);
		num = strtoul(numbers.at(1).c_str(), nullptr, 10);
		if (num < 1 || num > stones)
			throw "The heaps count must be between 1 and NUM_OF_STONES included";
		heaps = static_cast<uint8_t>(num);
	}
	else
		throw "You have to type 2 arguments: stones and heaps";
}

int main(void)
{
	uint8_t			stones;
	uint8_t 		heaps;
	uint8_t 		divisionResult;
	double_t 		res = 1;

	try
	{
		getInput(stones, heaps);
	} catch (const char *s) {
		std::cout << s << std::endl;
		return 1;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	while (heaps)
	{
		divisionResult = stones / heaps;
		if (stones % heaps == 0)
		{
			res *=pow(divisionResult, heaps);
			break;
		}
		else
		{
			res *= divisionResult;
			stones -= divisionResult;
			heaps--;
		}
	}
	std::cout << res << std::endl;

	return 0;
}