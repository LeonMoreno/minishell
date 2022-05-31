#include "include/libft.h"

int main(void)
{
	char *res;
	char *res2;
	char *res3;
	int	len;

	len = 0;
	res = ft_strchr("Hola mi leo iestas Bacan", 'i');
	res2 = res;
	res2++;
	while (*res2 != 'i')
	{
		res2++;
		len++;
	}
	printf("len = %d\n", len);
	res3 = malloc(sizeof(char) * len + 3);
	ft_strlcpy(res3, res, len + 3);
	printf("res = %s\n", res3);
	return (0);
}
