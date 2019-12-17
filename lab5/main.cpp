//
// Created by User on 15.12.2019.
//

#include <string>
#include <iostream>

#define NUM_DIGITS 7
#define ROME_SMALL "ivxlcrm"
#define ROME_BIG "IVXLCRM"
#define MAX_NUM 3056

enum e_state 	{WORK, END, LESS, EQUAL, GREAT};

enum e_state	get_general_state(int8_t num);
enum e_state	get_general_state(int8_t num);
enum e_state	get_work_state(int8_t first_num, int8_t second_num);
void			NaN_error();
int8_t			get_num();
int8_t			odd_work(int8_t n, int8_t &seil, uint16_t &res);
int8_t			even_work(int8_t n, int8_t &seil, uint16_t &res);


uint16_t 		nums[NUM_DIGITS] = {1, 5, 10, 50, 100, 500, 1000};
const char		*g_line;

int main()
{
	std::string	line;
	uint16_t	res = 0;
	int8_t		upper = 6;
	int8_t		n;
	bool		stop = false;

	do
	{
		std::cout << "Enter a rome number between 1 and " << MAX_NUM << ":\n";
		std::getline(std::cin, line, '\n');
	} while (line.empty());

	g_line = line.c_str();
	n = get_num();
	while (!stop)
	{
		switch (get_general_state(n))
		{
			case WORK:
				if (n % 2 == 0)
					n = even_work(n, upper, res);
				else
					n = odd_work(n, upper, res);
				break;
			case END:
				stop = true;
				break;
		}
	}

	if (res > MAX_NUM)
		std::cout << "The number is too large" << std::endl;
	else
		std::cout << res << std::endl;
	return (0);
}

enum e_state	get_general_state(int8_t num)
{
	if (num == NUM_DIGITS)
		return END;
	else
		return WORK;
}

enum e_state	get_work_state(int8_t first_num, int8_t second_num)
{
	if (second_num == NUM_DIGITS)
		return END;
	else if (second_num < first_num)
		return LESS;
	else if (second_num > first_num)
		return GREAT;
	else
		return EQUAL;
}

void	NaN_error()
{
	std::cout << "NaN" << std::endl;
	exit(1);
}

int8_t get_num()
{
	int8_t		i = 0;
	static int	iter = 0;

	if (g_line[iter] == '\0')
		return NUM_DIGITS;

	while (i < NUM_DIGITS)
	{
		if (g_line[iter] == ROME_SMALL[i] || g_line[iter] == ROME_BIG[i]) {
			iter++;
			return i;
		}
		i++;
	}
	NaN_error();
}



int8_t	odd_work(int8_t n, int8_t &seil, uint16_t &res)
{
	int8_t	next_num;

	if (n > seil)
		NaN_error();

	next_num = get_num();

	if (n - 1 < seil)
		seil = n - 1;

	switch(get_work_state(n, next_num))
	{
		case LESS:
		case END:
			res += nums[n];
			break;
		case EQUAL:
		case GREAT:
			NaN_error();
			break;
	}
	return next_num;
}

int8_t	even_work(int8_t n, int8_t &seil, uint16_t &res)
{
	static int8_t	count = 1;
	int8_t 			next_num;

	next_num = get_num();
	if (n + 2 < seil)
		seil = n + 2;

	switch(get_work_state(n, next_num))
	{
		case LESS:
		case END:
			if (n <= seil)
				res += nums[n] * count;
			else
				NaN_error();
			break;
		case GREAT:
			if (next_num <= seil && count == 1)
			{
				res += nums[next_num] - nums[n];
				next_num = get_num();
				seil = n - 1;
			}
			else
				NaN_error();
			break;
		case EQUAL:
			seil = n;
			count++;
			if (count <= 3)
				next_num = even_work(next_num, seil, res);
			else
				NaN_error();
			break;
	}
	count = 1;
	return next_num;
}