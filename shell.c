
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

int split(char *str, char **par)
{
	char ch[1024];
	int i;
	i=0;

	while(*str!=NULL)
	{
		while(*str!=' ' ||*str!='\t'||*str!=NULL )
			ch[i++]=*(str++);
		if(*str==' ' || *str=='\t')
		{
			*str++=NULL;
			ch[i++]=*(str++);
			strcpy(*par++,ch);
			i=0;
		}

	}
	return 0;
}

int main(int argc, char const *argv[])
{
	char c;
	char str[1024];
	char *par[64];
	int pid;
	int status;
	/* code */
	/*putchar('\n');
	putchar('$');
	c=getchar();
	putchar(':');
	putchar(c);
	putchar('\n');	
	putchar('\n');
	*/
	for(;;)
	{
		printf("$" );
		gets(str);
		printf("%s1\n",str );

		pid=fork();

		printf("%d\n",pid);

		if(pid==0)
		printf("%s\n","Heyyy" );

		if (pid<0)
		{
			perror("fork");
			exit(1);
		}

		if (pid==0)
		{
			printf("CHILD\n");
			split(str,par);
			printf("%s\n CHILD2",par);
			
		}

		else if(pid>0)
		{
			while(wait(&status)!=pid)
			printf("Hello!!\n");
		}
	

	}
	/*write(1,'&',sizeof(char));*/
	return 0;
}
