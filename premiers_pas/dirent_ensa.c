#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	DIR *f;
	char *err;
	struct dirent *e;
	int files = 0;

	f  = opendir("/sers/lmoreno/Documents");
	if (f == NULL)
	{
		//perror("msg");
		//perror("No se puede leer el directorio");
		err = strerror(3);
		printf("str = %s\n", err);
		return (1);
	}
	while ((e = readdir(f)))
	{
		files++;
		printf("File %3d: %hhu %s \n", files, e->d_type, e->d_name);
	}
	closedir(f);
	return (0);
}
