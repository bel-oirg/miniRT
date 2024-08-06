/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:34:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/05 01:14:48 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_phong init_phong(t_material material, t_light light, t_tuple point, t_tuple normalv)
{
    t_phong p;
    
    p.effective_color = t_t(material.color, '&' ,light.color);
    p.effective_color.w = 1;
    p.lightv = normalizer4(t_t(light.light_point, '-', point));
    p.ambient = t_f(p.effective_color,  '*',  material.ambient);
    p.light_dot_normal = _dot4(p.lightv, normalv);
    return (p);
}

t_tuple lighting(t_material material, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    t_phong p;

    p = init_phong(material, light, point, normalv);
    if (p.light_dot_normal < 0)
    {
        p.diffuse = get_tup(0, 0, 0, 0);
        p.specular = get_tup(0, 0, 0, 0);
    }
    else
    {
        p.diffuse = t_f(p.effective_color,  '*',  (material.diffuse * p.light_dot_normal));
        p.lightv = t_f(p.lightv, '*', -1);
        p.reflectv = reflect(p.lightv, normalv);
        p.reflect_dot_eye = _dot4(p.reflectv, eyev);
        if (p.reflect_dot_eye <= 0)
            p.specular = get_tup(0, 0, 0, 0);
        else
        {
            p.factor = pow(p.reflect_dot_eye, material.shininess);
            p.specular = t_f(light.color, '*', material.specular * p.factor);
        }
    }
    return (t_t(t_t(p.ambient, '+', p.diffuse),  '+', p.specular));
}

t_light *init_light()
{
    t_light *light;

    light = my_malloc(sizeof(t_light), 1);
    light->color = get_tup(1, 1, 1, 0);
    light->light_point = get_tup(10, 10, 10, 1);
    return (light);
}
