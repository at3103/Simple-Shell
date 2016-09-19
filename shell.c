
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

//#define mem_clear(){free(str);free(hist[100]);free(par1);free(temp);}

//char hist[1024][100];
char *hist[100];//=NULL;
int hist_count =  -1;
int pipe_count =  -1;
char *strpipe[64];
int pipe_curr;

int split(char *strtemp, char **temp)
{
	char *ch;

	ch = (char *)malloc(strlen(strtemp)*sizeof(char));
	int i;
	char **par = temp;
	char *str = strtemp;

	while (*str != '\0') {

		//printf("%s\n","in loop" );/*debug*/
		*par++ = str;
		while ((*str != ' ') && (*str != '\t') && (*str != '\0'))
			str++;
		//printf("%s\n","out while");/*debug*/

		while ((*str == ' ') || (*str == '\t'))
			*str++ = '\0';
		//if(*(str+1)!='\0')



	}
	*par = '\0';
/*
*	for (i = 0; temp[i]!='\0'; ++i)
*		printf("Arguments are %sthis\n", temp[i]);
*/

	//printf("%s\n","out of loop" );/*debug*/
	free(ch);
	return 0;
}

int split1(char *strtemp, char *temp)
{
	char *ch;

	ch = (char *)malloc(strlen(strtemp)*sizeof(char));

	int i;
	char *par = temp;
	char *str = strtemp;


	//printf("%s\n","in loop" );/*debug*/

	while ((*str != ' ') && (*str != '\t') && (*str != '\0'))
		str++;
	//printf("%s\n","out while");/*debug*/

	if ((*str == ' ') || (*str == '\t'))
		*str++ = '\0';

	//temp=str;
	if (str == '\0')
		strcpy(temp, " ");
	else
		strcpy(temp, str);
/*	if(*(str+1)!='\0')
	*par='\0';
*/

	free(ch);
	//free(par);
	//free(str);
	//free(strtemp);
	//free(temp);
	return 0;
}


int getpath(char *str, char *path)
{
	char *ch;
	char *pth;
	char *comm;
	size_t l;

	pth = path;
/*
*	pth=path+strlen(path);
*	printf("%s\n","in getpath" );
*	/*debug*/

/*
*	*(pth++) = '/';
*	ch=str;
*	pth++=str;
*	while(*ch!=NULL)
*		*(pth++)=*(ch++);
*
*	*(pth)=NULL;
*	printf("%s\n",path);
*	while(str!=NULL){
*		*path++=*str++;
*		l++;
*	}
*/

	l = strlen(str);
	ch = str+l;

	while (*(ch-1) != '/' && ch != str)
		ch--;

	if ((*ch) == '/') {
		comm = ch+1;
		*pth++ = '/';
		*pth = '\0';
	} else if ((ch == str) && *ch != '/') {
		comm = ch;
		*pth++ = '.';
		*pth = '\0';

	} else {
		comm = ch;
		*(ch-1) = '\0';
		strcpy(pth, str);
		pth++;
		*pth = '\0';
	}
	*(comm+strlen(comm)+1) = '\0';

	//printf("Command is %s\n",comm );/*debug*/
	//printf("Path is %s\n",path );/*debug*/
	strcpy(str, comm);
	return 0;
}

int insert_history(char *str, size_t str_size)
{
	int i;

	hist_count++;

	if (hist_count < 100) {
		hist[hist_count] = malloc(str_size * sizeof(char));
		strcpy(hist[hist_count], str);
	}

	else {
		for (i = 0; i < hist_count; i)
			strcpy(hist[i], hist[i+1]);

		hist_count--;
		strcpy(str, hist[hist_count++]);
	}
	return 0;

}


int display_history(void)
{
	int i;

	if (hist_count ==  -1) {
		printf("\n\n");
		return 0;
	}

	//printf("\n\n" );
	for (i = 0; i <= hist_count; i++)
		printf("%d %s\n", i, hist[i]);
	return 0;
}

