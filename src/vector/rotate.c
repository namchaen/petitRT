#include "vec3.h"
#include <stdlib.h>
#include <math.h>

t_vec3	vquat_rotate(float theta, t_vec3 n, t_vec3 v1)
{
	t_vec3	v;

	v = vadd_(vmul(v1, cos(theta)), vmul(vcross(n, v1), sin(theta)));
	return (v);
}

t_quat	vquat(float theta, t_vec3 v)
{
	t_quat	q;

	q.a = cos(theta);
	q.v = vunit(v);
	return (q);
}

//static t_vec3	vquat_mul_ex(float theta, t_vec3 v1, t_vec3 v2)
//{
//t_vec3	v;

//v.x = cos(theta) * v2.x + v1.x * cos(theta) + v1.y * v2.z - v1.z * v2.y;
//v.y = cos(theta) * v2.y - v1.x * v2.z + v1.y * cos(theta) + v1.z * v2.x;
//v.z = cos(theta) * v2.z + v1.x * v2.y - v1.y * v2.x + v1.z * cos(theta);
//return (v);
//}


t_quat	vquat_mul_(t_quat q1, t_quat q2)
{
	t_quat	q;

	q.a = q1.a * q2.a - (q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z);
	q.v.x = q1.a * q2.v.x + q1.v.x * q2.a + q1.v.y * q2.v.z - q1.v.z * q2.v.y;
	q.v.y = q1.a * q2.v.y - q1.v.x * q2.v.z + q1.v.y * q2.a + q1.v.z * q2.v.x;
	q.v.z = q1.a * q2.v.z + q1.v.x * q2.v.y - q1.v.y * q2.v.x + q1.v.z * q2.a;
	q.v = vunit(q.v);
	return (q);
}

t_vec3	vquat_mul(float theta, t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.x = cos(theta) * v2.x + v1.x + v1.y * v2.z - v1.z * v2.y;
	v.y = cos(theta) * v2.y - v1.x * v2.z + v1.y + v1.z * v2.x;
	v.z = cos(theta) * v2.z + v1.x * v2.y - v1.y * v2.x + v1.z;
	return (v);
}

t_vec3	vmul_qut(float theta, t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.x = v2.x + v1.x * cos(theta) + v1.y * v2.z - v1.z * v2.y;
	v.y = v2.y - v1.x * v2.z + v1.y * cos(theta) + v1.z * v2.x;
	v.z = v2.z + v1.x * v2.y - v1.y * v2.x + v1.z * cos(theta);
	return (v);
}

t_vec3	vroll(t_vec3 v1, float alpha)
{
	alpha = alpha * M_PI / 180;
	v1.y = cos(alpha) * v1.y - sin(alpha) * v1.z;
	v1.z = sin(alpha) * v1.y + cos(alpha) * v1.z;
	return (vunit(v1));
}

t_vec3	vpitch(t_vec3 v1, float alpha)
{
	alpha = alpha * M_PI / 180;
	v1.x = cos(alpha) * v1.x + sin(alpha) * v1.z;
	v1.z = -sin(alpha) * v1.x + cos(alpha) * v1.z;
	return (vunit(v1));
}

t_vec3	vyaw(t_vec3 v1, float alpha)
{
	alpha = alpha * M_PI / 180;
	v1.x = cos(alpha) * v1.x - sin(alpha) * v1.y;
	v1.y = sin(alpha) * v1.x + cos(alpha) * v1.y;
	return (vunit(v1));
}

t_vec3	vrotate(t_vec3 v1, float a, float b, float r)
{
	a = a * M_PI / 180;
	b = b * M_PI / 180;
	r = r * M_PI / 180;
	v1.x = (cos(r) + cos(b)) * v1.x - sin(r) * v1.y + sin(b) * v1.z;
	v1.y = (sin(r) + cos(a)) * v1.x + cos(r) * v1.y - sin(a) * v1.z;
	v1.z = -sin(b) * v1.x + sin(a) * v1.y + (cos(a) + cos(b)) * v1.z;
	return (vunit(v1));
}