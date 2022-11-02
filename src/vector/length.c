#include "vec3.h"
#include <math.h>
#include <stdlib.h>

float	vnorm2(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	vnorm(t_vec3 v)
{
	return (sqrt(vnorm2(v)));
}


t_vec3	vunit(t_vec3 v)
{
	float	len;

	len = vnorm(v);
	if (len == 0)
	{
		printf("Error: devider is 0\n");
		exit(0);
	}
	len = 1 / len;
	v.x *= len;
	v.y *= len;
	v.z *= len;
	return (v);
}
