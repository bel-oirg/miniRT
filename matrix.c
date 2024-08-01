/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 06:27:23 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/01 02:49:56 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_tuple get_tup(double x, double y, double z, double t)
{
    t_tuple _t;

    _t.t[0] = x;
    _t.t[1] = y;
    _t.t[2] = z;
    _t.t[3] = t;
    return (_t);
}

t_matrix    multi_m(t_matrix m1, t_matrix m2)
{
    t_matrix    multi;
    int         i;
    int         j;
    int         k;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
        {
            multi.m[i][j] = 0;
            k = -1;
            while (++k < 4)
                multi.m[i][j] += m1.m[i][k] * m2.m[k][j];
        }
    }
    return (multi);
}

t_matrix    transp_m(t_matrix m)
{
    t_matrix    trans;
    int         i;
    int         j;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            trans.m[i][j] = m.m[j][i];
    }
    return (trans);
}

t_tuple matrix_tuple(t_matrix m, t_tuple tup)
{
    t_tuple    mult;
    int         i;
    int         j;

    i = -1;
    while (++i < 4)
    {
        mult.t[i] = 0;
        j = -1;
        while (++j < 4)
            mult.t[i] += m.m[i][j] * tup.t[j];
    }
    return (mult);
}

double det_3x3(double m[3][3]) {
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
         - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
         + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

void    set_m3(t_matrix m, double m3[3][3], int c, int d)
{
    int     i;
    int     j;
    int     a;
    int     b;

    a = -1;
    i = -1;
    while (++i < 4)
    {
        if (c == i)
            continue ;
        a++;
        b = -1;
        j = -1;
        while (++j < 4)
        {
            if (j == d)
                continue ;
            m3[a][++b] = m.m[i][j];
        }
    }
}

double  determinant(t_matrix m)
{
    double  m3[3][3];
    double  det;
    int     i;
    int     sign;

    det = 0.0;
    sign = 1;
    i = -1;
    while (++i < 4)
    {
        set_m3(m, m3, 0, i);
        det += m.m[0][i] * sign * det_3x3(m3);
        sign = -sign;
    }
    return (det);
}

t_matrix  adjoint(t_matrix m)
{
    double      m3[3][3];
    t_matrix    adj;
    int         sign;
    int         i;
    int         j;

    sign = 1;
    i = -1;
    while (++i < 4)
    {
        j = -1;
        while(++j < 4)
        {
            sign = 1;
            set_m3(m, m3, i, j);
            if ((i + j) % 2)
                sign = -1;
            adj.m[j][i] = sign * det_3x3(m3);
        }
    }
    return (adj);
}

t_matrix    inv_m(t_matrix m)
{
    t_matrix    inv;
    t_matrix    adj;
    double      deter;
    int         i;
    int         j;

    deter = determinant(m);
    if (fabs(deter) < EPSILON)
    {
        printf("This matrix do not have an inverse\n");
        inv.m[0][0] = NAN;
    }
    adj = adjoint(m);
    i = -1;
    while (++i < 4)
    {
        j = -1;
        while(++j < 4)
            inv.m[i][j] = adj.m[i][j] / deter;
    }
    return (inv);
}

t_tuple normal_at(t_sphere sphere, t_tuple world_p)
{
    t_tuple obj_p;
    t_tuple obj_n;
    t_tuple world_n;

    obj_p = matrix_tuple(inv_m(sphere.transform), world_p);
    obj_n = t_t(obj_p, '-', get_tup(0, 0, 0, 0));
    world_n = matrix_tuple(transp_m(inv_m(sphere.transform)), obj_n);
    world_n.t[3] = 0;
    return (normalizer4(world_n));
}

/*
    function normal_at(sphere, world_point)
        object_point ← inverse(sphere.transform) * world_point
        object_normal ← object_point - point(0, 0, 0)
        world_normal ← transpose(inverse(sphere.transform)) * object_normal
        world_normal.w ← 0
        return normalize(world_normal)
    end function
*/

/*
    function position(ray, t)
        return ray.origin + ray.direction * t
    end function
*/