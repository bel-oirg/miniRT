/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 01:02:58 by abennar           #+#    #+#             */
/*   Updated: 2024/07/24 00:14:18 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float get_pixel_move();

void	cylinder(t_img *img)
{
	int	x;
	int	y;
	
	float	point;

	t_dot	*ray_o;
	t_dot	*ray_d;
	t_dot	*light_d;
	t_dot	*scale;
	
    light_d = normalizer(get_vec(2.0f, 2.0f, 2.0f));
    ray_o = get_vec(2.0f, 0.0f, 6.0f);
	
	
    scale = get_vec(2.0f, 2.0f, 2.0f);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
            ray_d = get_vec((float) x / WIDTH,(float) y / HEIGHT , 0.0f);
            ray_d = v_f(v_f(ray_d, '*', 2.0f), '-', 1.0f);
            ray_d = v_v(ray_d, '&', scale);
			
	
			
			point = degree_2(ray_d->x * ray_d->x + ray_d->z * ray_d->z,
					2.0f * ray_o->x * ray_d->x +
					2.0f * ray_o->z * ray_d->z,
			ray_o->x * ray_o->x + ray_o->z * ray_o->z - 1);
			if (isnan(point))
				continue;
			
			t_dot *hit_p = normalizer(v_v(ray_o, '+', v_f(ray_d, '*', point)));
            float angle = _dot(*hit_p, *light_d) * 0.5f + 0.5f;

            my_mlx_pp(img, x, y, get_col(angle, rgb_conv(1.0f, 1.0f, 1.0f)));
		}
	}
}