#include "minirt.h"


t_obj *objs()
{
    t_obj *rtn;
    t_sph *ob;

    rtn = malloc(sizeof(t_obj));
    rtn->sphsize = 0;
    rtn->sph = NULL;
    return rtn;
}


void new_sph(t_obj *self,  t_vec3 pos, double r, t_vec3 color)
{
    t_sph *temp;
    t_sph aa;
    int i;

    temp = self->sph;
    aa.origin = pos;
    aa.radius = r;
    aa.color = color;
    self->sph = malloc(sizeof(t_sph) * (self->sphsize + 1));
    i = 0;
    while (i < self->sphsize)
    {
        self->sph[i] = temp[i];
        i++;
    }
    self->sph[i] = aa;
    self->sphsize = self->sphsize + 1;
    free(temp);
}

