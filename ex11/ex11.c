#include <stdio.h>

int main()
{
	int numbers[4] = { 0 };
	// char name[4] = { 'a', 'b', 'c', 'd', 'e' }; // This results in weird errors
	char name[4] = { 'a' };

	// Print them out raw
	printf("numbers: %d %d %d %d\n",
		    numbers[0], numbers[1], numbers[2], numbers[3]);

	printf("name each: %c %c %c %c\n",
		    name[0], name[1], name[2], name[3]);

	// Note: Raw... unreliable, sometimes nonsense data
	// To be safe, just initialize your variables

	printf("name: %s\n", name);

	// Set up the numbers
	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;

	// Set up the name
	name[0] = 'Z';
	name[1] = 'e';
	name[2] = 'd';
	// name[3] = '\0';
	name[3] = 'B';
	// name[4] = 'A'; // This doesn't result in an error?

	// Note: without a null pointer, this could be bad... machine dependent?

	// Then print them out initialized
	printf("numbers: %d %d %d %d\n",
		    numbers[0], numbers[1], numbers[2], numbers[3]);

	printf("name each: %c %c %c %c\n",
		    name[0], name[1], name[2], name[3]);

	// Another way to use name
	char *another = "Zed";

	printf("another: %s\n", another);

	printf("another each: %c %c %c %c\n",
		    another[0], another[1], another[2], another[3]);
}
