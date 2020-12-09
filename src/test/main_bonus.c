#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../get_next_line_bonus.h"

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
		return (1);
	return (0);
}

void test1() {
	char	*str = "";
	char	*file1 = "/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/toto.txt";
	char	*file2 = "/Users/yde-mont/Desktop/ECLIPSE/workspace/LIBFT/get_next_line/numbers.dict.txt";

	int		fd1 = open(file1, O_RDONLY);
	int		fd2 = open(file2, O_RDONLY);
	printf("Buffer:%d\n", BUFFER_SIZE);
	int i = 0;
	while (1 == get_next_line(i%2 ? fd1 : fd2, &str))
		fprintf(stderr, "File: %d, line %d:\t\t%s.\n", (i % 2) ? fd1 : fd2, i++, str);
	fprintf(stderr, "File: %d, line %d:\t\t%s.\n", i%2 ? fd2 : fd1, i, str);
	close(fd1);
	close(fd2);
}

void test2() {
	t_segment *s1 = malloc(sizeof(t_segment));
	t_segment *s2 = malloc(sizeof(t_segment));

	printf("%p, %p, %ld, %ld\n", s1, s2, s2 - s1, ((long) s2) - ((long) s1));
}
int		main()
{
	test1();

	return (0);
}
