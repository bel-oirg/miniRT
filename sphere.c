/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 04:30:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/28 23:04:21 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
    Sphere equation : (x^2 - a^2) + (y^2 - b^2) + (z^2 - c^2) = r^2
*/

t_sphere *init_sphere(double raduis, t_dot *sphere_o, t_dot *color)
{
    t_sphere *sph;

    sph = my_malloc(sizeof(t_sphere), 1);
    sph->material = init_material(color);
    sph->raduis = raduis;
    sph->sphere_o = sphere_o;
    sph->next = NULL;
    return (sph);
}

void    sphere_intersection(t_inter *inter, t_sphere *sph, t_cam *cam, int x, int y)
{
    float       x_offset;
    float       y_offset;


    x_offset = (x + 0.5) * cam->pixel_move;
    y_offset = (y + 0.5) * cam->pixel_move;
    sph->ray_d = get_vec(cam->half_width - x_offset, cam->half_height - y_offset, 1.0f);
    // ray_d = v_v(ray_d, '+', cam->transf);

    sph->hit = degree_2( _dot(*sph->ray_d, *sph->ray_d),                    // a
                2.0f * _dot(*sph->sphere_o, *sph->ray_d),                   // b
            _dot(*sph->sphere_o, *sph->sphere_o) - pow(sph->raduis, 2));    // c
    if (sph->hit)
        inter->h0 = sph->hit[0],
        inter->h1 = sph->hit[1];
    else
        inter->h0 = INT_MAX,
        inter->h1 = INT_MAX;
    inter->type = SPHERE;
    inter->sph = sph;
}
