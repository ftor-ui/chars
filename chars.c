#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned int int_to_string(const char* string);

void print_rand_chars(const unsigned int count);

int main(const int argc, const char* argv[])
{
	if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
	{
		printf("Use the: chars [count_of_chars]");
		return 0;
	}
	unsigned int count = int_to_string(argv[1]);
	print_rand_chars(count);
	return 0;
}

unsigned int int_to_string(const char* string)
{
	unsigned int integer = 0; // remove the trash

	// Find top `i` of string[i]
	int count = 0;
	for (int i = 0; string[i] != 0; ++i)
		count++;

	// Convert string to integer
	int step = 1; // step is a digit
	for (int i = count - 1; i >= 0; --i)
	{
		integer += step * (string[i] - 48); // 48 is a error ASCII table
		step *= 10;
	}

	return integer;
}

void print_rand_chars(const unsigned int count)
{
	srand(time(NULL));
	for (int i = 0; i < count; i++)
		printf("%c", rand() % 93 + 34); // 33 is a error ASCII table
}
