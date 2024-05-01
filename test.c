#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include <errno.h>
#include <stdarg.h>
#include <wchar.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct s_list
{
	char *buffer;
	struct s_list *next_list;
}	t_list;

int main()
{
	t_list	*list1;
	t_list	*list2;

	list1 = malloc(sizeof(t_list));
	if (!list1)
		return (0);
	list2 = malloc(sizeof(t_list));
	if (!list2)
		return (0);

	list1->buffer = "Hello";
	list1->next_list = list2;
	list2->buffer = "42";
	list2->next_list = NULL;

	printf("List 1: %s\n", list1->buffer);
	printf("List 2: %s\n", list2->buffer);

	free(list1);
	free(list2);
	return (1);
}