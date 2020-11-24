#include <stdio.h>

int binary_diff(char *file1, char *file2, size_t buf_size);

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage : %s file1 file2\n", argv[0]);
		return 0;
	}
	if (binary_diff(argv[1], argv[2], 1024) == 0)
		printf("AC\n");
	else
		printf("WA\n");
	return 0;
}
