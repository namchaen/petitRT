#include "vec3.h"
#include <stdlib.h>

t_vec3	vadd_(t_vec3 v1, t_vec3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec3	vsub_(t_vec3 v1, t_vec3 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vec3	vmul_(t_vec3 v1, t_vec3 v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}

t_vec3	vdiv_(t_vec3 v1, t_vec3 v2)
{
	if (!v2.x || !v2.y || !v2.z)
	{
		printf("Error: devider is 0\n");
		exit(0);
	}
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	return (v1);
}