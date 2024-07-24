#include "minirt.h"

t_dot *lighting(t_material *material, t_light *light, t_dot *sphere_o, t_dot *camerav, t_dot *normalv)
{
    t_dot *ambient;
    t_dot *specular;
    t_dot *diffuse;
    double factor;
    double light_dot_normal;
    t_dot *effective_color;
    double reflect_dot_eye;
    t_dot *lightv;
    t_dot *reflectv;

    effective_color = v_f(material->color, '*' ,light->intensity);
    lightv = normalizer(v_v(light->light_point, '-', sphere_o));
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
        reflectv = reflect(lightv, normalv);
        reflect_dot_eye = (double)_dot(*reflectv, *camerav);
        if (reflect_dot_eye <= 0)
        {
            specular = get_vec(0, 0, 0);
        }
        else
        {
            factor = pow(reflect_dot_eye, material->shininess);
            specular = v_f(get_vec(light->intensity, light->intensity, light->intensity), '*', material->specular * factor);
        }
    }
    return (v_v(v_v(ambient, '+', diffuse),  '+', specular));
}


// t_dot *reflect(t_dot *in, t_dot *normal)
// {
//     t_dot *p1;

//     p1 = v_f(normal, '*', 2 * _dot(*in, *normal));
//     return (v_v(in, '-', p1));
// }

int main()
{
    // t_material  *material = malloc(sizeof(t_material));
    // t_light     *light = malloc(sizeof(t_light));
    // t_dot       *sphere_o = malloc(sizeof(t_dot));
    // t_dot       *camerav = malloc(sizeof(t_dot));
    // t_dot       *normalv = malloc(sizeof(t_dot));

    t_dot       *out;
    t_dot   *v1 = get_vec(1,  -1, 0);
    t_dot   *v2 = get_vec(0, 1, 0);
    out = reflect(v1, v2);
    // material->ambient = 0.1;
    // material->specular = 0.9;
    // material->diffuse = 0.9;
    // material->shininess = 200;
    // material->color = get_vec(1, 1, 1);

    // light->color = get_vec(1, 1, 1);
    // light->light_point = get_vec(0, 0, -10);
    // light->intensity = 1;

    // sphere_o = get_vec(0, 0, 0);

    // camerav = get_vec(0, sqrt((float)1/2), -sqrt((float)1/2));

    // normalv = get_vec(0, 0, -1);
    // out = lighting(material, light, sphere_o, camerav, normalv);

    printf("%f - %f - %f\n", out->x, out->y, out->z);
}