/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/26 07:56:00 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    draw_the_world(t_img *raw, t_world *w, t_cam *cam, t_light *light)
{
    int x;
    int y;
    t_dot   *hit_p;
    t_dot   *out_col;
    t_dot   *origin;
    t_sphere    *sph;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            sph = w->spheres;
            origin = v_v(cam->cam_o, '-', sph->sphere_o);
            
            sphere_intersection(sph, cam, x, y);
            if (!sph->hit[0])
                continue ;
            
            hit_p = v_v(origin, '+', v_f(sph->ray_d, '*', sph->hit[0]));

            out_col = lighting(sph->material, light, hit_p, v_f(sph->ray_d, '*', -1));
            my_mlx_pp(raw, x, y, vrgb_conv(out_col));
        }
    }
}

t_material  *init_material(t_dot *color)
{
    t_material  *material;

    material = my_malloc(sizeof(t_material), 1);
    material->ambient = 0.1;
    material->diffuse = 0.9;
    material->specular = 0.9;
    material->shininess = 200.0;
    material->color = color;
    return (material);
}

int main()
{
    t_buddha    *v;
    t_cam       *cam;
    t_light     *light;
    t_world     *world;
    
    v = init_mlx();
    cam = init_cam();
    light = init_light();
    world = setup_world(light);

    draw_the_world(v->raw_img, world, cam, light);

    mlx_put_image_to_window(v->mlx, v->win, v->raw_img->img, 0, 0);
    mlx_hook(v->win, 17, 2, destroy_rt, v);
    mlx_hook(v->win, 2, 2, key_destroy, v);
    mlx_loop(v->mlx);
}

