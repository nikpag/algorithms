#include "set.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	SimpleSet set;
	set_init(&set);
	set_add(&set, "orange");
	set_add(&set, "blue");
	set_add(&set, "red");
	set_add(&set, "green");
	set_add(&set, "yellow");

	if (set_contains(&set, "yellow") == SET_TRUE) {
		printf("Set contains 'yellow'!\n");
	}
	else {
		printf("Set does not contains 'yellow'!\n");
	}

	if (set_contains(&set, "purple") == SET_TRUE) {
		printf("Set contains 'purple'!\n");
	}
	else {
		printf("Set does not contains 'purple'!\n");
	}

	set_destroy(&set);
}
