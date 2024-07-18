/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/18 00:04:00 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void my_mlx_pp(t_img *raw, int x, int y, unsigned int color)
{
    char	*dst;

	dst = raw->addr + (y * raw->line_length + x * (raw->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int trgb_conv(float t, float r, float g, float b)
{
    int             trans;
    int             red;
    int             green;
    int             blue;

    trans = 255 * t;
    red = 255 * r;
    green = 255 * g;
    blue = 255 * b;
    return (trans << 24 | red << 16 | green << 8 | blue);
}


void sphere(t_img *raw)
{
    int x;
    int y;
    
    t_dot *ray_o;
    t_dot *ray_d;
    t_dot *hit_p;
    t_dot *light_d;

    // unsigned int col;
    unsigned int col;

    //raduis of the sphere
    float r;
    float close_p;

    r = 1.0f;
    ray_o = get_vec(0.0f, 0.0f, -2.0f);
    float d;

    /*
        Sphere equation : (x^2 - a^2) + (y^2 - b^2) + (z^2 - c^2) = r^2
    */

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            ray_d = get_vec((float)x/WIDTH, (float)y/HEIGHT, -0.0f);
            /*
                to centralize the spher - [0, 1] --> [-1, 1]
                ray_d = ray_d * 2.0f - 1.0f
            */
            vec_x_float(ray_d, 2.0f);
            vec_plus_float(ray_d, -1);

            close_p = degree_2( _dot(*ray_d, *ray_d), // a
                        2.0f * _dot(*ray_o, *ray_d),  // b
                        _dot(*ray_o, *ray_o) - r*r);  // c

            // plug t0 -> a + bt
            hit_p = normalizer(set_hit_p(*ray_o, *ray_d, close_p));
            light_d = normalizer(get_vec(1.0f, 1.0f, 1.0f));

            d = fmax(_dot(*hit_p, *light_d), 0.0f);
            // (p . light_d) = cos(angle) - it gives us the diff angle
            col = get_col((d * 0.5f) + 0.5f, trgb_conv(1.0f, 1.0f, 1.0f, 1));
            if (isnan(close_p))
                col =  trgb_conv(1.0f, 1.0f, 1.0f, 1.0f);
            my_mlx_pp(raw, x, y, col);
        }
    }
}



void init_minirt(t_buddha *v)
{
    v->mlx = mlx_init(); //TODO check if it fails
    v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "The miniRT");
    v->raw_img->img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
    v->raw_img->addr = mlx_get_data_addr(v->raw_img->img, 
                            &v->raw_img->bits_per_pixel,
                            &v->raw_img->line_length,
                            &v->raw_img->endian);
}

int	destroy_rt(t_buddha *v)
{
	mlx_destroy_window(v->mlx, v->win);
	my_malloc(0, 2);
	exit(0);
}

int key_destroy(int key, t_buddha *v)
{
    (key == 53) && (destroy_rt(v));
    return (0);
}

int main()
{
    t_buddha *v;

    v = my_malloc(sizeof(t_buddha), 1);
    v->raw_img = my_malloc(sizeof(t_img), 1);
    init_minirt(v);
    sphere(v->raw_img);
    mlx_put_image_to_window(v->mlx, v->win, v->raw_img->img, 0, 0);
    mlx_hook(v->win, 17, 2, destroy_rt, v);
    mlx_hook(v->win, 2, 2, key_destroy, v);
    mlx_loop(v->mlx);
}
//TODO work on resize
//TODO change colors [0, 255] -> [0, 1]

//shading models -> Phong reflection model