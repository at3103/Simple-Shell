
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>

int split(char *str, char **par)
{
	char ch[1024];

	while(*str!=NULL)
	{
		
		printf("%s\n","in loop" );
		while((*str!=' ') && (*str!='\t') && (*str!=NULL))
			str++;
		printf("%s\n","out while");
		
		while((*str==' ') || (*str=='\t'))
		{
			*str++=NULL;

		}
		*par++=str;


	}
	*par=NULL;
	printf("%s\n","out of loop" );
	return 0;
}

int getpath(char *str, char *path)
{
	char *ch;
	int l;

	printf("%s\n","in getpath" );
	*(path+strlen(path)) = '\\';
	*path++;
	*path=NULL;

	printf("%s\n",path );

	// while(str!=NULL)
	// {
	// 	*path++=*str++;
	// 	l++;
	// }

	//l=strlen(str);
	ch=str+l;

	// while(*ch!='\\')
	// {
	// 	ch--;
	// }
	// ch++;
	// str=ch;
	// *ch=NULL;

	return 0;
}

int main(int argc, char const *argv[])
{
	char c;
	char str[1024];
	char *par[64];
	int pid;
	int status;
	int i;
	char path[1024];
	
	/*For continuos prompts*/
	for(;;)
	{
		printf("$" );
		gets(str);
		printf("%s1\n",str );

		split(str,par);
		getcwd(path,sizeof(path));
		printf("%s\n",path );
		getpath(str,path);

		


		pid=fork();

		printf("%d\n",pid);

		for (i = 0; par[i]!=NULL; ++i)
			{
				printf("%s\n", par[i]);
			}
			printf("%s\n",str );


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
			
			//execl(path,str,par);

			
			
		}

		else if(pid>0)
		{
			while(waitpid(pid))
			{}
		}
	

	}
	return 0;
}
