/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:17:49 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/16 16:46:32 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

float _dot(t_dot a, t_dot b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void set_dot(t_dot *point, float x, float y, float z)
{
    point->x = x;
    point->y = y;
    point->z = z;
}

void vec_float(t_dot *point, float a)
{
    point->x *= a;
    point->y *= a;
    point->z *= a;
}

void set_hit_p(t_dot *hit, t_dot origin, t_dot direction, float close)
{
    hit->x = origin.x + direction.x * close;
    hit->y = origin.y + direction.y * close;
    hit->z = origin.z + direction.z * close;
}

float   get_lengh(t_dot a)
{

    return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_dot *normalizer(t_dot *p)
{
    float   len;
    
    t_dot *normal = malloc(sizeof(t_dot));
    if (!normal)
        return ((t_dot *)NULL);
    len = get_lengh(*p);
    normal->x = p->x/len;
    normal->y = p->y/len;
    normal->z = p->z/len;
    return (normal);
}