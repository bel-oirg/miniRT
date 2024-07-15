/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/15 19:00:02 by bel-oirg         ###   ########.fr       */
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
    t_dot ray_o;
    t_dot ray_d;
    float a;
    float b;
    float c;
    float r;
    float delta;
    r = 1.2f;
    set_dot(&ray_o, 0.0f, 0.0f, -2.0f);

    /*
    Sphere equation : (x^2 - a^2) + (y^2 - b^2) + (z^2 - c^2) = r^2
    to do raycasting on a sphere, we will change x, y
    now -> x^2 + y^2 = r^2 
    */
    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            set_dot(&ray_d, (float)x/WIDTH, (float)y/HEIGHT, 0.5f);

            //to centralize the spher - [0, 1] --> [-1, 1]
            ray_d.x = ray_d.x * 2.0f - 1.0f;
            ray_d.y = ray_d.y * 2.0f - 1.0f;

            //calculate the delta params
            a = _dot(ray_d, ray_d);
            b = 2.0f * _dot(ray_o, ray_d);
            c = _dot(ray_o, ray_o) - r*r;
            delta = b*b - 4.0f * a * c;

            if (delta >= 0.0f)
                my_mlx_pp(raw, x, y, 0xFF0000 );
        }
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