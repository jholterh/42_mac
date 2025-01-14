#include "solong.h"

int	check_file_end(char *str)
{
	int	file_end_len;
	int	str_len;

	file_end_len = strlen(".ber");
	str_len = strlen(str);
	if (str_len < file_end_len)
	{
		printf("Wrong file type as input\n");
		return (1);
	}
	if (strcmp(str + str_len - file_end_len, ".ber"))
	{
		printf("Wrong file type as input\n");
		return (1);
	}
	return (0);
}