/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 06:47:49 by abennar           #+#    #+#             */
/*   Updated: 2024/07/31 07:03:11 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void plane(t_img *img, t_cam *cam)
{
    t_dot *o;
    t_dot *d;
    t_dot *nv;
    t_dot   *scale;
    int x, y;

    nv = get_vec(0, 1, 0); // the normal vector 
    t_dot   *p  = get_vec(1, 1, 1); // the coordinates of a point on the plane
    float   pixel_move = cam->pixel_move;

    scale = get_vec(2.0f, 2.0f, 2.0f);

    o = get_vec(0.0f, 0.0f, 0.0f);

    
    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
                d = get_vec((float)x * pixel_move , (float)y  * pixel_move, 0.0f);

                d = v_f(v_f(d, '*', 2.0f), '-', 1.0f);

                 d = v_v(d, '&', scale);

                float point =  (nv->x * (p->x - o->x) + nv->y * (p->y - o->y) + nv->z * (p->z - o->z)) /
                                (nv->x * d->x + nv->y * d->y + nv->z * d->z);

                if (point <= 0)
                    continue;
                my_mlx_pp(img, x, y, rgb_conv(0.8235, 0.8235, 0.8235));
        }
    }
}
