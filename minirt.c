/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/02 12:14:55 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world setup_world()
{
	t_world     new_w;

	new_w.light = init_light();
	new_w.spheres = init_sphere(0.6, get_tup(0, 0, 0, 0), get_tup(0, 0, 1, 0));
	// new_w->spheres->next = init_sphere(0.4, get_tup(0, 0, 0, 0), get_vec(1, 0, 0));
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
	t_tuple			col_t;
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

			// ray.direction = matrix_tuple(multi_m(translate(0, 0, 0),
			// 		scale(1, 1, 1)), ray.direction);
			// ray.direction = matrix_tuple(rot_x(0), ray.direction);
			// ray.direction = matrix_tuple(rot_y(0), ray.direction);
			// ray.direction = matrix_tuple(rot_z(0), ray.direction);
			ray.direction = normalizer4(t_t(ray.direction, '-', ray.origin));

/*
	transform = view_transform(cam->view, add_tuple(cam->view,
		cam->pos), cross_product(cross_product(cam->pos,
		create_tuple(0, 1, 0, 0)), cam->pos));
	cam->transform = invert_matrix(transform);
	camera_pixel_size(rt, cam);
	cam->origin = mult_matrix_tuple(cam->transform, create_tuple(0, 0, 0, 1));
*/

/*
	direction = normalize_v(subtract_tuple(mult_matrix_tuple(cam->transform,
		create_tuple(cam->half_width - x_offset,
		cam->half_height - y_offset, -1, 1)), cam->origin));
*/

			head.count = 0;
			sph = w.spheres;
			// while (sph)
			// {
			intersect_sphere(*sph, ray, &head);
			// 	sph = sph->next;
			// }
			closest = _hit(&head);
			if (!closest)
				continue ;
			/*
				point ← position(ray, hit.t)
				normal ← normal_at(hit.object, point)
				eye ← -ray.direction
			*/
			point = position(ray, closest->t);
			// point()
			normalv = normal_at(*sph, point);
			eyev = t_f(ray.direction, '*', -1);


			col_t = lighting(*sph->material, *w.light, point, eyev, normalv);
			printf("eyev %f \nnormalv %f \n", eyev.t[3], normalv.t[3]);
			// printf("col3 -> %f\n", col_t.t[3]);
			final_col = rgbt_uint(col_t.t[0], col_t.t[1], col_t.t[2], col_t.t[3]);
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

// int main()
// {
// 	t_material	m;
// 	t_light		light;
// 	t_tuple		eyev;
// 	t_tuple		normalv;
// 	t_tuple		out;
// 	t_tuple		position;

// 	m.ambient = 0.1;  //?
// 	m.diffuse = 0.9;
// 	m.specular = 0.9;
// 	m.shininess = 200.0;
// 	m.color = get_tup(1, 1, 1, 0); //CHECK THIS idk

// 	eyev = get_tup(0, 0, -1, 0); //this 0
// 	// eyev = get_tup(0, -sqrt(1.0/2), -sqrt(1.0/2), 0); //this 0

// 	normalv = get_tup(0, 0, -1, 0); //this 0  hmm

// 	light.light_point = get_tup(0, 0, 10, 1); //this 1
// 	light.intensity = 1.0;
// 	light.color = get_tup(1, 1, 1, 0);
	
// 	position = get_tup(0, 0, 0, 1); //this 1
// 	out = lighting(m, light, position, eyev, normalv);
	
// 	printf("%f %f %f %f\n", out.t[0], out.t[1], out.t[2], out.t[3]);
// 	printf("%d\n", rgbt_uint(0.1, 0.2, 0.3, 0));
// }

//TODO PREPARE_COMPUTATION