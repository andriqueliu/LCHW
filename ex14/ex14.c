#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);

// Note: for the first argument, it'll use "ex" (14 is not made up of letters!)
// Also note, the inputs this function takes in... they're just
// copies that are being made!
void print_arguments(int argc, char *argv[])
{
	int i = 0;

	for (i = 0; i < argc; i++) {
		print_letters(argv[i]);
	}
}

void print_letters(char arg[])
{
	int i = 0;

	// Rewrite so that you don't need to rely on the null terminator
	// for (i = 0; arg[i] != '\0'; i++) {
	int length = strlen(arg);
	for (i = 0; i < length; i++) {
		char ch = arg[i];

		// if (can_print_it(ch)) {
		// 	printf("'%c' == %d ", ch, ch);
		// }

		// EC: Rewrite so that you don't need can_print_it
		// if (isalpha((int) ch) || isblank((int) ch)) {
		// if (isalpha((int) ch)) {
		// EC: Rewrite ^ to print out numbers and digits!
		// Note: isblank only comes in handy when an arg. is bounded by "" and has a space
		// Otherwise, the spaces just separate the arguments.
		if (isalnum((int) ch) || isblank((int) ch)) {
			printf("'%c' == %d ", ch, ch);
		}
	}

	printf("\n");
}

int can_print_it(char ch)
{
	return isalpha((int) ch) || isblank((int)ch);
}

int main(int argc, char *argv[])
{
	print_arguments(argc, argv);

	// Add 1 to number of args
	// Results in a seg fault
	// print_arguments(argc + 1, argv); // Note: how an array is placed as an input

	return 0;
}
