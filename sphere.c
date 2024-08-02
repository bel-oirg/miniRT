/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 04:30:26 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/02 03:23:45 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
    Sphere equation : (x^2 - a^2) + (y^2 - b^2) + (z^2 - c^2) = r^2
*/

t_sphere *init_sphere(double raduis, t_tuple sphere_o, t_tuple color)
{
    t_sphere    *sph;

    sph = my_malloc(sizeof(t_sphere), 1);
    sph->material = init_material(color);
    /*
        you can remove the rotation on the sphere
        TODO you should invert the transform matrix
    */
    sph->transform = translate(0, 0, 0);
    sph->raduis = raduis;
    sph->sphere_o = sphere_o;
    sph->next = NULL;
    return (sph);
}

