/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:34:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/28 02:02:05 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_phong *init_phong(t_material *material, t_light *light, t_dot *point, t_dot *normalv)
{
    t_phong *p;

    p = my_malloc(sizeof(t_phong), 1);
    p->effective_color = v_f(material->color, '*' ,light->intensity);
    p->lightv = normalizer(v_v(light->light_point, '-', point));
    p->ambient = v_f(p->effective_color,  '*',  material->ambient);
    p->light_dot_normal = _dot(*p->lightv, *normalv);
    return (p);
}

t_dot *lighting(t_material *material, t_light *light, t_dot *point, t_dot *camerav)
{
    t_phong *p;
    t_dot   *normalv;

    normalv = normalizer(point);
    p = init_phong(material, light, point, normalv);
    if (p->light_dot_normal < 0)
    {
        p->diffuse = get_vec(0, 0, 0);
        p->specular = get_vec(0, 0, 0);
    }
    else
    {
        p->diffuse = v_f(p->effective_color,  '*',  (material->diffuse * p->light_dot_normal));
        p->lightv = v_f(p->lightv, '*', -1);
        p->reflectv = reflect(p->lightv, normalv);
        p->reflect_dot_eye = _dot(*p->reflectv, *camerav);
        if (p->reflect_dot_eye <= 0)
            p->specular = get_vec(0, 0, 0);
        else
        {
            p->factor = pow(p->reflect_dot_eye, material->shininess);
            p->specular = v_f(get_vec(light->intensity, light->intensity, light->intensity), '*', material->specular * p->factor);
        }
    }
    return (v_v(v_v(p->ambient, '+', p->diffuse),  '+', p->specular));
}

t_light *init_light()
{
    t_light *light;
    
    light = my_malloc(sizeof(t_light), 1);
    light->color = get_vec(1, 1, 1);
    light->light_point = get_vec(-10, 10, -10);
    light->intensity = 0.9;
    return (light);
}
