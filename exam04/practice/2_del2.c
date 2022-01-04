#ifdef __linux__
	#include <stdio.h>
	#include <sys/wait.h>
#endif

int		ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}

int		put_error(char *err, char *path)
{
	write(2, path, ft_strlen(path));
	if(path)
	{
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
	return(1);
}

void	sub(char **argv, char **av, int j, int i) //manque d'elements
{
	int k = 0;
	while(i < j)
		argv[k++] = av[i++];
	argv[k] == NULL;
}

int	cd (char **av, int len)
{
	if(len != 2)
		return(err_len, NULL);
	if(chdir(av[1]))
		return(err_arg, av[1]);
	return(0);
}