int clear_history(void)
{
	hist_count =  -1;
	free(hist[100]);
	//printf("%s\n","history cleared!!" ); /*debug*/
	return 0;
}

int compute_pipe(char *str)
{
	char *temp;

	int i;


	for (temp = strtok(str, "|"); temp != NULL; temp = strtok(NULL, "|")) {
		pipe_count++;
		strpipe[pipe_count] = (char *)malloc(sizeof(temp));
		strcpy(strpipe[pipe_count], temp);
	}

	// temp=strtok(NULL,'\0');
	//pipe_count++;
	//strtemp[pipe_count]=(char*)malloc(sizeof(temp));
	//strcpy(strtemp[pipe_count],temp);
	for (i = 0; i <= pipe_count; ++i)
		printf("%d%s\n", i, strpipe[i]);
	printf("The count is %d\n", pipe_count);
	//exit(0);

	return 0;
}



int main(int argc, char const *argv[])
{
	char c;
	char *str = NULL;
	size_t str_size;
	char *str1;
	char *par[64];
	char *par1;
	int pid;
	int status;
	int i;
	char *path;
	char cwd[1024];
	char *temp;
	int flag;
	size_t str_len;
	int j;
	int hflag = 0;
	int *pfd;
	int pflag = 0;

	int l;

	flag = 0;

	void mem_clear(void)
	{
		free(str);
		free(str1);
		free(par[64]);
		free(hist[100]);
		free(par1);
		free(temp);
		// free(strpipe[64]);
		// free(pfd);
	}

	/*For continuos prompts*/
	for (;;) {
		flag = 0;
		/**path=' ';*/
		if (hflag == 0 && pflag == 0) {
			printf("$");
			getline(&str, &str_size, stdin);
/*			printf("%s\n",str );
*			printf("%zu\n",str_size );
			*/
		}

		str_len = strlen(str);

		if (str_len > 0 && str[str_len-1] == '\n')
			str[str_len-1] = '\0';

		if (str_len == 1)
			continue;

		if (strchr(str, '|') != NULL || pflag == 1) {
			if (pflag == 0) {
				if (hflag == 0)
					insert_history(str, str_size);

				compute_pipe(str);
				printf("%d\n", pipe_count);
				pfd = (int *)malloc((pipe_count+1)*sizeof(int));
				pipe_curr = 0;
				pipe(pfd);
				pflag = 1;
			}
/*
*			if (pipe_curr==pipe_count+1)
*				pflag=0;
*/

			strcpy(str, strpipe[pipe_curr]);

			/* code */
		}
		str1 = (char *)malloc(str_len*sizeof(char));
		par1 = (char *)malloc(str_len*sizeof(char));
		temp = (char *)malloc(str_len*sizeof(char));
		path = (char *)malloc(str_len*sizeof(char));

		//printf("%s\n","history insertd" ); /*debug*/
		strcpy(str1, str);
		split1(str1, par1);


		if (strcmp(str1, "history") != 0 && hflag == 0 && pflag == 0)
			insert_history(str, str_size);
		else //if (strcmp(str1,"history")==0){
			hflag = 0;

		split(str, par);
		//split1(str1,par1);
		strcpy(temp, str1);
		//getpath(temp,path);

		//printf("Command in main is %s\n",temp );/*debug*/
		//printf("Parameters in main is %s\n",par1 );/*debug*/


		if (strcmp(temp, "history") == 0 && pflag == 0) {
			if (strcmp(par1, "\0") == 0) {
				display_history();
			}

			else if (strcmp(par1, "-c") == 0) {
				clear_history();
			}

			else if (((atoi(par1) < 10 && par1[1] == '\0') ||
				  (atoi(par1) < 100 && atoi(par1) > 9 &&
				   isdigit(par1[1])))
				 && (atoi(par1) >= 0 && isdigit(par1[0]))) {
				j = atoi(par1);
				if (j <= hist_count) {
					strcpy(str, hist[j]);
					hflag = 1;
					continue;
				} else {
					printf("%s", "error :");
					printf("%s\n", "Offset out of range");
				}
			} else
				printf("%s\n", "Error : Invalid argument");
			flag = 1;
		}

		/*cd command*/
		else if (strcmp(temp, "cd") == 0 && pflag == 0) {
			flag = 1;
			chdir(par1);
			getcwd(cwd, sizeof(cwd));
			printf("%s\n", cwd);/*debug*/
		}

		/*exit command*/
		else if (strcmp(temp, "exit") == 0) {
			flag = 1;

			//mem_clear();
			exit(0);
		}


		else {
			pid = fork();

			if (pid < 0) {
				perror("fork");

				mem_clear();

				exit(1);
			}

			if (pid == 0) {
				if (pflag == 1) {
					printf("%s\n", "Entered");
					if (pipe_curr < pipe_count
						&& pipe_curr != 0) {
						printf("%s\n", "Entered2");
						dup2(pfd[pipe_curr]-1, 0);
						dup2(pfd[pipe_curr+1], 1);
						for (l = 0;
							l <= pipe_count; ++l)
							// if(l==pipe_curr+1
							//|| l==pipe_curr-1)
							//	continue;
							close(pfd[l]);
					} else if (pipe_curr == 0) {
						printf("%s\n", "Entered3");
						dup2(pfd[pipe_curr+1], 1);


						for (l = 0;
							l <= pipe_count; ++l)
							// if(l==pipe_curr+1)
							//	continue;
							close(pfd[l]);
					} else {
						dup2(pfd[pipe_curr]-1, 0);
						printf("%s\n", "Entered4");
						for (l = 0;
							l <= pipe_count; ++l)
							// if(l==pipe_curr-1)
							//	continue;
							close(pfd[l]);

					}


				}

				// printf("CHILD\n");/*debug*/

				printf("The path is %s\n", str);/*debug*/
				printf("The command is %s\n", temp);/*debug*/

				printf("The arg are %s\n", par[1]);/*debug*/

/*				  for (i = 0; par[i]!=NULL; ++i){
*				  printf("First argument is %s ", par[i]);
*				  }
*/
				//printf("\n");
				//execl("/bin/ls","ls",".",0);

				if (execv(str, par) ==  -1) {
					printf("error: %s\n", strerror(errno));
					//mem_clear();

				}

/*
*				if(strcmp(par1,"\0")==0) {
*					execl(str,temp,0);
*				} else
*					execl(str,temp,par1,0);
*/
				return 0;



			}

			else {

/*
*				if (pflag==1)
*				{
*				dup2(pdf[pipe_curr],0);
*
*				for ( l = 0; l <= pipe_count; ++l)
*					close(pdf[l])
*/


				if (pflag == 1 && pipe_curr < pipe_count) {
					pipe_curr++;
					printf("%s%d\n", "Inc", pipe_curr);
					continue;

				} else if (pflag == 1 &&
						pipe_curr == pipe_count) {
					pipe_curr++;
					printf("%s%d\n", "Inc", pipe_curr);
				}
				if (pflag == 1 && pipe_curr == pipe_count+1) {

					pflag = 0;
					dup2(0, 0);
					dup2(1, 1);
					printf("%s\n", "Finished");
					pipe_curr = 0;
					for (l = 0; l <= pipe_count; ++l)
						close(pfd[l]);
					//mem_clear();
					pipe_count =  -1;
					free(strpipe[64]);
					free(pfd);

				}
				while (wait(&status) != pid)
					;
				//mem_clear();

			}
		}


	}


	mem_clear();

	// free(str);
	// free(hist[100]);
	// free(par1);
	//free(temp);
	//free(&str_size);
	return 0;
}
