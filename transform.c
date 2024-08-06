/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:34:59 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/06 01:20:53 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_matrix rotation(t_tuple norm) {
	double angle;
	double angle_cos;
	double angle_sin;
	double m_cos;
	t_matrix rot;
	t_tuple cros_p;
	
	angle = acos(_dot4(norm, get_tup(0, 1, 0, 0))); // the angle betw  norm_vec and y (0, 1, 0)
	cros_p = cros(norm, get_tup(0, 1, 0, 0));  // the cross product of norm and the y 
	angle_cos = cos(angle);
	angle_sin = sin(angle); // vals of rotation  matrix
	m_cos = 1.0 - angle_cos;;

	//rotation matrix elements
	rot.m[0][0] = angle_cos + (pow(cros_p.x, 2) * m_cos);
	rot.m[0][1] = (cros_p.x * cros_p.y * m_cos) - (cros_p.z * angle_sin);
	rot.m[0][2] = (cros_p.x * cros_p.z * m_cos) + (cros_p.y * angle_sin);
	rot.m[0][3] = 0;

	rot.m[1][0] = (cros_p.y * cros_p.x * m_cos) + (cros_p.z * angle_sin);
	rot.m[1][1] = angle_cos + (pow(cros_p.y, 2) * m_cos);
	rot.m[1][2] = (cros_p.y * cros_p.z * m_cos) - (cros_p.x * angle_sin);
	rot.m[1][3] = 0;

	rot.m[2][0] = (cros_p.z * cros_p.x * m_cos) - (cros_p.y * angle_sin);
	rot.m[2][1] = (cros_p.z * cros_p.y * m_cos) + (cros_p.x * angle_sin);
	rot.m[2][2] = angle_cos + (pow(cros_p.z, 2) * m_cos);
	rot.m[2][3] = 0;

	rot.m[3][0] = 0;
	rot.m[3][1] = 0;
	rot.m[3][2] = 0;
	rot.m[3][3] = 1;

	return rot;
}

t_tuple	cros(t_tuple v1, t_tuple v2)
{
	t_tuple	new;
	
	new.x = (v1.y * v2.z - v1.z * v2.y);
	new.y = (v1.z * v2.x - v1.x * v2.z);
	new.z = (v1.x * v2.y - v1.y * v2.x);
	new.w = 0;
	return (new);
}

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
