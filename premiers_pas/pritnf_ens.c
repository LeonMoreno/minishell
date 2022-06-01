#include <stdio.h>
#include <stdlib.h>

//extern char **environ;

int main(int argc, char **arv, char **env)
{
	//printf("%s\n", environ[0]);
	//*environ = malloc(sizeof(char) * 5);
	if (setenv("LEOA", "100", 0) != 0)
		perror("setenv");
	//*environ = "leo=1";	

	//printf("%s\n", *environ);
	/*int i;
	char **envs;
	envs = env;
	i = 0;
	while (envs[i])
	{
		printf("%s\n", envs[i]);
		i++;
	}*/
	return(0);
}

