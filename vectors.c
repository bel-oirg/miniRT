/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:17:49 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/15 17:27:51 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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