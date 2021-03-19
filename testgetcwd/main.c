#include <stdio.h>
#include <unistd.h>
# define MAXDIR 50
int main(void)
{
char dir[MAXDIR];
getcwd(dir, MAXDIR);
printf("Current directory is %s", dir);
return 0;
}
