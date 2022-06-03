#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// wetiven version from his gitLab
// Compilation :
// gcc -g -Wall -Werror -Wextra microshell.c -o microshell

size_t	ft_strlen(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

void    ft_puterr(char *s) // 
{ 
	write(2, s, ft_strlen(s));
}

void	exec(char **av, char **env, int in, int out) // always specify in/output. fd[0]/fd[1] for pipes, else 0 and 1.
{
	int	pid;

	if (av[0]) // Seems clearer to make that test here instead of burying it in an "else if".
	{
		if (strcmp(av[0], "cd") == 0) // Also avoiding brainfarts by expliciting strcmp expected returns, and avoiding "double negative" assumptions on its return.
		{
			if (!av[1] || (av[1] && av[2])) // no arg or more than 1
				ft_puterr("error: cd: bad arguments\n");
			else if (chdir(av[1]) == -1) // can't go to path
			{
				ft_puterr("error: cd: cannot change directory to ");
				ft_puterr(av[1]);
				ft_puterr("\n");
			}
		}
		else
		{
			pid = fork();
			if (pid == 0) // if we're in child process, restore in/outputs (in case precedent pipes messed them up), execve the cmd, and put error and exit
			{
				if (in != STDIN_FILENO)
				{
					dup2(in, STDIN_FILENO);
					close(in);
				}
				if (out != STDOUT_FILENO)
				{
					dup2(out, STDOUT_FILENO);
					close(out);
				}
				execve(av[0], av, env);
				ft_puterr("error: cannot execute ");
				ft_puterr(av[0]);
				ft_puterr("\n");
				exit(-1);
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	int	start = 0, end = start, cmd_in = STDIN_FILENO;
	int	fd[2];

	(void)ac;
	av = &av[1]; // gets rid of av[0] which is not usefull
	while (av[end])
	{
		if (strcmp(av[end], "|") == 0) // pipe = execute cmd, then use output as input to next cmd
		{
			av[end] = NULL;
			pipe(fd); // creates a pipe via fd's
			exec(av + start, env, cmd_in, fd[1]); // Send output to pipe // exec(char **av, char **env, int in, int out)
			close(fd[1]); // Close pipe output
			if (cmd_in != STDIN_FILENO) // check if some fd is open here
				close(cmd_in);
			cmd_in = fd[0]; // // pipe input becomes current cmd input for next loop to catch
			end++;
			start = end;
		}
		else if (strcmp(av[end], ";") == 0) // semi-colon = there are several cmds to treat (before and after the ";")
		{
			av[end] = NULL;
			exec(av + start, env, cmd_in, STDOUT_FILENO); // Send out == 1
			while (waitpid(-1, NULL, 0) != -1) // Wait for prev cmd exec
				;
			if (cmd_in != STDIN_FILENO)
				close(cmd_in);
			cmd_in = STDIN_FILENO; // current cmd input resets to STDIN (meaning 0)
			end++;
			start = end;
		}
		else
			end++; // go to next arg 
	}
	if (end > 0 && av[end - 1] != NULL) // if previous av[] is null, means it has been treated bc it had a | or ; ?
		exec(av + start, env, cmd_in, STDOUT_FILENO); // executing all non null av[], starting at "start"
	while (waitpid(-1, NULL, 0) != -1)
		;
	if (cmd_in != STDIN_FILENO) // Don't know why this was above waitpid in the original version, it seems to work here, but let's keep that in mind if unexpected bugs appear.
		close(cmd_in);
	return 0; // don't forget this !!!
}
