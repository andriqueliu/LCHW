// Note!!! 
// plox[n] is the same as *(plox + n)

// Note: sizeof returns size in BYTES

#include <stdio.h>

int main()
{
	// Note: the array DOES NOT have a width assigned to it...
	// The way this works is... C notes the desired size you want, so it just
	// does it for you
	int areas[] = { 10, 12, 13, 14, 20 };
	char name[] = "Zed";
	// The full_name method and the name methods are identical, behaviorally
	// char full_name[] = {

	// }

	printf("The size of an int: %ld\n", sizeof(int));
	printf("The size of areas (int[]): %ld\n", sizeof(areas));
	printf("The number of ints in areas: %ld\n",
		    sizeof(areas) / sizeof(int));
	printf("The first area is %d, the second %d\n", areas[0], areas[1]);

	printf("name: %s\n", name);

	// Break name messing w/ null char
	// Note: C lets you mess around w/ memory... you can change up stuff outside
	// of this array... like access name[1000]
	// Note: If you assign the null char earlier, printf keeps printing until it encounters
	// the null char
	// name[3] = '\0';
	// printf("name: %s\n", name);
}
