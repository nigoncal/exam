#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int    ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void    ft_putstr(char *s)
{
	write(2, s, ft_strlen(s));
}

// 2 cases : cd or another command
void    exec(char **av, char **env, int in, int out)
{
    if (av[0] && strcmp(av[0], "cd")) // not cd case
	{
        int pid = fork();
        if (pid == 0) {
            if (in != 0) {
                dup2(in, 0);
                close(in);
            }
            if (out != 1) {
                dup2(out, 1);
                close(out);
            }
            execve(av[0], &av[0], env);
            ft_putstr("error: cannot execute ");
            ft_putstr(av[0]);
            ft_putstr("\n");
            exit(-1);
        }
    }
	else if (av[0]) // cd case
	{
        if (!av[1] || (av[1] && av[2]))
            ft_putstr("error: cd: bad arguments\n");
        else if (chdir(av[1]) == -1) {
            ft_putstr("error: cd: cannot change directory to ");
            ft_putstr(av[1]);
            ft_putstr("\n");
        }
    }
}

// envp are environment variables
int    main(int argc, char **argv, char **envp)
{
    int    i = 0, j = 0, fdsave = 0; // i = current argv[]; j = previous argv[]
    int    fd[2];

    (void) argc;
    argv = &argv[1]; // we don't need argv[0] (executable name)
    while (argv[i]) // parsing "|" and ";"
	{
        if (!strcmp(argv[i], "|")) { // strcmp returns 0 if str2 is equal to str1
            argv[i] = NULL;
            pipe(fd);
            exec(argv + j, envp, fdsave, fd[1]); // void exec(char **av, char **env, int in, int out)
            close(fd[1]);
            if (fdsave)
                close(fdsave);
            fdsave = fd[0];
            i += 1;
            j = i;
        } else if (!strcmp(argv[i], ";")) {
            argv[i] = NULL;
            exec(argv + j, envp, fdsave, 1);
            while (waitpid(-1, NULL, 0) != -1) // pid_t waitpid(pid_t, int *, int)
                ;
            if (fdsave)
                close(fdsave);
            fdsave = 0;
            i += 1;
            j = i;
        } else
            i += 1; // incrementing to parse next argv[i]
    }
    if (i > 0 && argv[i - 1] != NULL)
        exec(&argv[j], envp, fdsave, 1);
    if (fdsave)
        close(fdsave);
    while (waitpid(-1, NULL, 0) != -1)
        ;
    return 0;
}