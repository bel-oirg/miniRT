/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:34:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/07/24 08:53:50 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_dot *lighting(t_material *material, t_light *light, t_dot *point, t_dot *camerav, t_dot *normalv)
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

    effective_color = v_f(material->color, '*' ,light->intensity);
    lightv = normalizer(v_v(light->light_point, '-', point));
    ambient = v_f(effective_color,  '*',  material->ambient);
    light_dot_normal = _dot(*lightv, *normalv);
    if (light_dot_normal < 0)
    {
        
        diffuse = get_vec(0, 0, 0);
        specular = get_vec(0, 0, 0);
    }
    else
    {
        diffuse = v_f(effective_color,  '*',  (material->diffuse * light_dot_normal));
        lightv = v_f(lightv, '*', -1);
        reflectv = reflect(lightv, normalv);
        reflect_dot_eye = _dot(*reflectv, *camerav);
        if (reflect_dot_eye <= 0)
            specular = get_vec(0, 0, 0);
        else
        {
            factor = pow(reflect_dot_eye, material->shininess);
            specular = v_f(get_vec(light->intensity, light->intensity, light->intensity), '*', material->specular * factor);
        }
    }
    return (v_v(v_v(ambient, '+', diffuse),  '+', specular));
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
