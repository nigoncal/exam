/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <milletp.pro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:59:05 by gbaud             #+#    #+#             */
/*   Updated: 2022/04/26 18:44:22 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef __linux__
# include <sys/wait.h>
# include <stdio.h>
#endif

#define ERR_FATAL "error: fatal\n"
#define ERR_EXEC "error: cannot execute "
#define ERR_CD_ARG "error: cd: bad arguments\n"
#define ERR_CD_DIR "error: cd: cannot change directory to "

void	ft_putnbr_fd(int n, int fd)
{
	int	s;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			n = -n;
			write(fd, "-", 1);
		}
		s = n % 10 + 48;
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		write(fd, &s, 1);
	}
}

//*****************

int ft_strlen(char *str) {
	int i = 0;
	while (str[i]) 
		i++;
	return (i);
}

int put_err(char *err, char *path) 
{
	write(2, err, ft_strlen(err));
	if (path) 
	{
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
	return (1);
}

/********		DELIMIT 1		********/
// breaking input into segments, between "|" and ";"
void sub(char **argv, char **av, int i, int j) {
	int k = 0;
	while (i < j)
		argv[k++] = av[i++];
	argv[k] = NULL;
}

int cd(char **av, int len) 
{
    if (len != 2)
        return (put_err(ERR_CD_ARG, NULL));
    if (chdir(av[1]))
        return (put_err(ERR_CD_DIR, av[1]));
    return (0);
}



/********		DELIMIT 2		********/

int main(int ac, char **av, char **env) 
{
	int i=1,j,k,l; // all my iterators.
	// i = on argc (total nm of arg), j = inside argv[x], to look for semi-colons, k = , l = 
	int   p[2]; // array with my 2 commands
	pid_t pid;
	int   fd_in;
	
	while (i < ac) // while there are args to treat (counted by "ac")
	{
		j=i, k=i, l=i;
		// checks in every argv[j], if there is a ";" inside it
		while (j < ac && strncmp(av[j], ";", 2)) // + if yes, is there a whitespace after the ";" ?
			j++;
		fd_in = 0;
		while (k < j) // Decompose chaque argv[] : avance tant qu'on est pas arrivé au ";"
		{ 
			l = k;
			while (l < j && strncmp(av[l], "|", 2)) // [k - l] -> troncon cmd + arg
				l++;
			char *argv[l - k + 1]; // creates an array with all commands ?..
			sub(argv, av, k, l);
			pipe(p); // executes commands stored in p
/********		DELIMIT 3		********/
			if ((pid = fork()) == -1) // forking and checking if it worked
				return (put_err(ERR_FATAL, NULL));
			else if (pid == 0)
			{
				dup2(fd_in, 0);
				if (l < j)
					dup2(p[1], 1);
				close(p[0]);
				if (!strncmp(argv[0], "cd", 3))
					cd(argv, l-k);
				else if (execve(argv[0], argv, env)) 
				{
					close(p[1]);
					close(fd_in);
					return (put_err(ERR_EXEC, argv[0]));
				}
				close(p[1]);
				close(fd_in);
				return (0);
			} 
			else 
			{
				waitpid(pid, NULL, 0);
				close(p[1]);
				if (fd_in)
					close(fd_in);
				fd_in = p[0];
    		}
			k=l+1;
		}
		close(fd_in);
		i=j+1;
	}
	return (0);
}
