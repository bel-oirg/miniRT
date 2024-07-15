/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/15 12:16:32 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h> //to use random() :)

void my_mlx_pp(t_img *raw, int x, int y, int color)
{
    char	*dst;

	dst = raw->addr + (y * raw->line_length + x * (raw->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void davinchi(t_img *raw)
{
    int x;
    int y;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
            my_mlx_pp(raw, x, y, random());
    }
}

void init_minirt()
{
    void *mlx;
    void *win;
    t_img raw_img;

    mlx = mlx_init(); //check if it fails
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "A TITLE");
    raw_img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    raw_img.addr = mlx_get_data_addr(raw_img.img, &raw_img.bits_per_pixel, &raw_img.line_length, &raw_img.endian);
    davinchi(&raw_img);
    mlx_put_image_to_window(mlx, win, raw_img.img, 0, 0);
    mlx_loop(mlx);
}

int main()
{
    init_minirt();
}