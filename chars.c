#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>

unsigned int string_to_int(const char* string);

void print_rand_chars(int unsigned const count, int unsigned const seed, int unsigned const buffer);

int main(const int argc, const char* argv[])
{
	if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
	{
		printf("Use the: chars [-opt][variable]\n\n"
			   "[MUST_HAVE]:\n"
			   "\t-c\tCOUNT   Set count of chars\n"
			   "[OPTIONAL]:\n"
			   "\t-s\tSEED    Set seed for random chars (default use the current time)\n"
			   "\t-b\tBUFFER  Set size of buffer for contain chars (default use the 4096 bytes)\n");
		return 0;
	}
	
	int mh_variables = 0; // logical variable mean that the must have (mh) variables have been set
	
	int unsigned count;
	int unsigned seed = time(NULL);
	int unsigned size_buffer = 4096;
	
	for (int i = 1; i < argc - 1; i+=2) {
		if (strcmp(argv[i], "-c") == 0) {
			count = string_to_int(argv[i + 1]);
			mh_variables = 1;
		}
		else if (strcmp(argv[i], "-s") == 0) 
			seed = string_to_int(argv[i + 1]);
		else if (strcmp(argv[i], "-b") == 0)
			size_buffer = string_to_int(argv[i + 1]);
	}
	
	print_rand_chars(count, seed, size_buffer);
	return 0;
}

unsigned int string_to_int(const char* string)
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

void print_rand_chars(int unsigned const count, int unsigned const seed, int unsigned const size_buffer)
{
	srand(seed);
	char *buffer = (char *)malloc(sizeof(char) * size_buffer);
	for (int unsigned i = 0; i < count; i++) {
		*(buffer + i % size_buffer) = (char)(rand() % 93 + 34);
		if ((i + 1) / size_buffer > 0 && (i + 1) % size_buffer == 0)
			write(STDOUT_FILENO, buffer, size_buffer);
	}
	if (count < size_buffer)
		write(STDOUT_FILENO, buffer, count);
	else if (count / size_buffer != 0)
		write(STDOUT_FILENO, buffer, count % size_buffer);
}
