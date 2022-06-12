#include <stdio.h>

void ft_ft(int x, int i)
{
	printf("X = %d i = %d\n", x, i);
}

int main(void)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (i < 10)
	{
		if (i != 0 && (i % 2 == 0))
			x++;
		ft_ft(x, i);
		i++;
	}
	return (0);
}
