
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>

int split(char *str, char **temp)
{
	char ch[1024];
	int i;
	char **par=temp;

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

	for (i = 0; temp[i]!=NULL; ++i)
			{
				printf("%s\n", temp[i]);
			}


	printf("%s\n","out of loop" );
	return 0;
}

int getpath(char *str, char *path)
{
	char *ch;
	char *pth;
	char *comm;
	int l;
	pth=path+strlen(path);

	printf("%s\n","in getpath" );
	
	*(pth++) = '/';
	ch=str;
	//pth++=str;
	while(*ch!=NULL)
	{
		*(pth++)=*(ch++);
	}

	*(pth)=NULL;

	printf("%s\n",path);

/*	while(str!=NULL)
	{
		*path++=*str++;
		l++;
	}*/

	l=strlen(str);
	ch=str+l;

	while(*(ch-1)!='/'&& ch!=str)
	{
		ch--;
	}
	//ch++;
	if((*ch)=='/')
		comm=ch+1;
	else
		comm=ch;
	*(comm+strlen(comm)+1)=NULL;

	printf("Command is %s\n",comm );
	strcpy(str,comm);
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
	char temp[1024];
	
	/*For continuos prompts*/
	for(;;)
	{
		printf("$" );
		gets(str);
		printf("%s1\n",str );
		
		split(str,par);
		strcpy(temp,str);
		getcwd(path,sizeof(path));
		printf("%s\n",path );
		getpath(temp,path);
		printf("Command in main is %s\n",temp );

		


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
			
			printf("The path is%s\n",path );
			printf("The command is %s\n",temp );
			
			printf("The arguments are %s\n",par[1]);

			for (i = 0; par[i]!=NULL; ++i)
			{
				printf("%s\n", par[i]);
			}
			

			execl(path,temp,par,0);


			
		}

		else if(pid>0)
		{
			wait();
			/*while(waitpid(pid))
			{}*/
		}
	

	}
	return 0;
}
