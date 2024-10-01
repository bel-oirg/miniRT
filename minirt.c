/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/10/01 10:16:02 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world setup_world()
{
	t_world     new_w;

	new_w.light = init_light();
	new_w.spheres = init_sphere(0.6, get_tup(1, 0, 0, 0), get_tup(1, 0.2, 1, 0));
	return (new_w);
}

void    draw_the_world(t_img *raw, t_world w, t_cam *cam)
{
	t_ray			ray;
	t_intersection	head;
	t_intersection	*closest;
	int         	x;
	int         	y;
    double       	x_offset;
    double       	y_offset;
	t_sphere		*sph;
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

			ray.origin = get_tup(0, 0, 2, 0);
			ray.direction = get_tup(x_offset, y_offset, -1, 0);

			ray.direction = matrix_tuple(multi_m(translate(0, 0, 0),
					scale(1, 1, 1)), ray.direction);
			// ray.direction = matrix_tuple(rot_x(0), ray.direction);
			// ray.direction = matrix_tuple(rot_y(0), ray.direction);
			// ray.direction = matrix_tuple(rot_z(0), ray.direction);
			ray.direction = normalizer4(t_t(ray.direction, '-', ray.origin));
			head.count = 0;
			sph = w.spheres;
			while (sph)
			{
				intersect_sphere(*sph, ray, &head);
				sph = sph->next;
			}
			closest = _hit(&head);
			if (!closest)
				continue ;
			point = position(ray, closest->t);
			normalv = normal_at(*closest->object.sphere, point);
			eyev = t_f(ray.direction, '*', -1);

			final_col =  t_rgbt(lighting(*closest->object.sphere->material,
						*w.light, point, eyev, normalv));
			my_mlx_pp(raw, x, y, final_col);
		}
	}
}

int main()
{
	t_cam       *cam;
	t_world     w;
	t_buddha    *v;

	v = init_mlx();
	cam = init_cam();
	w = setup_world();

	draw_the_world(v->raw_img, w, cam);

	mlx_put_image_to_window(v->mlx, v->win, v->raw_img->img, 0, 0);
	mlx_hook(v->win, 17, 2, destroy_rt, v);
	mlx_hook(v->win, 2, 2, key_destroy, v);
	mlx_loop(v->mlx);
}

//TODO PREPARE_COMPUTATION