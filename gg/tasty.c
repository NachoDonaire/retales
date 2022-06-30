#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libtasty.h"

char	rndm_a()
{
	int	i;
	char	c;

	i = rand() % 25;
	i = i + 97;
	c = i;
	return (c);
}

char	rndm_A()
{
	int	i;
	char	c;

	i = rand() % 25;
	i = i + 65;
	c = i;
	return (c);

}

char rndm_nb()
{
	int	i;
	char	c;

	i = rand() % 10;
	i = i + 48;
	c = i;
	return (c);

}

char	*generate_psswd()
{
	char	*psswd;
	int i;
	int swityi;
	int BUFF;

	BUFF = 20;
	i = 0;
	swityi = 0;
	psswd = calloc(BUFF, sizeof(char));
	while (i < BUFF)
	{
		swityi = rand() % 3;
		if (swityi == 0)
			psswd[i] = rndm_a();
		else if (swityi == 1)
			psswd[i] = rndm_A();
		else
			psswd[i] = rndm_nb();
		i++;
	}
	psswd[i] = '\0';
	return (psswd);
}

//int main()

/*
int	main(int arg, char *args[], char * const env[])
{
	if (arg == 0)
		return (0);
	char	*psswd;
	int	pid;
	int 	fd;
	int 	pos;
	int	lec;
	char	buff[5];
	int 	check_fd;


	psswd = generate_psswd();
	pos = 0;
	char * const s[] = {args[1], NULL};
	pid = fork();
	lec = 0;
	if (pid == 0)
	{
		execve("./proof.sh", s, env);
	}
	else
	{
		check_fd = open("check_fd.txt", O_RDONLY);
		fd = open("fd", O_WRONLY);
		lec = read(check_fd, buff, 5);
		printf("%d", lec);
		while (!buff[0])
		{
			psswd = generate_psswd();
			lec = read(check_fd, buff, 5);
			while (psswd[pos])
			{
				write(fd, &psswd[pos], 1);
				pos++;
			}
			pos = 0;
			write(fd, "\n", 1);
		}
	}
	return (0);
}*/
