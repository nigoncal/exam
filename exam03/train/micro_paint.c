#include <stdio.h>
#include <unistd.h>


#define ERR_OPE "Error: Operation file corrupted"
#define ERR_ARG "Error: argument"

typedef struct	s_rect
{
	char	t;
	char	f;
	float	x;
	float	y;
	float	h;
	float	w;
}				t_rect;

int	ft_strlen(char* str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	put_error(char* err)
{
	write(1, err, ft_strlen(err));
	return (1);
}

//Xa == x/ Ya == y => la case traitee
//Xtl == r.x/Ytl == r.y => coin haut gauche de la shape
//Xbr == r.x + r.w/Ybr == r.y + r.h => coin bas droit de la shape
//If Xtl <= Xa <= Xbr and Ytl <= Ya <= Ybr, alors le point est dans le rectangle
int	is_border(float x, float y, t_rect r)
{
	//is in rect ?
	if (x < r.x || x > r.x + r.w ||
		y < r.y || y > r.y + r.h)
		return (0); // if [y][x] is outside shape
	if ((x - r.x < 1.00000000 || (r.x + r.w) - x < 1.00000000 ) || // coordo case x - Xtl de la shape : donnera - de 1 si x est ds le rectangle 
//la case est elle pile sur le bord gauche ? si oui, sa coordo x - point le + a gauche de la shape donnera qqch entre 0 et 1
//la case est-elle pile sur le bord droit ? si oui, (bord gauche shape + largeur shape) - coordo x donnera qqch entre 0 et 1
		(y - r.y < 1.00000000 || (r.y + r.h) - y < 1.00000000 )) //
		return(2);
	return (1);
}

int	put_rect (int w, int h, char canvas[h][w], t_rect r)
{
	for(int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		// envoi à is_border avec les conditions correspondantes + changement du contenu de la case si ok
			if (r.t == 'r')
			{
				if(is_border(x, y, r) == 2)
					canvas[y][x] = r.f;
			}
			else if (r.t == 'R')
			{
				if(is_border(x, y, r) > 0)
					canvas[y][x] = r.f;
			}
			else
				return(1);
		return(0);
}

int	main(int argc, char** argv)
{
	FILE	*operation_file;
	int		w, h, last;
	char	c;
	t_rect	r;

	if (argc != 2)
		return(put_error(ERR_ARG));
	if(!(operation_file = fopen(argv[1], "r")))
		return(put_error(ERR_OPE));

	//parsing ligne 1
	last = fscanf(operation_file, "%d %d %c\n", &w, &h, &c);
	//protec
	if (last != 3 || w < 0 || w > 300 || h < 0 || h > 300)
	{
		return(put_error(ERR_OPE));
	}
	//creation canvas
	char canvas [h] [w];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			canvas[y][x] = c;

	//boucle parsing + draw de chaque shape
	while(1)
	{
		last = fscanf(operation_file, "%c %f %f %f %f %c\n", &r.t, &r.x, &r.y, &r.w, &r.h, &r.f);
		if (last == EOF)
			break;
		else if (r.w <= 0 || r.h <= 0)
			return(put_error(ERR_OPE));
		//send to put_rect & repeat
		else if (put_rect(w, h, canvas, r))
			return (put_error(ERR_OPE));
	}

	//print canvas to output
	for (int y = 0; y < h; y++)
	{
		write(1, canvas[y], w);
		write(1, "\n", 1);
	}

	fclose(operation_file);
	return(0);
}
