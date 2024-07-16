/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:38:50 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/16 16:46:36 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define WIDTH  1000
#define HEIGHT 1000

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	t_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}   t_img;

typedef struct s_dot
{
	float x;
	float y;
	float z;
}	t_dot;

float _dot(t_dot a, t_dot b);
void set_dot(t_dot *point, float x, float y, float z);
void vec_float(t_dot *point, float a);
void set_hit_p(t_dot *hit, t_dot origin, t_dot direction, float close);
t_dot *normalizer(t_dot *p);