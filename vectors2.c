/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 04:15:50 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/24 04:16:53 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float _dot(t_dot a, t_dot b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float   get_length(t_dot a)
{
    return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
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