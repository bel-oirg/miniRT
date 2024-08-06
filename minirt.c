/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:37:52 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/05 01:24:24 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_world setup_world()
{
	t_world     new_w;

	new_w.light = init_light();
	// new_w.spheres = init_sphere(0.6, get_tup(0, 0, 0, 0), get_tup(1, 0.2, 1, 0));
	new_w.planes = init_plane((t_dot){0, 0, 0}, (t_dot){0,0,1});
	// new_w.spheres->next = init_sphere(0.7, get_tup(0, 0, 0, 0), get_tup(0, 1, 1, 0));
	return (new_w);
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