/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/24 04:03:06 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void my_mlx_pp(t_img *raw, int x, int y, unsigned int color)
{
    char	*dst;

	dst = raw->addr + (y * raw->line_length + x * (raw->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_dot *lighting(t_material *material, t_light *light, t_dot *point, t_dot *camerav, t_dot *normalv)
{
    t_dot *ambient;
    t_dot *specular;
    t_dot *diffuse;
    double factor;
    double light_dot_normal;
    t_dot *effective_color;
    double reflect_dot_eye;
    t_dot *lightv;
    t_dot *reflectv;

    effective_color = v_f(material->color, '*' ,light->intensity);
    lightv = normalizer(v_v(light->light_point, '-', point));
    ambient = v_f(effective_color,  '*',  material->ambient);

    light_dot_normal = _dot(*lightv, *normalv);
    if (light_dot_normal < 0)
    {
        
        diffuse = get_vec(0, 0, 0);
        specular = get_vec(0, 0, 0);
    }
    else
    {
        diffuse = v_f(effective_color,  '*',  (material->diffuse * light_dot_normal));
        reflectv = reflect(lightv, normalv);
        reflect_dot_eye = (double)_dot(*reflectv, *camerav);
        if (reflect_dot_eye <= 0)
            specular = get_vec(0, 0, 0);
        else
        {
            factor = pow(reflect_dot_eye, material->shininess);
            specular = v_f(get_vec(light->intensity, light->intensity, light->intensity), '*', material->specular * factor);
        }
    }
    return (v_v(v_v(ambient, '+', diffuse),  '+', specular));
}

unsigned int rgb_conv(float r, float g, float b)
{
    u_int8_t             red;
    u_int8_t             green;
    u_int8_t             blue;

    red = 255 * r;
    green = 255 * g;
    blue = 255 * b;
    return (red << 16 | green << 8 | blue);
}

void init_cam(t_cam *cam)
{
    cam->ratio = (double) WIDTH/HEIGHT;
    cam->field_of_view = 0.9f;
    cam->half_view = tan(cam->field_of_view/2);
    cam->transf = get_vec(0.0f, 0.0f, 0.0f);
    cam->cam_o = get_vec(0.0f, 0.0f, -2.0f);

    if (cam->ratio >= 1)
        cam->half_width = cam->half_view,
        cam->half_height = cam->half_view / cam->ratio;
    else
        cam->half_width = cam->half_view * cam->ratio,
        cam->half_height = cam->half_view;

    cam->pixel_move = (cam->half_width * 2) / WIDTH;
}

/*
    Sphere equation : (x^2 - a^2) + (y^2 - b^2) + (z^2 - c^2) = r^2
*/

void sphere(t_img *raw, float r, t_cam *cam)
{
    int x;
    int y;

    t_dot *ray_d;
    t_dot *hit_p;
    t_dot *light_d;
    t_dot *sphere_o;
    t_dot *origin;

    t_dot *out_col;

    float close_p;
    float x_offset;
    float y_offset;

    //----------
    t_material  *material = malloc(sizeof(t_material));
    t_light     *light = malloc(sizeof(t_light));

    material->ambient = 0.1;
    material->diffuse = 0.9;

    material->specular = 0.9;
    material->shininess = 200.0;
    material->color = get_vec(1, 0.2, 1);

    light->color = get_vec(1, 1, 1);
    light->light_point = get_vec(-10, 10, -10);
    light->intensity = 1;
    //----------

    sphere_o = get_vec(0.0f, 0.0f, 0.0f);
    origin = v_v(cam->cam_o, '-', sphere_o);
    light_d = normalizer(get_vec(1.0f, 1.0f, 1.0f));
    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            /*
                point ← position(ray, hit.t)                /// -> hit_p
                normal ← normal_at(hit.object, point)       /// normalize(hit_p)
                eye ← -ray.direction                        /// ray_d * -1

                color ← lighting(hit.object.material, light, point, eye, normal)
            */
            x_offset = (x + 0.5) * cam->pixel_move;
            y_offset = (y + 0.5) * cam->pixel_move;
            ray_d = get_vec(cam->half_width - x_offset, cam->half_height - y_offset, 1.0f);
            // ray_d = v_v(ray_d, '+', cam->transf);
            close_p = degree_2( _dot(*ray_d, *ray_d),   // a
                        2.0f * _dot(*origin, *ray_d),   // b
                        _dot(*origin, *origin) - r*r);  // c
            if (isnan(close_p))
                continue ;
            hit_p = v_v(origin, '+', v_f(ray_d, '*', close_p));
            // angle = _dot(*hit_p, *light_d) * 0.5f + 0.5f;
            out_col = lighting(material, light, hit_p, v_f(ray_d, '*', -1), normalizer(hit_p));
            my_mlx_pp(raw, x, y, rgb_conv(out_col->x, out_col->y, out_col->z));
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
    t_buddha    *v;
    t_cam       *cam;

    v = my_malloc(sizeof(t_buddha), 1);
    v->raw_img = my_malloc(sizeof(t_img), 1);
    cam = my_malloc(sizeof(t_cam), 1);
    init_minirt(v);
    init_cam(cam);
    sphere(v->raw_img, 0.3f, cam);
    mlx_put_image_to_window(v->mlx, v->win, v->raw_img->img, 0, 0);
    mlx_hook(v->win, 17, 2, destroy_rt, v);
    mlx_hook(v->win, 2, 2, key_destroy, v);
    mlx_loop(v->mlx);
}

