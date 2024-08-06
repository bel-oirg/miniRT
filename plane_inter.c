/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:35:26 by abennar           #+#    #+#             */
/*   Updated: 2024/08/06 01:28:30 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void printMatrix(t_matrix matrix) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", matrix.m[i][j]);
        }
        printf("\n");
    }
}

t_object	insert_plane(t_plane plane)
{
	t_object	new;

	new.type = PLANE;
	new.plane = malloc(sizeof(plane));
	new.plane->point = plane.point;
	new.plane->norm_vec = plane.norm_vec;
	new.plane->next = NULL;
	return (new);
}

void		plane_trans(t_plane	*plane)
{
	t_matrix	trans;
	t_matrix	rotate;
	t_matrix	transform;	

	trans = translate(plane->point.x, plane->point.y, plane->point.z);
	rotate = rotation(plane->norm_vec);

	transform = multi_m(trans, rotate);

	for(int i = 0; i <= 4; i++)
		for (int j = 0; j <= 4; j++)
			(*plane->trans).m[i][j] = transform.m[i][j];
}

t_plane		*init_plane(t_dot	p, t_dot norm_vec)
{
	t_plane *plane;

	plane = malloc(sizeof(t_plane));
	plane->trans = malloc(sizeof(t_matrix));
	plane->norm_vec = get_tup(norm_vec.x, norm_vec.y, norm_vec.z, 0);
	plane->point = get_tup(p.x, p.y, p.z, 0);
	plane_trans(plane);
	
	plane->next = NULL;
	return (plane);
}

bool	intersect_plane(t_plane plane, t_ray ray, t_intersection *head)
{
	double			point;
	t_ray		new;

	if (fabs(ray.direction.y) < EPSILON)
		return false;

	// point = (plane.norm_vec->x * (plane.point->y - ray.origin.t[0]) + plane.norm_vec->y * 
	// 	(plane.point->y - ray.origin.t[1]) + plane.norm_vec->z * (plane.point->z - ray.origin.t[2])) /
	// 	(plane.norm_vec->x * ray.direction.t[0] + plane.norm_vec->y * ray.direction.t[1] + plane.norm_vec->z * ray.direction.t[2]);


	t_matrix invert = inv_m(*plane.trans);
	new.origin = matrix_tuple(invert, ray.origin);
	new.direction = matrix_tuple(invert, ray.direction);
	point =  (-1 * new.origin.y / new.direction.y);
	
	

	if (point > 0)
	{
		return true;
	}
	else return false;
	
// 	inter.object = insert_plane(plane);
// 	add_intersection(head, &inter);
}