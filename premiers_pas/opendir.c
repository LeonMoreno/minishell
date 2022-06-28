#include <dirent.h>
#include <stdio.h>

int main(void)
{
	DIR *d;
	struct dirent *dir;
	
	d = opendir(".");
	if (!d)
		return (0);
	while ((dir = readdir(d)))
		printf("%s\n", dir->d_name);
	closedir(d);
	return (0);
}
