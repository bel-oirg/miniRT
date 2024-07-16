/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/16 21:00:11 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void my_mlx_pp(t_img *raw, int x, int y, unsigned int color)
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
    t_dot hit_p;
    // unsigned int col;
    
    //degree 2, params
    float a;
    float b;
    float c;

    //solutions
    float t1;
    float t2;

    //delta
    float delta;

    //raduis of the sphere
    float r;
    
    float close_p;
    r = 1.5f;
    set_dot(&ray_o, 0.0f, 0.0f, -2.0f);
    t_dot *normalize_p;
    t_dot *light_d;
    float d;


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

            delta = (b*b - 4.0f * a * c);
            if (delta < 0)
                continue;
            t1 = (-b - sqrt(delta)) / (2.0f * a);
            t2 = (-b + sqrt(delta)) / (2.0f * a);
            close_p = fmin(t1, t2);

            set_hit_p(&hit_p, ray_o, ray_d, close_p);
            normalize_p = normalizer(&hit_p);

            set_dot(light_d, -1.0f, -1.0f, -1.0f);
            
            light_d = normalizer(light_d);

            d = fmax(_dot(*normalize_p, *light_d), 0.0f); // it gives us the cos(angle)
            unsigned int col = get_col((d * 0.5f) + 0.5f, 0xFFFF00FF);
            //always d = t1
            if (delta >= 0.0f)
                my_mlx_pp(raw, x, y, col);
            // else
            //     my_mlx_pp(raw, x, y, 0xFF000000);

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