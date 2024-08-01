/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/01 10:46:03 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world *setup_world()
{
	t_world     *new_w;

	new_w = my_malloc(sizeof(t_world), 1);
	new_w->light = init_light();
	new_w->spheres = init_sphere(0.7, get_tup(0, 0, 0, 0), get_vec(1, 0, 1));
	// new_w->spheres->next = init_sphere(0.4, get_tup(0, 0, 0, 0), get_vec(1, 0, 0));
	return (new_w);
}

void    draw_the_world(t_img *raw, t_world *w, t_cam *cam)
{
	t_ray			ray;
	t_intersection	head;
	t_matrix		tr_sc;
	int         	x;
	int         	y;
    double       	x_offset;
    double       	y_offset;
	t_sphere		*sph;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			x_offset = cam->half_width - (x + 0.5) * cam->pixel_move;
    		y_offset = cam->half_height - (y + 0.5) * cam->pixel_move;

			ray.origin = get_tup(0, 0, 1, -1);
			ray.direction = get_tup(x_offset, y_offset, -1, 1);

			tr_sc = multi_m(translate(0, 0, 0), scale(1, 1, 1));

			ray.direction = matrix_tuple(tr_sc, ray.direction);
			// ray.direction = matrix_tuple(rot_x(0), ray.direction);
			// ray.direction = matrix_tuple(rot_y(0), ray.direction);
			// ray.direction = matrix_tuple(rot_z(0), ray.direction);
			ray.direction = normalizer4(t_t(ray.direction, '-', ray.origin));

			head.count = 0;
			sph = w->spheres;
			// while (sph)
			// {
			intersect_sphere(*sph, ray, &head);
			// 	sph = sph->next;
			// }
			if (!_hit(&head))
				continue ;
			my_mlx_pp(raw, x, y, vrgb_conv(get_vec(1, 0, 1)));
		}
	}
}

int main()
{
	t_cam       *cam;
	t_world     *w;
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
//TODO that the hit() function returns 
//the intersection with the lowest NONNEGATIVE t value
