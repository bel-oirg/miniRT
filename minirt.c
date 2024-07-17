/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/17 21:13:21 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void my_mlx_pp(t_img *raw, int x, int y, unsigned int color)
{
    char	*dst;

	dst = raw->addr + (y * raw->line_length + x * (raw->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void sphere(t_img *raw)
{
    int x;
    int y;
    
    t_dot *ray_o;
    t_dot *ray_d;
    t_dot *hit_p;
    // unsigned int col;
    unsigned int col;
    
    //degree 2, params
    float a;
    float b;
    float c;

    //raduis of the sphere
    float r;
    float close_p;
    
    r = 1.5f;
    ray_o = get_vec(0.0f, 0.0f, -2.0f);
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
            ray_d = get_vec((float)x/WIDTH, (float)y/HEIGHT, 0.5f);

            //to centralize the spher - [0, 1] --> [-1, 1]
            ray_d->x = ray_d->x * 2.0f - 1.0f;
            ray_d->y = ray_d->y * 2.0f - 1.0f;
            // ray_d->z = ray_d->z * 2.0f - 1.0f;

            //calculate the delta params
            a = _dot(*ray_d, *ray_d);
            b = 2.0f * _dot(*ray_o, *ray_d);
            c = _dot(*ray_o, *ray_o) - r*r;

            close_p = degree_2(a, b, c);
            if (isnan(close_p))
                continue ;

            hit_p = set_hit_p(*ray_o, *ray_d, close_p);
            
            normalize_p = normalizer(hit_p);

            light_d = normalizer(get_vec(-1.0f, -1.0f, -1.0f));

            d = fmax(_dot(*normalize_p, *light_d), 0.0f);
            /*
                (p . light_d) = cose(angle) - it gives us the diff angle
            */
            col = get_col((d * 0.5f) + 0.5f, 0xFFFF00FF);
            my_mlx_pp(raw, x, y, col);
        }
    }
}

void init_minirt(t_buddha *v)
{
    v->mlx = mlx_init(); //check if it fails
    v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "The miniRT");
    v->raw_img->img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
    v->raw_img->addr = mlx_get_data_addr(v->raw_img->img, &v->raw_img->bits_per_pixel, &v->raw_img->line_length, &v->raw_img->endian);

}

int	destroy_rt(t_buddha *v)
{
	mlx_destroy_window(v->mlx, v->win);
	my_malloc(0, 2);
	exit(0);
}

int key_hook_man(int key, t_buddha *v)
{
    (key == 53) && (destroy_rt(v));
    return (0);
}

int main()
{
    t_buddha *v;

    v = malloc(sizeof(t_buddha));
    v->raw_img = malloc(sizeof(t_img));
    init_minirt(v);
    sphere(v->raw_img);
    mlx_put_image_to_window(v->mlx, v->win, v->raw_img->img, 0, 0);
    mlx_hook(v->win, 17, 2, destroy_rt, v);
    mlx_hook(v->win, 2, 2, key_hook_man, v);
    mlx_loop(v->mlx);
}