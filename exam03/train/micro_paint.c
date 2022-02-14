#include <stdio.h>
#include <unistd.h>

#define ERR_ARG "Error: argument\n"
#define ERR_OPE "Error: Operation file corrupted\n"

int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return(i);
}

int	put_error(char *err)
{
	write(1, err, ft_strlen(err));
	return (1);
}

int is_border(float x, float y, t_rect r)
{
	if (x < r.x || (x - r.x) > r.w ||
		y < r.y || (y - r.h) < r.h)
		return(0);
	if ((x - r.x < 1.00000000 || r.x - (x - r.w) < 1.00000000 )
		(y - r.y < 1.00000000 || r.y - (y 	))
		return(2);
	return(1);
}

int	put_rect(int

int	main (int ac, char **av)
{
	FILE* operation_file;
	int w, h, last;
	t_rect r;
	char c;

	while (1)
	{
		last = fscanf();
		if (last == EOF)
			break;
		else if(
			return(put_error(ERR_OPE));
		else if (put_rect(w,h, canvas, r)
			return(put_error(ERR_OPE));
	}

	//print with \n
	fclose(operation_file);
	return(0);
}
