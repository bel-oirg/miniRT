/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:34:24 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/05 01:13:11 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple t_t(t_tuple t1, char op, t_tuple t2)
{
    t_tuple out = {0};

    if (op == '+')
    {
        out.x = t1.x + t2.x;
        out.y = t1.y + t2.y;
        out.z = t1.z + t2.z;
        out.w = t1.w + t2.w;
    }
    else if (op == '-')
    {
        out.x = t1.x - t2.x;
        out.y = t1.y - t2.y;
        out.z = t1.z - t2.z;
        out.w = t1.w - t2.w;
    }
    else if (op == '&')
    {
        out.x = t1.x * t2.x;
        out.y = t1.y * t2.y;
        out.z = t1.z * t2.z;
        out.w = t1.w * t2.w;
    }
    else
        printf("Unknown op\n");
    return (out);
}

double   get_length4(t_tuple a)
{
    return (sqrt(a.x * a.x + a.y * a.y
            + a.z * a.z + a.w * a.w));
}

t_tuple normalizer4(t_tuple p)
{
    t_tuple normalized;
    double  len;

    len = get_length4(p);
    if (len)
    {
        normalized.x = (p.x) / len;
        normalized.y = (p.y) / len;
        normalized.z = (p.z) / len;
        normalized.w = (p.w) / len;
        return (normalized);
    }
    normalized.x = 0;
    normalized.y = 0;
    normalized.z = 0;
    normalized.w = 0;
    printf("In normalizer4 len == 0, I returned (0,0,0,0)\n");
    return (normalized);
}

double  _dot4(t_tuple a, t_tuple b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

t_tuple t_f(t_tuple p, char op, float a)
{
    t_tuple out = {0};

    if (op == '+' || op == '-')
    {
        (op == '-') && (a = -a);
        out.x = p.x + a;
        out.y = p.y + a;
        out.z = p.z + a;
        out.w = p.w + a;
    }
    else if (op == '*' || op == '/')
    {
        if (op == '/')
        {
            if (a == 0)
            {
                printf("t_f division on 0, I retutned 0\n");
                return (out);
            }
            a = 1.0 / a;
        }
        out.x = p.x * a;
        out.y = p.y * a;
        out.z = p.z * a;
        out.w = p.w * a;
    }
    else
        printf("Unknown op");
    return (out);
}

/*
    function reflect(in, normal)
    return in - normal * 2 * dot(in, normal)
    end function
*/
t_tuple reflect(t_tuple in, t_tuple normal)
{
    t_tuple p1;

    p1 = t_f(normal, '*', 2.0 * _dot4(in, normal));
    return (t_t(in, '-', p1));
}

/*
    function position(ray, t)
        return ray.origin + ray.direction * t
    end function
*/
t_tuple position(t_ray ray, double t)
{
    return (t_t(ray.origin, '+', t_f(ray.direction, '*', t)));
}

unsigned int rgbt_uint(float r, float g, float b, float t)
{
    u_int8_t             transp;
    u_int8_t             red;
    u_int8_t             green;
    u_int8_t             blue;

    if (r > 1.0f)
        r = 1.0f;
    if (g > 1.0f)
        g = 1.0f;
    if (b > 1.0f)
        b = 1.0f;
    if (t > 1.0f)
        t = 1.0f;
    transp = 0;
    red = 255 * r;
    green = 255 * g;
    blue = 255 * b;

    return (transp << 24 | red << 16 | green << 8 | blue);
}

unsigned int t_rgbt(t_tuple t)
{
    return (rgbt_uint(t.x, t.y, t.z, t.w));
}