#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFF_SIZE 4096

int	read_file(char *str)
{
	int	fd;
	int	n;
	int	len;
	char	*buff;
	int	i;

	buff = (char*)malloc(BUFF_SIZE * sizeof(char));
	len = 0;
	fd = open(str, O_RDONLY);
	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
		len = len + i;
	close(fd);
	free(buff);
	return (len);
}
