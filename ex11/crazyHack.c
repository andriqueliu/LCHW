// Treat an array of chars (name array) as just a whole integer
// So an integer is 8 bytes long, but so is 4 chars in an array...

// So, just add everything?

#include <stdio.h>

int power(int value, int power);

int main()
{
	// First, assume that it goes from LSB to MSB, left to right
	char name[4] = { 'a', 'b', 'c', 'd' };
	int value;

	value = 0;

	for (int i = 0; i < 4; i++) {
		value = value + name[i];
	}

	printf("Result: %d\n", value);
}

int power(int value, int power)
{
	int result;

	if (power == 0) {
		return 1;
	} else {
		for (int i = 0; i < power; i++) {
			result = result * value;
		}
		return value;
	}
}
