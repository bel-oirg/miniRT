/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 04:08:24 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/24 04:09:40 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void my_mlx_pp(t_img *raw, int x, int y, unsigned int color)
{
    char	*dst;

	dst = raw->addr + (y * raw->line_length + x * (raw->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void init_mlx(t_buddha *v)
{
    v->mlx = mlx_init(); //TODO check if it fails
    v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "The miniRT");
    v->raw_img->img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
    v->raw_img->addr = mlx_get_data_addr(v->raw_img->img, 
                            &v->raw_img->bits_per_pixel,
                            &v->raw_img->line_length,
                            &v->raw_img->endian);
}

int	destroy_rt(t_buddha *v)
{
	mlx_destroy_window(v->mlx, v->win);
	my_malloc(0, 2);
	exit(0);
}

int key_destroy(int key, t_buddha *v)
{
    (key == 53) && (destroy_rt(v));
    return (0);
}