/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/28 22:26:38 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam   *init_cam()
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

t_world *setup_world(t_light *light)
{
    t_sphere    *sph;
    t_world     *new_w;

    new_w = my_malloc(sizeof(t_world), 1);
    new_w->light = light;
    new_w->count_objects = 0;
    new_w->spheres = init_sphere(0.1, get_vec(0, 0, -1), get_vec(1, 1, 0));
    new_w->spheres->next = init_sphere(0.2, get_vec(0, 0, -1), get_vec(1, 1, 1));
    sph = new_w->spheres;
    while (sph)
    {
        new_w->count_objects++;
        sph = sph->next;
    }
    new_w->all_hits = my_malloc(sizeof(double) * 2 * new_w->count_objects, 1);
    return (new_w);
}

void    draw_the_world(t_img *raw, t_world *w, t_cam *cam, t_light *light)
{
    t_sphere    *sph;
    t_inter     *inter;
    t_inter     *inter_head;
    t_inter     *close_inter;
    t_dot       *hit_p;
    t_dot       *out_col;
    t_dot       *origin;
    int         x;
    int         y;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            inter_head = my_malloc(sizeof(t_inter), 1);
            inter = inter_head;

            sph = w->spheres;
            origin = v_v(cam->cam_o, '-', w->spheres->sphere_o);
            
            while(sph)
            {
                sphere_intersection(sph, cam, x, y);
                if (sph->hit)
                    inter->h0 = sph->hit[0],
                    inter->h1 = sph->hit[1];
                else
                    inter->h0 = INT_MAX,
                    inter->h1 = INT_MAX;
                inter->type = SPHERE;
                inter->sph = sph;
                sph = sph->next;
                inter->next = NULL;
                if (sph)
                    inter->next = my_malloc(sizeof(t_inter), 1);
                inter = inter->next;
            }
            inter = NULL;

            close_inter = inter_head;
            while (inter_head && inter_head->next)
            {
                if (inter_head->h0 > inter_head->next->h0)
                    close_inter = inter_head->next;
                inter_head = inter_head->next;
            }
            if (!close_inter->sph->hit)
                continue;
            if (close_inter->h0 == INT_MAX)
                continue;
            hit_p = v_v(origin, '+', v_f(close_inter->sph->ray_d, '*', close_inter->sph->hit[0]));

            // out_col = lighting(w->spheres->material, light, hit_p, v_f(w->spheres->ray_d, '*', -1));
            out_col = lighting(close_inter->sph->material, light, hit_p, v_f(close_inter->sph->ray_d, '*', -1));
            my_mlx_pp(raw, x, y, vrgb_conv(out_col));
        }
    }
}


int main()
{
    t_buddha    *v;
    t_cam       *cam;
    t_light     *light;
    t_world     *w;

    v = init_mlx();
    cam = init_cam();
    light = init_light();
    w = setup_world(light);

    draw_the_world(v->raw_img, w, cam, light);

    mlx_put_image_to_window(v->mlx, v->win, v->raw_img->img, 0, 0);
    mlx_hook(v->win, 17, 2, destroy_rt, v);
    mlx_hook(v->win, 2, 2, key_destroy, v);
    mlx_loop(v->mlx);
}

