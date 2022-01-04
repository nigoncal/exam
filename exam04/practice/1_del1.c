int		ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}

int		put_error(char *err, char *path)
{
	write(2, err, ft_strlen(err));
	if(path)
	{
		write(2, '\n', 1);
		write(2, path, ft_strlen(path));
	}
	return(1);
}

