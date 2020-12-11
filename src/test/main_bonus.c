#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../get_next_line_bonus.h"

void gnl(int fd, int r, char * s)
{
	static int i = 1;
	char * line = NULL;
	int gnlReturn = get_next_line(fd, &line);
	printf("%d - Return:%d, %d, String:%s, %s, %p, %p\n", i++, r, gnlReturn, s, line, s, line);
//	check(r == gnlReturn && s == NULL ? line == NULL : !strcmp(line, s));
//	if (s != NULL)
//		mcheck(line, strlen(s) + 1);
	if (gnlReturn != -1)
		free(line);
}

int test3() {
	int             fd;
	int             i;
	int             j;
	char    		*line = 0;
//	char			*lineadress[66];

	j = 1;
	printf("\n==========================================\n");
	printf("============= TEST 7 : Marge =============\n");
	printf("==========================================\n\n");

	int fd2;

	if (!(fd = open("/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/files_gnl/mix_marge1", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	if (!(fd2 = open("/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/files_gnl/mix_marge2", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while (j < 8)
	{
		if ((i = get_next_line(fd, &line)) > 0)
			printf("1 %d, %s\n", j, line);
		free(line);
		j++;
	}
	while (j < 13)
	{
		if ((i = get_next_line(fd2, &line)) > 0)
			printf("%s\n", line);
		free(line);
		j++;
	}
	if ((i = get_next_line(fd, &line)) > 0)
		printf("2 %d, %s\n", j, line);
	free(line);
	j++;
	if ((i = get_next_line(fd2, &line)) > 0)
		printf("3 %d, %s\n", j, line);
	free(line);
	j++;
	if ((i = get_next_line(fd2, &line)) > 0)
		printf("4 %d, %s\n", j, line);
	free(line);
	j++;
	if ((i = get_next_line(fd, &line)) > 0)
		printf("5 %d, %s\n", j, line);
	free(line);
	j++;
	if ((i = get_next_line(fd2, &line)) > 0)
		printf("6 %d, %s\n", j, line);
	free(line);
	j++;
	if ((i = get_next_line(fd, &line)) > 0)
		printf("7 %d, %s\n", j, line);
	free(line);
	j++;
	while (j < 23)
	{
		if ((i = get_next_line(fd2, &line)) > 0)
			printf("8 %d, %s\n", j, line);
		free(line);
		j++;
	}
	get_next_line(fd2, &line);
	printf("9 %d, %s\n", j, line);
	free(line);
	j++;
	while (j < 25)
	{
		if ((i = get_next_line(fd, &line)) > 0)
			printf("a %d, %s\n", j, line);
		free(line);
		j++;
	}
	get_next_line(fd, &line);
	printf("b %d, %s\n", j, line);
	free(line);
	close(fd);
	close(fd2);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 25)
		printf("\nRight number of lines\n");
	else if (j != 25)
		printf("\nNot Good - Wrong Number Of Lines\n");
return (0);
}

int		main_()
{
	int fd[4];

	fd[0] = open("/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line_bonus/files/41_with_nl", O_RDWR);
	fd[1] = open("/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line_bonus/files/42_with_nl", O_RDWR);
	fd[2] = open("/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line_bonus/files/43_with_nl", O_RDWR);
	fd[3] = open("/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line_bonus/files/nl", O_RDWR);

	/* 1 */ gnl(1000, -1, NULL);
	/* 2 */ gnl(fd[0], 1, "0123456789012345678901234567890123456789");
	/* 3 */ gnl(1001, -1, NULL);
	/* 4 */ gnl(fd[1], 1, "01234567890123456789012345678901234567890");
	/* 5 */ gnl(1002, -1, NULL);
	/* 6 */ gnl(fd[2], 1, "012345678901234567890123456789012345678901");

	/* 7 */ gnl(1003, -1, NULL);
	/* 8 */ gnl(fd[0], 0, "0");

	/* 9 */ gnl(1004, -1, NULL);
	/* 10 */ gnl(fd[1], 0, "1");

	/* 11 */ gnl(1005, -1, NULL);
	/* 12 */ gnl(fd[2], 0, "2");

	/* 13 */ gnl(1006, -1, NULL);
	/* 14 */ gnl(fd[3], 1, "");
	/* 15 */ gnl(1007, -1, NULL);
	/* 16 */ gnl(fd[3], 0, "");
	  while(1) ;


	return (0);
}
