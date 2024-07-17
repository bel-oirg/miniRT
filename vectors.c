/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:17:49 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/17 20:39:38 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

float _dot(t_dot a, t_dot b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_dot *get_vec(float x, float y, float z)
{
    t_dot *point;

    point = malloc(sizeof(t_dot));
    point->x = x;
    point->y = y;
    point->z = z;
    return (point);
}

void vec_x_float(t_dot *point, float a)
{
    point->x *= a;
    point->y *= a;
    point->z *= a;
}

t_dot *set_hit_p(t_dot origin, t_dot direction, float close)
{
    t_dot *hit;

    hit = malloc(sizeof(t_dot));
    hit->x = origin.x + direction.x * close;
    hit->y = origin.y + direction.y * close;
    hit->z = origin.z + direction.z * close;
    return (hit);
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
    normal->x = (p->x)/len;
    normal->y = (p->y)/len;
    normal->z = (p->z)/len;
    return (normal);
}

unsigned int get_col(float d, unsigned int base_color)
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;

    alpha = ((base_color >> 24) & 255 ) * d;
    red = ((base_color >> 16) & 255) * d;
    green = ((base_color >> 8) & 255) * d;
    blue = ((base_color) & 255) * d;

    return ((alpha << 24) | (red << 16) | (green << 8) | (blue));
}

float degree_2(float a, float b, float c)
{
    float delta;
    float t1;
    float t2;

    delta = (b * b - 4.0f * a * c);
    if (delta < 0)
        return (NAN);
    t1 = (-b - sqrt(delta)) / (2.0f * a);
    t2 = (-b + sqrt(delta)) / (2.0f * a);
    return (t1);
}