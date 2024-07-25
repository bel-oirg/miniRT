/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:38:50 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/25 02:14:31 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define WIDTH  1200
#define HEIGHT 1200

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
}	t_cam;

typedef struct s_material
{
    t_dot	*color;
    double	ambient;
    double	diffuse;
    double	specular;
    double	shininess;
}	t_material;

typedef struct s_light
{
	double	intensity;
	t_dot	*color;
	t_dot	*light_point;
}	t_light;

typedef struct s_phong
{
    t_dot *ambient;
    t_dot *specular;
    t_dot *diffuse;
    t_dot *lightv;
    t_dot *reflectv;
    t_dot *effective_color;
    double factor;
    double light_dot_normal;
    double reflect_dot_eye;
}	t_phong;

// typedef struct s_world
// {
//     t_light *light;
//     t_cam   *cam;

//     t_sphere sph1, ...;
//     t_cylinder 

// }   t_world;

typedef struct s_sphere
{
    double      *hit;
    t_material  *material;
    double      raduis;
    t_dot       *sphere_o;
    struct      s_sphere *next;
} t_sphere;

//my_malloc
void	*my_malloc(size_t size, int mode);

//vectors
t_dot *get_vec(float x, float y, float z);
t_dot *normalizer(t_dot *p);
t_dot *v_v(t_dot *p1, char op, t_dot *p2);
t_dot *v_f(t_dot *p, char op, float a);
t_dot *reflect(t_dot *in, t_dot *normal);

//vectors2
float _dot(t_dot a, t_dot b);
float   get_length(t_dot a);
double *degree_2(float a, float b, float c);

//ft_mlx
int key_destroy(int key, t_buddha *v);
void my_mlx_pp(t_img *raw, int x, int y, unsigned int color);
int	destroy_rt(t_buddha *v);
t_buddha *init_mlx();

//rotation matrix
t_dot	*rot_x(t_dot ray, double norm_angle);
t_dot	*rot_y(t_dot ray, double norm_angle);
t_dot	*rot_z(t_dot ray, double norm_angle);

//colors
unsigned    int rgb_conv(float r, float g, float b);
unsigned    int vrgb_conv(t_dot *color);
unsigned    int get_col(float d, unsigned int base_color);
t_dot       *rgb_v(unsigned int base_color);

//lighting
t_light *init_light();
t_dot *lighting(t_material *material, t_light *light, t_dot *point, t_dot *camerav);
