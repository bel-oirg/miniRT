/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:34:24 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/01 06:50:37 by bel-oirg         ###   ########.fr       */
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
