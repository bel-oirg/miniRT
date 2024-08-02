/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:34:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/02 09:08:27 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_phong init_phong(t_material material, t_light light, t_tuple point, t_tuple normalv)
{
    t_phong p;
    
    p.effective_color = t_f(material.color, '*' ,light.intensity);
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
        p.diffuse = get_tup(0, 0, 0, 0); //VERIFIED
        p.specular = get_tup(0, 0, 0, 0); //VERIFIED
    }
    else
    {
        p.diffuse = t_f(p.effective_color,  '*',  (material.diffuse * p.light_dot_normal));
        p.lightv = t_f(p.lightv, '*', -1);
        p.reflectv = reflect(p.lightv, normalv);
        p.reflect_dot_eye = _dot4(p.reflectv, eyev);
        if (p.reflect_dot_eye <= 0)
            p.specular = get_tup(0, 0, 0, 0);  //VERIFIED
        else
        {
            p.factor = pow(p.reflect_dot_eye, material.shininess);
            p.specular = t_f(get_tup(light.intensity, light.intensity, light.intensity, light.intensity), '*', material.specular * p.factor);
        }
    }
    return (t_t(t_t(p.ambient, '+', p.diffuse),  '+', p.specular));
}

t_light *init_light()
{
    t_light *light;

    light = my_malloc(sizeof(t_light), 1);
    light->color = get_tup(1, 1, 1, 1);
    light->light_point = get_tup(-10, 10, -10, 1); //VERIFIED
    light->intensity = 0.9;
    return (light);
}

/*
function is_shadowed(world, point) 
    v ← world.light.position - point 
    distance ← magnitude(v)
    direction ← normalize(v)
    r ← ray(point, direction)
    intersections ← intersect_world(world, r)
    h ← hit(intersections)
    
    if h is present and h.t < distance
        return true
    else
        return false
    end if
end function
*/

// int is_shadowed(t_world *w, t_cam *cam, t_dot *point)
// {
//     t_dot   *direction;
//     t_inter *inter;
//     t_dot   *v;
//     t_dot   *r;
//     int     shad;
//     double  distance;

//     shad = 0;
//     v = v_v(w->light->light_point, '-', point);
//     distance = get_length(*v);
//     direction = normalizer(v);
//     r = v_v(point, '-', direction);
//     inter = sort_intersections(w, cam, point->x, point->y);
//     if (inter->h0 < distance)
//         shad = 1;
//     return (shad);
// }
