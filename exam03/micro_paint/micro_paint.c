/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <milletp.pro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 22:41:22 by gbaud             #+#    #+#             */
/*   Updated: 2022/02/10 14:35:25 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#define ERR_ARG "Error: argument\n"
#define ERR_OPE "Error: Operation file corrupted\n"

typedef struct  s_rect 
{
    char        t; // type : 'r' = border / 'R' = fill
    char        f; // filling char
    float       x; // x pos of the painted rect
    float       y; // y pos of the painted rect
    float       w; // width of canevas
    float       h; // height of canevas
}               t_rect;

int ft_strlen(char *str) {
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int put_error(char *err) {
    write(1, err, ft_strlen(err));
    return (1);
}

int is_border(float x, float y, t_rect r) {
// est-on a l'interieur du rectangle a ecrire ?
    if (x < r.x || x > r.x + r.w ||  // est-on trop a gauche ? x < r.x || la shape est elle assez large ?)
        y < r.y || y > r.y + r.h) // meme ligne mais pour la hauteur
        return (0); // cell is outside shape
// est-on sur le bord du rectangle a ecrire ?
    if ((x - r.x < 1.00000000 || (r.x + r.w) - x < 1.00000000) || // est-on sur le bord droit du rectangle a ecrire/le bord du canevas ?
        (y - r.y < 1.00000000 || (r.y + r.h) - y < 1.00000000)) // meme ligne mais en inversé, pour la verticale
        return (2); // cell is on border
    return (1); // cell is in shape but not on border
}

// parcourt le tableau. Pour chaque case, check si elle est “dans” la forme ou non (via is_border), remplit la case si oui
int put_rect(int w, int h, char canvas[h][w], t_rect r) // dessine le rectangle a ecrire sur le canevas en memoire
{
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        // bordure (r) ou rect plein (R) ?
            if (r.t == 'r') 
            {
                if (is_border(x, y, r) == 2)
                    canvas[y][x] = r.f;
            } 
            else if (r.t == 'R')
            {
                if (is_border(x, y, r) > 0) // meme chose, juste une différence au niveau de la comparaison de la return value
                    canvas[y][x] = r.f;
            } 
            else 
                return (1);
        return (0);
}

int main(int ac, char **av) {
    FILE *operation_file;
    int w, h, last;
    t_rect r;
    char c;

//parsing start

    if (ac != 2)
        return (put_error(ERR_ARG));
    if (!(operation_file = fopen(av[1], "r"))) // ouvre le fichier en read
        return (put_error(ERR_OPE));

    // on check la 1ere ligne du fd : taille et char du canevas
    last = fscanf(operation_file, "%d %d %c\n", &w, &h, &c);
    if (last != 3 || w <= 0 || w > 300 || h <= 0 || h > 300) // si last n'est pas egale a 3, une conversion a foiré, 0 < W et H < 300
        return (put_error(ERR_OPE));
    
    // parsing step 1 stop
    // on cree et remplit le fond du canevas
    char canvas[h][w];
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            canvas[y][x] = c;

    // parsing step 2 start
    while (1)
    {
        last = fscanf(operation_file, "%c %f %f %f %f %c\n", &r.t, &r.x, &r.y, &r.w, &r.h, &r.f); // le f est en dernier
     
        if (last == EOF)
            break;
        else if (last != 6 || r.w <= 0 || r.h <= 0) // meme parsing que plus haut mais juste un check des arg et si w et h st plus grands que 0
            return (put_error(ERR_OPE));
    // parsing stop
    // on ecrit le rectangle
        else if (put_rect(w, h, canvas, r))  // On ecrit le rect parsé a la ligne courante. 0 = rien a signaler
            return (put_error(ERR_OPE));
    }
    
    for (int y = 0; y < h; y++) // print du canvas de la memoire vers la sortie standard, ligne par ligne
    {
        write(1, canvas[y], w);
        write(1, "\n", 1);
    }
    
    fclose(operation_file); // ne pas oublier !!!!
    
    return (0);
}