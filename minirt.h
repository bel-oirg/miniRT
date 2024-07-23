/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:38:50 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/24 00:22:19 by abennar          ###   ########.fr       */
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

typedef struct s_cam
{
    t_dot *transf;
	t_dot *cam_o;
    double field_of_view;
    double half_view;
    double half_width;
    double half_height;
	double ratio;
	double pixel_move;
} t_cam;

//my_malloc
void	*my_malloc(size_t size, int mode);

void my_mlx_pp(t_img *raw, int x, int y, unsigned int color);
unsigned int rgb_conv(float r, float g, float b);

//vector
float degree_2(float a, float b, float c);
float _dot(t_dot a, t_dot b);
t_dot *get_vec(float x, float y, float z);
unsigned int get_col(float d, unsigned int base_color);
t_dot *set_hit_p(t_dot origin, t_dot direction, float close);
t_dot *normalizer(t_dot *p);
t_dot *v_v(t_dot *p1, char op, t_dot *p2);
t_dot *v_f(t_dot *p, char op, float a);

//rotation matrix
t_dot	*rot_x(t_dot ray, double norm_angle);
t_dot	*rot_y(t_dot ray, double norm_angle);
t_dot	*rot_z(t_dot ray, double norm_angle);
