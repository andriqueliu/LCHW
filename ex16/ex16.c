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
	// Note!!! malloc syntax... usage...
	// ...
	struct Person *who = malloc(sizeof(struct Person));
	// Note: You are asserting that the *POINTER* is not NULL. 
	assert(who != NULL);

	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who)
{
	assert(who != NULL);

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
}
