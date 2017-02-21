/*
Lesson: make a struct, point a ptr at it, use that to make sense of internal memory
structures...
Then, get to constructing these structures using malloc
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
	// Note!!! the syntax, and also the usage:
	// malloc asks the OS for a raw chunk of memory, sized accordingly using sizeof
	struct Person *who = malloc(sizeof(struct Person));
	// Note: You are asserting that the *POINTER* is not NULL.
	// This is just making sure that the pointer isn't unset or invalid.
	assert(who != NULL);

	// Note: strdup returns a pointer to a string which is which is duplicated from the input
	// into strdup. The memory for the new string is allocated using malloc!!!
	// Note: strdup is used to duplicate the string, making sure that this structure OWNS it.
	// strdup is doing something similar to malloc, and needs to be freed. 
	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who)
{
	assert(who != NULL);

	// Free the memory space allocated previously
	// Both for the duplicated name and the entire struct
	// Break: forget to free the duplicated names (see below for notes)
	free(who->name);
	free(who);
}

void Person_print(struct Person *who)
{
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
	// Make two people structs
	// Note that you are creating pointers to structs here...
	// But the function Person_create is allocating memory for those structs.
	struct Person *joe = Person_create("Joe Alex", 32, 64, 140);

	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	// Print them out and where they are in memory
	printf("Joe is at memory location %p\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p\n", frank);
	Person_print(frank);

	// Make everyone age 20 years and then print them again
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	frank->age += 20;
	frank->weight += 20;
	// Break: pass NULL into print
	// Results in a seg fault
	Person_print(frank);

	// Destroy them both so we clean up
	// Break: pass NULL into a destroy argument
	// Results in assertion error
	Person_destroy(joe);
	// Person_destroy(NULL);
	// Break: Forget to call destroy at the end... What options needed to report memory leaks?
	// Need Valgrind or similar to report memory leaks at compile time
	Person_destroy(frank);

	return 0;
}
