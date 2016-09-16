
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
//#include <process.h>

int split(char *str, char **temp)
{
	char ch[1024];
	int i;
	char **par=temp;

	while(*str!='\0')
	{
		
		printf("%s\n","in loop" );/*debug*/
		while((*str!=' ') && (*str!='\t') && (*str!='\0'))
			str++;
		printf("%s\n","out while");/*debug*/
		
		while((*str==' ') || (*str=='\t'))
		{
			*str++='\0';

		}
		*par++=str;


	}
	*par='\0';

	for (i = 0; temp[i]!='\0'; ++i)
			{
				printf("%s\n", temp[i]);
			}


	printf("%s\n","out of loop" );/*debug*/
	return 0;
}

int getpath(char *str, char *path)
{
	char *ch;
	char *pth;
	char *comm;
	size_t l;

	pth=path;
	/*pth=path+strlen(path);
*/
	printf("%s\n","in getpath" );/*debug*/
	
	/**(pth++) = '/';*/
	/*ch=str;
	//pth++=str;
	while(*ch!=NULL)
	{
		*(pth++)=*(ch++);
	}

	*(pth)=NULL;

	printf("%s\n",path);
*/
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
	{
		comm=ch+1;
		*pth++='/';
		*pth='\0';
	}
	else if((ch==str) && *ch!='/')
	{
		comm=ch;
		*pth++='.';
		*pth='\0';

	}
	else
	{
		comm=ch;
		*(ch-1)='\0';
		strcpy(pth,str);
		pth++;
		*pth='\0';
	}
	*(comm+strlen(comm)+1)='\0';

	printf("Command is %s\n",comm );/*debug*/
	printf("Path is %s\n",path );/*debug*/
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
	char cwd[1024];
	char temp[1024];
	int flag;
	size_t str_len;
	/*For continuos prompts*/
	for(;;)
	{	
		flag=0;
		*path=' ';
		printf("$" );
		/*gets(str);*/
		fgets(str,sizeof(str),stdin);

		str_len=strlen(str);

		if(str_len>0 && str[str_len-1]=='\n')
		{
			str[str_len-1]='\0';
		}

		printf("%s1\n",str );	/*debug*/
		
		split(str,par);
		strcpy(temp,str);
		//getcwd(path,sizeof(path));
		getpath(temp,path);
		printf("Command in main is %s\n",temp );/*debug*/


		
		if(strcmp(temp,"exit")==0)
		{
			printf("Exiting %s\n",temp);/*debug*/
			flag=1;	
			exit(0);
			//break;
		}

		else if(strcmp(temp,"cd")==0)
		{	
			flag=1;
			chdir(par[0]);
			getcwd(cwd,sizeof(cwd));
			printf("The changed dir is %s\n",cwd);/*debug*/	
		}

			

		else if(strcmp(temp,"history")==0)
		{
			flag=1;
			chdir(par[0]);
			getcwd(cwd,sizeof(cwd));
			printf("The changed dir is %s\n",cwd);/*debug*/	
		}

		else
		{
			pid=fork();

			printf("%d\n",pid);

			
			if (pid<0)
			{
				perror("fork");
				exit(1);
			}

			if (pid==0)
			{

				printf("CHILD\n");/*debug*/
			
				printf("The path is %s\n",path );/*debug*/
				printf("The command is %s\n",temp );/*debug*/
				
				printf("The arguments are \n");/*debug*/

				for (i = 0; par[i]!=NULL; ++i)
				{
					printf("%s\n", par[i]);
				}
			
				execl(str,temp,par,0);

				return 0;
				//execvp(temp,par);

				
			}

			else 
			{
				while(wait(&status)!=pid)
					;
				//waitpid(pid);
				/*while(!waitpid(pid))
				{}*/
			}
		}

	}
	return 0;
}
