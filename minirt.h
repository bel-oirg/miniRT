/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:38:50 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/17 22:38:59 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define WIDTH  1000
#define HEIGHT 1000

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}   t_img;

typedef struct s_buddha
{
	t_img *raw_img;
	void *mlx;
	void *win;
}	t_buddha;

typedef struct s_dot
{
	float x;
	float y;
	float z;
}	t_dot;

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;


//my_malloc
void	*my_malloc(size_t size, int mode);

//vector
float degree_2(float a, float b, float c);
float _dot(t_dot a, t_dot b);
t_dot *get_vec(float x, float y, float z);
void vec_x_float(t_dot *point, float a);
unsigned int get_col(float d, unsigned int base_color);
t_dot *set_hit_p(t_dot origin, t_dot direction, float close);
t_dot *normalizer(t_dot *p);
void vec_plus_float(t_dot *point, float a);