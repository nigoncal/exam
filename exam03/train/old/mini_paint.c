#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define ERR_ARG "Error: argument"
#define ERR_OPE "Error: Operation file corrupted"

typedef struct	s_circ
{
	char	t;
	float	x;
	float	y;
	float	r;
	char	f;
}				t_circ;

int	ft_strlen(char* str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}

int	put_error(char* err)
{
	write(1, err, ft_strlen(err));
	return (1);
}

float dist (float x1, float y1, float x2, float y2)
{
	return(sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

int is_border(int x, int y, t_circ r)
{
	if (dist(x, y, r.x, r.y) > r.r)
		return (0);
	if (dist(x, y, r.x, r.y) > r.r - 1)
		return (2);
	return (1);
}

int	put_circ(int w, int h, char canvas[h][w], t_circ r)
{
	for(int y = 0; y < h; y++)
		for(int x = 0; x < w; x++)
			if (r.t == 'c')
			{
				if (is_border(x, y, r) == 2)
					canvas[y][x] = r.f;
			}
			else if (r.t == 'C')
			{
				if (is_border(x, y, r) > 0)
					canvas[y][x] = r.f;
			}
			else
				return (1);
	return (0);
}

int	main(int ac, char**av)
{
	FILE *operation_file;
	int w, h, last;
	t_circ r;
	char c;

	if (ac != 2)
		return (put_error(ERR_ARG));
	if (!(operation_file = fopen(av[1], "r")))
		return (put_error(ERR_OPE));

	last = fscanf(operation_file, "%d %d %c\n", &w, &h, &c);
	if (last != 3 || w <= 0 || w > 300 || h <= 0 || h > 300)
		return (put_error(ERR_OPE));

	char canvas[h][w];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			canvas[y][x] = c;

	while(1)
	{
		last = fscanf(operation_file, "%c %f %f %f %c", &r.t, &r.x, &r.y, &r.r, &r.f);
		
		if (last == EOF)
			break;
		else if (last != 5 || r.r <= 0)
			return(put_error(ERR_OPE));
		else if (put_circ(w, h, canvas, r))
			return(put_error(ERR_OPE));
	}

	for (int y = 0; y < h; y++)
	{
		write(1, canvas[y], w);
		write(1, "\n", 1);
	}
	fclose(operation_file);
	return(0);
}