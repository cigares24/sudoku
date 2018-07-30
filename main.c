#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"
#include <fcntl.h>

int	**g_grid;

int	get_size(char *str)
{
	int	n;
	int	res;

	n = 0;
	res = 0;
	while (str[n])
	{
		if (str[n] == '\n')
			res++;
		n++;
	}
	return (res);
}

int	check_grid(char *str)
{
	int	n;
	int	len;
	int	li;
	int	i;

	n = 0;
	li = 0;
	while (str[n] != '\n')
		n++;
	len = n;
	n = 0;
	i = -1;
	while (str[n])
	{
		i++;
		if (str[n] == '\n')
		{
			if (i != len)
				return (0);
			i = -1;
		}
		n++;
	}
	n = 0;
	while (str[n])
	{
		if (str[n] == '\n')
			li++;
		n++;
	}
	if (li != len)
		return (0);
	return (1);
}

void	**grid_convert(char *str)
{
	int	n;
	int	i;
	int	k;

	n = 0;
	i = 0;
	while (str[n] != '\0')
	{
		if (str[n] == '\n' || n == 0)
		{
			if (n != 0)
			{
				i++;
				n++;
			}
			if ((g_grid[i] = (int*)malloc(get_size(str) * sizeof(int))) <= 0)
				return (0);
			k = 0;
		}
		if (str[n] >= 48 && str[n] <= 57)
			g_grid[i][k] = str[n] - 48;
		else if (str[n] != '\n')
			g_grid[i][k] = 0;
		k++;
		n++;
	}
}

void	print_grid(int **grid, int len)
{
	int	n;
	int	i;

	i = 0;
	while (i < len)
	{
		n = 0;
		while (n < len)
		{
			ft_putchar(grid[i][n] + 48);
			ft_putchar(' ');
			if ((n + 1) % 3 == 0 && n < len - 1)
				write(1, "| ", 2);
			n++;
		}
		ft_putchar('\n');
		if ((i + 1) % 3 == 0 && i != len - 1)
		{
			n = n + len % 3 + 1;
			while (--n >= 0)
				write(1, "- ", 2);
			ft_putchar('-');
			ft_putchar('\n');
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	n;
	int	len;
	char	*sudoku;
	int	fd;
	int	verif;

	if (argc == 1)
		return (0);
	n = 0;
	while (argv[++n])
	{
		len = read_file(argv[n]);
		fd = open(argv[n], O_RDWR);
		if ((sudoku = (char*)malloc(len * sizeof(char))) <= 0)
			return (0);
		read(fd, sudoku, len);
		if (!(check_grid(sudoku)))
		{
			write(1, "invalid grid\n", 13);
			return (0);
		}
		write(1, "processing...\n\n\n", 16);
		if ((g_grid = (int**)malloc((get_size(sudoku) + 1) * sizeof(int*))) <= 0)
			return (0);
		grid_convert(sudoku);
		verif = sudo_resolve(g_grid, get_size(sudoku), 0);
		print_grid(g_grid, get_size(sudoku));
		write(1, "done!\n", 6);
		close(fd);
		free(g_grid);
	}
	return (0);
}
