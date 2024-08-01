/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:34:59 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/01 02:27:42 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix    rot_x(double teta)
{
    t_matrix rotated;

	rotated.m[0][0] = 1;
	rotated.m[0][1] = 0;
	rotated.m[0][2] = 0;
	rotated.m[0][3] = 0;
	rotated.m[1][0] = 0;
	rotated.m[1][1] = cos(teta);
	rotated.m[1][2] = -sin(teta);
	rotated.m[1][3] = 0;
	rotated.m[2][0] = 0;
	rotated.m[2][1] = sin(teta);
	rotated.m[2][2] = cos(teta);
	rotated.m[2][3] = 0;
	rotated.m[3][0] = 0;
	rotated.m[3][1] = 0;
	rotated.m[3][2] = 0;
	rotated.m[3][3] = 1;
    return (rotated);
}

t_matrix	rot_y(double teta)
{
	t_matrix	rotated;

	rotated.m[0][0] = cos(teta);
    rotated.m[0][1] = 0;
	rotated.m[0][2] = sin(teta);
	rotated.m[0][3] = 0;
	rotated.m[1][0] = 0;
	rotated.m[1][1] = 1;
	rotated.m[1][2] = 0;
	rotated.m[1][3] = 0;
	rotated.m[2][0] = -sin(teta);
    rotated.m[2][1] = 0;
	rotated.m[2][2] = cos(teta);
    rotated.m[2][3] = 0;
    rotated.m[3][0] = 0;
	rotated.m[3][1] = 0;
	rotated.m[3][2] = 0;
	rotated.m[3][3] = 1;
	return (rotated);
}

t_matrix	rot_z(double teta)
{
	t_matrix	rotated;

	rotated.m[0][0] = cos(teta);
	rotated.m[0][1] = -sin(teta);
	rotated.m[0][2] = 0;
	rotated.m[0][3] = 0;
    rotated.m[1][0] = sin(teta);
	rotated.m[1][1] = cos(teta);
	rotated.m[1][2] = 0;
	rotated.m[1][3] = 0;
    rotated.m[2][0] = 0;
    rotated.m[2][1] = 0;
    rotated.m[2][2] = 1;
    rotated.m[2][3] = 0;
    rotated.m[3][0] = 0;
	rotated.m[3][1] = 0;
	rotated.m[3][2] = 0;
	rotated.m[3][3] = 1;
	return (rotated);
}

t_matrix	scale(double x, double y, double z)
{
	t_matrix	scale;

	scale.m[0][0] = x;
	scale.m[0][1] = 0;
	scale.m[0][2] = 0;
	scale.m[0][3] = 0;
    scale.m[1][0] = 0;
	scale.m[1][1] = y;
	scale.m[1][2] = 0;
	scale.m[1][3] = 0;
    scale.m[2][0] = 0;
    scale.m[2][1] = 0;
    scale.m[2][2] = z;
    scale.m[2][3] = 0;
    scale.m[3][0] = 0;
	scale.m[3][1] = 0;
	scale.m[3][2] = 0;
	scale.m[3][3] = 1;
	return (scale);
}

t_matrix	translate(double x, double y, double z)
{
	t_matrix	trans;

	trans.m[0][0] = 1;
	trans.m[0][1] = 0;
	trans.m[0][2] = 0;
	trans.m[0][3] = x;
    trans.m[1][0] = 0;
	trans.m[1][1] = 1;
	trans.m[1][2] = 0;
	trans.m[1][3] = y;
    trans.m[2][0] = 0;
    trans.m[2][1] = 0;
    trans.m[2][2] = 1;
    trans.m[2][3] = z;
    trans.m[3][0] = 0;
	trans.m[3][1] = 0;
	trans.m[3][2] = 0;
	trans.m[3][3] = 1;
	return (trans);
}
