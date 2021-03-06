
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>


char *hist[100];
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
		*par++ = str;
		while ((*str != ' ') && (*str != '\t') && (*str != '\0'))
			str++;
		while ((*str == ' ') || (*str == '\t'))
			*str++ = '\0';

	}
	*par = '\0';

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

	while ((*str != ' ') && (*str != '\t') && (*str != '\0'))
		str++;

	if ((*str == ' ') || (*str == '\t'))
		*str++ = '\0';

	if (str == '\0')
		strcpy(temp, " ");
	else
		strcpy(temp, str);

	free(ch);
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

	if (hist_count ==  -1)
		return 0;

	for (i = 0; i <= hist_count; i++)
		printf("%d %s\n", i, hist[i]);
	return 0;
}

int clear_history(void)
{
	hist_count =  -1;
	free(hist[100]);
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

	return 0;
}

int close_pipe(int *pfd)
{
	int l = 0;

	for (l = 0; l < 2*pipe_count; ++l)
		close(pfd[l]);
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
	int pcount;
	int pc;

	flag = 0;

	void mem_clear(void)
	{
		free(str);
		free(str1);
		free(par[64]);
		free(hist[100]);
		free(par1);
		free(temp);
	}

	/*For continuos prompts*/
	for (;;) {
		flag = 0;
		if (hflag == 0 && pflag == 0) {
			printf("$");
			getline(&str, &str_size, stdin);
		}

		str_len = strlen(str);

		if (strcmp(str, "\n") == 0)
		continue;

		if (str_len > 0 && str[str_len-1] == '\n')
			str[str_len-1] = '\0';


		if (strchr(str, '|') != NULL || pflag == 1) {
			if (pflag == 0) {
				if (hflag == 0)
					insert_history(str, str_size);

				compute_pipe(str);
				pcount = 2 * pipe_count;
				pfd = (int *)malloc((pipe_count)*2*sizeof(int));
				pipe_curr = 0;
				for (i = 0; i < pipe_count; ++i) {
					if (pipe(pfd + (2 * i)) == -1) {
						perror("pipe");
						exit(EXIT_FAILURE);
					}
				}
				pflag = 1;
			}

			strcpy(str, strpipe[pipe_curr]);
			str_len = strlen(str);
		}
		str1 = (char *)malloc(str_len*sizeof(char));
		par1 = (char *)malloc(str_len*sizeof(char));
		temp = (char *)malloc(str_len*sizeof(char));
		path = (char *)malloc(str_len*sizeof(char));

		strcpy(str1, str);
		split1(str1, par1);


		if (strcmp(str1, "history") != 0 && hflag == 0 && pflag == 0)
			insert_history(str, str_size);
		else
			hflag = 0;

		split(str, par);
		strcpy(temp, str1);

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
					fprintf(stderr, "%s", "Error: Offset");
					fprintf(stderr, "%s\n", "out of range");
				}
			} else {
				fprintf(stderr, "Error: ");
				fprintf(stderr, "%s\n", "Invalid argument");
			}
			flag = 1;
		}

		/*cd command*/
		else if (strcmp(temp, "cd") == 0 && pflag == 0) {
			flag = 1;
			if (strcmp(par1, "\0") == 0) {
				fprintf(stderr, "%s", "Error: cd takes ");
				fprintf(stderr, "%s\n", "a single arg");
			}
			chdir(par1);
		}

		/*exit command*/
		else if (strcmp(temp, "exit") == 0) {
			flag = 1;
			exit(0);
		}


		else {
			pid = fork();
			if (pid < 0) {
				perror("fork");

				mem_clear();

				exit(1);
			}

			else if (pid == 0 && pflag == 1) {
				if (pipe_curr < pipe_count
					&& pipe_curr != 0) {
					if (dup2(pfd[pc - 2], 0) == -1) {
						printf("error: ");
						printf("%s\n", strerror(errno));
						exit(EXIT_FAILURE);
					}
					if (dup2(pfd[pc + 1], 1) == -1) {
						printf("error: ");
						printf("%s\n", strerror(errno));
						exit(EXIT_FAILURE);
					}
					close_pipe(pfd);


				} else if (pipe_curr == 0) {
					if (dup2(pfd[1], 1) == -1) {
						printf("error: ");
						printf("%s\n", strerror(errno));
						exit(EXIT_FAILURE);
					}
					close_pipe(pfd);
				} else {
					if (dup2(pfd[(pcount) - 2], 0) == -1) {
						printf("error: ");
						printf("%s\n", strerror(errno));
						exit(EXIT_FAILURE);
					}
					close_pipe(pfd);
				}
				if (execv(str, par) ==  -1)
					printf("error: %s\n", strerror(errno));
				return 0;
				}

			else if (pid == 0 && pflag == 0) {
				if (execv(str, par) ==  -1) {
					printf("error: %s\n", strerror(errno));
					exit(EXIT_FAILURE);
				}
				return 0;
			}

			else {


				if (pflag == 1 && pipe_curr < pipe_count) {
					pipe_curr++;
					pc = 2 * pipe_curr;
					continue;

				} else if (pflag == 1 &&
						pipe_curr == pipe_count) {
					pipe_curr++;
					pc = 2 * pipe_curr;
				}
				if (pflag == 1
					&& pipe_curr == pipe_count+1) {
					pflag = 0;
					pipe_curr = 0;
					pc = 0;
					close_pipe(pfd);
					pipe_count =  -1;
					free(strpipe[64]);
					free(pfd);
				}
				if (pflag == 0)
					while (wait(&status) != pid)
					;
			}
		}
	}
	mem_clear();
	return 0;
}
