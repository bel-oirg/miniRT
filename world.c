/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 04:25:51 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/26 04:59:51 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world *setup_world(t_light *light)
{
    t_sphere    *sph;
    t_world     *new_w;

    new_w = my_malloc(sizeof(t_world), 1);
    new_w->light = light;
    new_w->count_objects = 0;
    new_w->spheres = init_sphere(0.2, get_vec(0, 0, 1), get_vec(1, 1, 0));
    new_w->spheres->next = init_sphere(0.7, get_vec(0, 0, 1), get_vec(1, 1, 1));
    sph = new_w->spheres;
    while(sph)
    {
        new_w->count_objects++;
        sph = sph->next;
    }
    new_w->all_hits = my_malloc(sizeof(double) * 2 * new_w->count_objects, 1);
    return (new_w);
}