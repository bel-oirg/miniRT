/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:34:22 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/08/02 15:21:58 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_phong init_phong(t_material material, t_light light, t_tuple point, t_tuple normalv)
{
    t_phong p;
    
    p.effective_color = t_t(material.color, '&' ,light.color);
    p.effective_color.t[3] = 1;
    p.lightv = normalizer4(t_t(light.light_point, '-', point));
    p.ambient = t_f(p.effective_color,  '*',  material.ambient);
    p.light_dot_normal = _dot4(p.lightv, normalv);
    return (p);
}

t_tuple lighting(t_material material, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    t_phong p;

    p = init_phong(material, light, point, normalv);
    // printf("light_dot_normal %f\n", p.light_dot_normal);
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
        // printf("reflect_dot_eye %f\n", p.reflect_dot_eye);

        if (p.reflect_dot_eye <= 0)
            p.specular = get_tup(0, 0, 0, 0);  //VERIFIED
        else
        {
            p.factor = pow(p.reflect_dot_eye, material.shininess);
            p.specular = t_f(light.color, '*', material.specular * p.factor);
        }
    }

	// printf("amb -> %f %f %f %f\n", p.ambient.t[0], p.ambient.t[1], p.ambient.t[2], p.ambient.t[3]);
	// printf("diffuse -> %f %f %f %f\n", p.diffuse.t[0], p.diffuse.t[1], p.diffuse.t[2], p.diffuse.t[3]);
	// printf("spec -> %f %f %f %f\n", p.specular.t[0], p.specular.t[1], p.specular.t[2], p.specular.t[3]);

    return (t_t(t_t(p.ambient, '+', p.diffuse),  '+', p.specular));
}

t_light *init_light()
{
    t_light *light;

    light = my_malloc(sizeof(t_light), 1);
    light->color = get_tup(1, 1, 1, 0);  //TODO I CHANGED 1 - 0
    light->light_point = get_tup(10, 10, 10, 1); //VERIFIED
    // light->intensity = 1.2;
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
