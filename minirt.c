/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/25 02:13:57 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam *init_cam()
{
    t_cam *cam;

    cam = my_malloc(sizeof(t_cam), 1);
    cam->ratio = (double) WIDTH/HEIGHT;
    cam->field_of_view = 1.0f;
    cam->half_view = tan(cam->field_of_view / 2);
    cam->transf = get_vec(0.0f, 0.0f, 0.0f);
    cam->cam_o = get_vec(0.0f, 0.0f, -2.0f);
    if (cam->ratio >= 1)
        cam->half_width = cam->half_view,
        cam->half_height = cam->half_view / cam->ratio;
    else
        cam->half_width = cam->half_view * cam->ratio,
        cam->half_height = cam->half_view;

    cam->pixel_move = (cam->half_width * 2) / WIDTH;
    return (cam);
}

/*
    Sphere equation : (x^2 - a^2) + (y^2 - b^2) + (z^2 - c^2) = r^2
*/

void sphere(t_img *raw, t_sphere *sph, t_cam *cam, t_light *light)
{
    int x;
    int y;
    float x_offset;
    float y_offset;

    t_dot *ray_d;
    t_dot *hit_p;
    t_dot *origin;
    t_dot *out_col;

    origin = v_v(cam->cam_o, '-', sph->sphere_o);
    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            x_offset = (x + 0.5) * cam->pixel_move;
            y_offset = (y + 0.5) * cam->pixel_move;
            ray_d = get_vec(cam->half_width - x_offset, cam->half_height - y_offset, 1.0f);
            // ray_d = v_v(ray_d, '+', cam->transf);
            sph->hit = degree_2( _dot(*ray_d, *ray_d),   // a
                        2.0f * _dot(*origin, *ray_d),   // b
                    _dot(*origin, *origin) - pow(sph->raduis, 2));  // c
            if (!sph->hit)
                continue ;
            hit_p = v_v(origin, '+', v_f(ray_d, '*', sph->hit[0]));
            out_col = lighting(sph->material, light, hit_p, v_f(ray_d, '*', -1));
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

t_sphere *init_sphere(double raduis, t_dot *sphere_o, t_dot *color)
{
    t_sphere *sph;

    sph = my_malloc(sizeof(t_sphere), 1);
    sph->material = init_material(color);
    sph->raduis = raduis;
    sph->sphere_o = sphere_o;
    return (sph);
}

int main()
{
    t_buddha    *v;
    t_cam       *cam;
    t_light     *light;
    t_sphere    *sph;

    v = init_mlx();
    cam = init_cam();
    light = init_light();
    sph = init_sphere(0.5, get_vec(0, 0, 0), get_vec(1, 0, 0));

    sphere(v->raw_img, sph, cam, light);

    mlx_put_image_to_window(v->mlx, v->win, v->raw_img->img, 0, 0);
    mlx_hook(v->win, 17, 2, destroy_rt, v);
    mlx_hook(v->win, 2, 2, key_destroy, v);
    mlx_loop(v->mlx);
}

