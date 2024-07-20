/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:17:49 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/20 23:16:44 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float _dot(t_dot a, t_dot b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_dot *get_vec(float x, float y, float z)
{
    t_dot *point;

    point = my_malloc(sizeof(t_dot), 1);
    point->x = x;
    point->y = y;
    point->z = z;
    return (point);
}

t_dot *v_f(t_dot *p, char op, float a)
{
    float   x;
    float   y;
    float   z;

    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    if (op == '+' || op == '-')
    {
        (op == '-') && (a = -a);
        x = p->x + a;
        y = p->y + a;
        z = p->z + a;
    }
    else if (op == '*' || op == '/')
    {
        (op == '/') && (a = 1.0f/a);
        x = p->x * a;
        y = p->y * a;
        z = p->z * a;
    }
    else
        return (printf("Unknown op"), NULL);
    return (get_vec(x, y, z));
}

t_dot *v_v(t_dot *p1, char op, t_dot *p2)
{
    float x;
    float y;
    float z;

    if (op == '+')
    {
        x = p1->x + p2->x;
        y = p1->y + p2->y;
        z = p1->z + p2->z;
    }
    else if (op == '-')
    {
        x = p1->x - p2->x;
        y = p1->y - p2->y;
        z = p1->z - p2->z;
    }
    else if (op == '&')
    {
        x = p1->x * p2->x;
        y = p1->y * p2->y;
        z = p1->z * p2->z;
    }
    else
        return (printf("Unknown op"), NULL);
    return (get_vec(x, y, z));
}

t_dot *set_hit_p(t_dot origin, t_dot direction, float close)
{
    t_dot *hit;

    hit = my_malloc(sizeof(t_dot), 1);
    hit->x = origin.x + direction.x * close;
    hit->y = origin.y + direction.y * close;
    hit->z = origin.z + direction.z * close;
    return (hit);
}

float   get_length(t_dot a)
{
    return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_dot *normalizer(t_dot *p)
{
    float   len;
    
    t_dot *normal = my_malloc(sizeof(t_dot), 1);
    len = get_length(*p);
    normal->x = (p->x)/len; //TODO CHECK if len == 0
    normal->y = (p->y)/len;
    normal->z = (p->z)/len;
    return (normal);
}

unsigned int get_col(float d, unsigned int base_color)
{
    u_int8_t red;
    u_int8_t green;
    u_int8_t blue;

    red = ((base_color >> 16) & 255) * d;
    green = ((base_color >> 8) & 255) * d;
    blue = ((base_color) & 255) * d;

    return ((red << 16) | (green << 8) | (blue));
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