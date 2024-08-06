/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 02:26:27 by abennar           #+#    #+#             */
/*   Updated: 2024/08/06 01:30:21 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    draw_the_world(t_img *raw, t_world w, t_cam *cam)
{
	t_ray			ray;
	t_intersection	head;
	t_intersection	*closest;
	int         	x;
	int         	y;
    double       	x_offset;
    double       	y_offset;
	// t_sphere		*sph;
	u_int32_t		final_col;
	t_tuple			point;
	t_tuple			normalv;
	t_tuple			eyev;


	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			x_offset = cam->half_width - (x + 0.5) * cam->pixel_move;
    		y_offset = cam->half_height - (y + 0.5) * cam->pixel_move;

			ray.origin = get_tup(0,0.5,-8,-8);
			ray.direction = get_tup(x_offset, y_offset, -1, 1);

			ray.direction = matrix_tuple(multi_m(translate(0, 0, 0),
					scale(1, 1, 1)), get_tup(cam->half_width - x_offset, cam->half_height - y_offset, -1, 0));
			ray.direction = normalizer4(t_t(ray.direction, '-', ray.origin));
			// head.count = 0;
			t_plane	*pln;
			// pln = w.planes;
			// while (pln)
			// {
			// 	// intersect_sphere(*sph, ray, &head);
			// 	pln = pln->next;
			// }
			if (!intersect_plane(*w.planes, ray, &head))
				continue;
				
				
			// closest = _hit(&head);
			// if (!closest)
			// 	continue ;
			// point = position(ray, closest->t);
			// normalv = normal_at(*closest->object.sphere, point);
			// eyev = t_f(ray.direction, '*', -1);

			// final_col =  t_rgbt(lighting(*closest->object.sphere->material,
			// 			*w.light, point, eyev, normalv));
			my_mlx_pp(raw, x, y, 255  );
		}
	}
}