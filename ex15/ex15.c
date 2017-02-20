// Note: again, the syntax is identical... plox[i] == *(plox + i)

// Thought: What does a pointer do? It's just a variable that stores a variable's address
// in memory. So it's pointing to its location, essentially. 

/*
Pointer notes:

In many cases, you'll probably want to use an array instead.
But, sometimes you have to use a pointer!

If you need a chunk of memory and have to work with it, pointers come in handy...

They're good for:
Working with chunks of memory like structs
Passing pointers instead of huge pieces of data the pointers point to
Take the address of a function and use it as a dynamic callback (??? Related to interrupts?)
...?

So, use pointers when you absolutely need them, or need them for performance boosts, etc.

Also note, you can use pointers and arrays kinda similarly.
You can use [] with a pointer, you can also use pointer arithmetic with an array.
*/
#include <stdio.h>

int main(int argc, char *argv[])
{
	// Create two arrays we care about
	// Note: so, ages on its own is just an address of where its elements start!
	// AKA, it's the address of the array's first entry!
	int ages[] = { 23, 43, 12, 89, 2 };
	char *names[] = {
		"Alan", "Frank",
		"Mary", "John", "Lisa"
	};

	// Safely get the size of ages
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	// First way using indexing
	// for (i = 0; i < count; i++) {
	// 	printf("%s has %d years alive.\n", names[i], *(ages + i)); // Using pointer arith. with an array
	// }

	// Break: Rewrite loops so that they start at the END of arrays and then go back
	// It works!
	i = count - 1;
	while (i > -1) {
		printf("%s has %d years alive.\n", names[i], ages[i]);
		i--;
	}

	printf("---\n");

	// Set up the pointers to the start of arrays
	int *cur_age = ages;

	// Break: Try to make cur_age point at names
	// Cast using int * because names contains char pointers
	// int *cur_age = (int *) names;

	// Note: names is two-dimensional...
	// This means that you need a pointer to a char pointer!
	char **cur_name = names;

	// Second way using pointers
	for (i = 0; i < count; i++) {
		printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i)); // Note: Deref name once, you get a char pointer!
	}

	printf("---\n");

	// Third way, pointers are just arrays
	for (i = 0; i < count; i++) {
		printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
	}

	printf("---\n");

	// Fourth way with pointers in a stupid complex way
	// Note: (cur_age - ages)... an address - another address! And the former address is getting incremented
	for (cur_name = names, cur_age = ages;
		(cur_age - ages) < count; cur_name++, cur_age++) {
		printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	}

	// BreaK: Try getting the math wrong in weird ways
	// Stops one entry too early
	// for (cur_name = names, cur_age = ages;
	// 	(cur_age + 1 - ages) < count; cur_name++, cur_age++) {
	// 	printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	// }

	// Seg fault from printing %s with **cur_name
	// for (cur_name = names, cur_age = ages;
	// 	(cur_age - ages) < count; cur_name++, cur_age++) {
	// 	printf("%s lived %d years so far.\n", **cur_name, *cur_age);
	// }
}
