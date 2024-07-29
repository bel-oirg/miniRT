/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/29 04:58:09 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world *setup_world()
{
    t_sphere    *sph;
    t_world     *new_w;

    new_w = my_malloc(sizeof(t_world), 1);
    new_w->light = init_light();
    
    new_w->spheres = init_sphere(0.7, get_vec(0.0f, 1.0f, 0), get_vec(1, 0, 0));
    new_w->spheres->next = init_sphere(0.2, get_vec(1, 0, 0), get_vec(1, 0, 1));
    sph = new_w->spheres;
    return (new_w);
}

t_inter *sort_intersections(t_inter *inter_head)
{
    t_inter *close_inter;

    close_inter = inter_head;
    while (inter_head && inter_head->next)
    {
        if (inter_head->h0 > inter_head->next->h0)
            close_inter = inter_head->next;
        inter_head = inter_head->next;
    }
    return (close_inter);
}

void    draw_the_world(t_img *raw, t_world *w, t_cam *cam)
{
    t_sphere    *sph;
    t_inter     *inter;
    t_inter     *inter_head;
    t_inter     *close_inter;
    t_dot       *hit_p;
    t_dot       *out_col;
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
            while (sph)
            {
                sphere_intersection(inter, sph, cam, x, y);
                sph = sph->next;
                inter->next = NULL;
                if (sph)
                    inter->next = my_malloc(sizeof(t_inter), 1);
                inter = inter->next;
            }
            close_inter = sort_intersections(inter_head);
            if (!close_inter->sph->hit || close_inter->h0 == INT_MAX)
                continue ;
            hit_p = v_v(cam->cam_o, '+', v_f(close_inter->sph->ray_d, '*', close_inter->sph->hit[0]));
            out_col = lighting(close_inter->sph->material, w->light,
                    hit_p, v_f(close_inter->sph->ray_d, '*', -1));
            my_mlx_pp(raw, x, y, vrgb_conv(out_col));
        }
    }
}

int main()
{
    t_buddha    *v;
    t_cam       *cam;
    t_world     *w;

    v = init_mlx();
    cam = init_cam();
    w = setup_world();

    draw_the_world(v->raw_img, w, cam);

    mlx_put_image_to_window(v->mlx, v->win, v->raw_img->img, 0, 0);
    mlx_hook(v->win, 17, 2, destroy_rt, v);
    mlx_hook(v->win, 2, 2, key_destroy, v);
    mlx_loop(v->mlx);
}

