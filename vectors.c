/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:17:49 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/24 22:08:30 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_dot *normalizer(t_dot *p)
{
    float   len;
    float   x;
    float   y;
    float   z;
    
    len = get_length(*p);
    if (len)
    {
        x = (p->x)/len;
        y = (p->y)/len;
        z = (p->z)/len;
        return (get_vec(x, y, z));
    }
    return (get_vec(0, 0, 0));
}

/*
    function reflect(in, normal)
    return in - normal * 2 * dot(in, normal)
    end function
*/

t_dot *reflect(t_dot *in, t_dot *normal)
{
    t_dot *p1;

    p1 = v_f(normal, '*', 2.0f * _dot(*in, *normal));
    return (v_v(in, '-', p1));
}
