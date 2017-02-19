// Note: %s expects a char *

#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;

	// Go through each string in argv...
	// Why is argv[0] being skipped?
	for (i = 1; i < argc; i++) {
		printf("arg %d: %s\n", i, argv[i]);
	}

	// Let's make our own array of strings
	// ??? An array of strings... sth *plox[]
	// This is making an array of four pointers to strings!
	char *states[] = {
		"California", "Oregon",
		"Washington", "Texas"
	};

	printf("%s\n", states[0]);

	// This actually works!
	// states[0] is the first char *
	states[0] = "Hello";

	// Note: Going OOB prints garbage
	// int num_states = 4;
	int num_states;
	// Try changing num states in the for loop

	for (i = 0, num_states = 4; i < num_states; i++) {
		printf("state %d: %s\n", i, states[i]);
	}

	// This does work... 
	argv[0] = "Hi";
	printf("%s\n", argv[0]);

	// This also works???
	if (argc > 1) {
		states[0] = argv[1];
	}
	printf("%s\n", states[0]);

	return 0;
}
