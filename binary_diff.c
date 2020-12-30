#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void error_handler()
{
	perror(strerror(errno));
	exit(0);
}

int binary_diff(char *file1, char *file2, size_t buf_size)
{
	FILE *f1;
	FILE *f2;
	char *buf1;
	char *buf2;
	size_t f1_rd_size;
	size_t f2_rd_size;
	int diff;

	if (!(f1 = fopen(file1, "r")))
		error_handler();
	if (!(f2 = fopen(file2, "r")))
	{
		fclose(f1);
		error_handler();
	}
	if (!(buf1 = (char *)malloc(sizeof(char) * (buf_size))))
	{
		fclose(f1);
		fclose(f2);
		error_handler();
	}
	if (!(buf2 = (char *)malloc(sizeof(char) * (buf_size))))
	{
		fclose(f1);
		fclose(f2);
		free(buf1);
		error_handler();
	}
	diff = 0;
	while (!feof(f1) || !feof(f2))
	{
		f1_rd_size = fread(buf1, sizeof(char), buf_size, f1);
		f2_rd_size = fread(buf2, sizeof(char), buf_size, f2);
		if (ferror(f1))
		{
			free(buf1);
			free(buf2);
			fclose(f1);
			fclose(f2);
			error_handler();
		}
		if (ferror(f2))
		{
			free(buf1);
			free(buf2);
			fclose(f1);
			fclose(f2);
			error_handler();
		}
		diff = memcmp(buf1, buf2, f1_rd_size <= f2_rd_size ? f1_rd_size : f2_rd_size);
		if (f1_rd_size < f2_rd_size)
			diff = -buf2[f1_rd_size];
		if (f1_rd_size > f2_rd_size)
			diff = buf1[f2_rd_size];
		if (diff != 0)
			break;
	}
	free(buf1);
	free(buf2);
	fclose(f1);
	fclose(f2);
	return (diff);
}
