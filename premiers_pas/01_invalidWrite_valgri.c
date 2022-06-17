#include <stdlib.h>

int	main(void)
{
	int	i;
	char	*s;
	
	s = malloc(sizeof(char) * 10);
	i = 0;
	while (i < 30)
	{
		s[i] = '\0';
		i++;
	}
	free(s);
	return (0);
}
