
#include <stdlib.h>
#include <stdio.h>

int	sudo_check_bl(int li, int col, int nb, int **grid)
{
	int	n;
	int	i;

	col = col - col % 3;
	li = li - li % 3;
	n = 0;
	while (n < 3)
	{
		i = 0;
		while (i < 3)
		{
			if (grid[col + n][li + i] == nb)
				return (1);
			i++;
		}
		n++;
	}
	return (0);
}

int	sudo_check_col(int li, int nb, int len, int **grid)
{
	int	n;

	n = 0;
	while (n < len)
	{
		if (grid[n][li] == nb)
			return (1);
		n++;
	}
	return (0);
}

int	sudo_check_li(int col, int nb, int len, int **grid)
{
	int	n;

	n = 0;
	while (n < len)
	{
		if (grid[col][n] == nb)
			return (1);
		n++;
	}
	return (0);
}

int	sudo_resolve(int **grid, int len, int pos)
{
	int	li;
	int	col;
	int	nb;

	if (pos == len * len)
		return (1);
	col = pos / len;
	li = pos % len;
	nb = 1;
	if (grid[col][li] != 0)
		return (sudo_resolve(grid, len, pos + 1));
	while (nb < 10)
	{
		if (sudo_check_col(li, nb, len, grid) + sudo_check_li(col, nb, len, grid) 
		+ sudo_check_bl(li, col, nb, grid) == 0)
		{
			grid[col][li] = nb;
			if (sudo_resolve(grid, len, pos + 1) == 1)	
				return (1);
		}
		nb++;
	}
	grid[col][li] = 0;
	return (0);
}
