/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:38:50 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/02 12:18:02 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define WIDTH   800
#define HEIGHT  800
#define EPSILON 0.00001

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct	s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}   t_img;

typedef struct s_buddha
{
	t_img			*raw_img;
	void			*mlx;
	void			*win;
}	t_buddha;

typedef struct s_dot
{
	float			x;
	float			y;
	float			z;
}	t_dot;

typedef struct s_tuple
{
	double			t[4];
}   t_tuple;

typedef struct s_matrix
{
	double			m[4][4];
}   t_matrix;

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

typedef struct s_cam
{
	t_tuple     	cam_o;
	double      	field_of_view;
	double      	half_view;
	double      	half_width;
	double      	half_height;
	double      	ratio;
	double			pixel_move;
}	t_cam;

typedef struct s_material
{
	t_tuple			color;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
}	t_material;

typedef struct s_light
{
	t_tuple			color;
	t_tuple			light_point;
}	t_light;

typedef struct s_phong
{
	t_tuple			ambient;
	t_tuple			specular;
	t_tuple			diffuse;
	t_tuple			lightv;
	t_tuple			reflectv;
	t_tuple			effective_color;
	double			factor;
	double			light_dot_normal;
	double			reflect_dot_eye;
}	t_phong;

typedef struct s_sphere
{
	t_material		*material;
	t_matrix        transform;
	t_tuple         sphere_o;
	double          raduis;
	struct s_sphere *next;
}   t_sphere;

typedef struct s_plane
{
	t_material		*material;
	//you can apply the trans
}   t_plane;

typedef struct s_world
{
	t_light			*light;
	t_sphere		*spheres;
}   t_world;

typedef enum    s_type
{
	SPHERE,
	CYLINDER,
	PLANE
}   t_type;

typedef struct s_object
{
	t_type      	type;
	t_sphere    	*sphere;
	// t_cylinder  *cylinder;
	// t_splane    *plane;
}   t_object;

typedef struct s_ray
{
	t_tuple   origin;
	t_tuple   direction;
}   t_ray;

typedef struct s_intersection
{
	double                  t;
	int                     count;
	t_object                object;
	struct s_intersection   *next;
} t_intersection;

//my_malloc
void	*my_malloc(size_t size, int mode);

//vectors
t_dot		*get_vec(float x, float y, float z);
t_dot		*normalizer(t_dot *p);
t_dot		*v_v(t_dot *p1, char op, t_dot *p2);
t_dot		*v_f(t_dot *p, char op, float a);

//vectors2
float		_dot(t_dot a, t_dot b);
float		get_length(t_dot a);

//ft_mlx
int			key_destroy(int key, t_buddha *v);
void		my_mlx_pp(t_img *raw, int x, int y, unsigned int color);
int			destroy_rt(t_buddha *v);
t_buddha	*init_mlx();

//rotation matrix
t_matrix	rot_x(double teta);
t_matrix	rot_y(double teta);
t_matrix	rot_z(double teta);

//colors
unsigned    int rgb_conv(float r, float g, float b);
unsigned    int vrgb_conv(t_dot *color);
unsigned    int get_col(float d, unsigned int base_color);
t_dot       *rgb_v(unsigned int base_color);

//lighting
t_light		*init_light();
t_tuple		lighting(t_material material, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv);
int         is_shadowed(t_world *w, t_cam *cam, t_dot *point);

//material
t_material	*init_material(t_tuple color);


//sphere
t_sphere *init_sphere(double raduis, t_tuple sphere_o, t_tuple color);

//cam
t_cam		*init_cam();

//simple_plane   //TMP
void		draw_plane(void *raw, t_cam *cam);

//sphere_intersection
t_object		insert_sphere(t_sphere sph);
void			replace_node(t_intersection *current, t_intersection *new_inter);
void			add_intersection(t_intersection *head, t_intersection *new_inter);
void			transform(t_ray *ray, t_matrix tr);
void			intersect_sphere(t_sphere sph, t_ray ray, t_intersection *head);
t_intersection	*_hit(t_intersection *head);

//tuples
t_tuple			t_t(t_tuple p1, char op, t_tuple p2);
t_tuple			t_f(t_tuple p, char op, float a);
t_tuple			normalizer4(t_tuple p);
double			_dot4(t_tuple a, t_tuple b);
t_tuple			reflect(t_tuple in, t_tuple normal);
t_tuple			position(t_ray ray, double t);
unsigned int	rgbt_uint(float r, float g, float b, float t);

//matrix
t_tuple			get_tup(double x, double y, double z, double t);
t_tuple			normal_at(t_sphere sphere, t_tuple world_p);
t_tuple			matrix_tuple(t_matrix m, t_tuple tup);
t_matrix    	inv_m(t_matrix m);
t_matrix    	transp_m(t_matrix m);
t_matrix    	multi_m(t_matrix m1, t_matrix m2);

//transform
t_matrix		translate(double x, double y, double z);
t_matrix		scale(double x, double y, double z);
t_matrix		rot_z(double teta);
t_matrix		rot_y(double teta);
t_matrix    	rot_x(double teta);