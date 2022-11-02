#include "vec3.h"
#include <stdlib.h>

t_vec3	vadd(t_vec3 v1, float t)
{
	v1.x += t;
	v1.y += t;
	v1.z += t;
	return (v1);
}

t_vec3	vsub(t_vec3 v1, float t)
{
	v1.x -= t;
	v1.y -= t;
	v1.z -= t;
	return (v1);
}

t_vec3	vmul(t_vec3 v1, float t)
{
	v1.x *= t;
	v1.y *= t;
	v1.z *= t;
	return (v1);
}

t_vec3	vdiv(t_vec3 v1, float t)
{
	if (t == 0)
	{
		printf("Error: devider is 0\n");
		exit(0);
	}
	v1.x /= t;
	v1.y /= t;
	v1.z /= t;
	return (v1);
}
