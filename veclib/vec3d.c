# include "vec3d.h"

t_vec3 vec3(double x, double y, double z)
{
	t_vec3 result;

	result.x = x;
	result.y = y;
	result.z = z;
	return	result;
}

t_vec3 add(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return	result;
}

t_vec3 sub(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return	result;
}

t_vec3 mp(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return result;
}

t_vec3 mpv(t_vec3 a, double c)
{
	t_vec3 result;

	result.x = a.x * c;
	result.y = a.y * c;
	result.z = a.z * c;
	return result;
}

t_vec3 dvd(t_vec3 a, double c)
{
	t_vec3 result;

	if (c == 0)
	{
		c = 0.001;
	}
	result.x = a.x / c;
	result.y = a.y / c;
	result.z = a.z / c;
	return result;
}

t_vec3 cross(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

   result.x = a.y * b.z - a.z * b.y;
   result.y = -(a.x * b.z - a.z * b.x);
   result.z = a.x * b.y - a.y * b.x;
   return result;
}

t_vec3 neg(t_vec3 a)
{
	a.x = -1 * a.x;
	a.y = -1 * a.y;
	a.z = -1 * a.z;
    return a;
}

double distance(t_vec3 u, t_vec3 v)
{
	return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2) + pow(u.z - v.z, 2));
}

double dot(t_vec3 a, t_vec3 b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}


double length_squared(t_vec3 a)
{
	return (a.x*a.x + a.y*a.y + a.z*a.z);
}

double length(t_vec3 v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

t_vec3 unit_vector(t_vec3 v)
{
	return dvd(v, length(v));
}

