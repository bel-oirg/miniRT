/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:34:24 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/02 07:52:02 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple t_t(t_tuple t1, char op, t_tuple t2)
{
    t_tuple out = {0};

    if (op == '+')
    {
        out.t[0] = t1.t[0] + t2.t[0];
        out.t[1] = t1.t[1] + t2.t[1];
        out.t[2] = t1.t[2] + t2.t[2];
        out.t[3] = t1.t[3] + t2.t[3];
    }
    else if (op == '-')
    {
        out.t[0] = t1.t[0] - t2.t[0];
        out.t[1] = t1.t[1] - t2.t[1];
        out.t[2] = t1.t[2] - t2.t[2];
        out.t[3] = t1.t[3] - t2.t[3];
    }
    else if (op == '&')
    {
        out.t[0] = t1.t[0] * t2.t[0];
        out.t[1] = t1.t[1] * t2.t[1];
        out.t[2] = t1.t[2] * t2.t[2];
        out.t[3] = t1.t[3] * t2.t[3];
    }
    else
        printf("Unknown op\n");
    return (out);
}


double   get_length4(t_tuple a)
{
    return (sqrt(a.t[0] * a.t[0] + a.t[1] * a.t[1]
            + a.t[2] * a.t[2] + a.t[3] * a.t[3]));
}

t_tuple normalizer4(t_tuple p)
{
    t_tuple normalized;
    double  len;

    len = get_length4(p);
    if (len)
    {
        normalized.t[0] = (p.t[0]) / len;
        normalized.t[1] = (p.t[1]) / len;
        normalized.t[2] = (p.t[2]) / len;
        normalized.t[3] = (p.t[3]) / len;
        return (normalized);
    }
    normalized.t[0] = 0;
    normalized.t[1] = 0;
    normalized.t[2] = 0;
    normalized.t[3] = 0;
    printf("In normalizer4 len == 0, I returned (0,0,0,0)\n");
    return (normalized);
}

double  _dot4(t_tuple a, t_tuple b)
{
    return (a.t[0] * b.t[0] + a.t[1] * b.t[1] + a.t[2] * b.t[2] + a.t[3] * b.t[3]);
}

t_tuple t_f(t_tuple p, char op, float a)
{
    t_tuple out = {0};

    if (op == '+' || op == '-')
    {
        (op == '-') && (a = -a);
        out.t[0] = p.t[0] + a;
        out.t[1] = p.t[1] + a;
        out.t[2] = p.t[2] + a;
        out.t[3] = p.t[3] + a;
    }
    else if (op == '*' || op == '/')
    {
        (op == '/') && (a = 1.0/a);
        out.t[0] = p.t[0] * a;
        out.t[1] = p.t[1] * a;
        out.t[2] = p.t[2] * a;
        out.t[3] = p.t[3] * a;
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

t_tuple position(t_ray ray, double t)
{
    return (t_t(ray.origin, '+', t_f(ray.direction, '*', t)));
}

/*
    function position(ray, t)
        return ray.origin + ray.direction * t
    end function
*/


unsigned int trgb_uint(float r, float g, float b, float t)
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
    transp = 1;
    red = 255 * r;
    green = 255 * g;
    blue = 255 * b;
    return (transp << 24 | red << 16 | green << 8 | blue);
}