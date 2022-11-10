#ifndef VEC3_H
# define VEC3_H

# include <stdio.h> //printf

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef t_vec3 t_point3;
typedef t_vec3 t_color3;

t_vec3	vec3(float x, float y, float z);
t_vec3	point3(float x, float y, float z);
t_vec3	color3(float x, float y, float z);
t_vec3	vmin(t_vec3 v1, t_vec3 v2);
void	vprnt(char *vname, t_vec3 *v);

float	vdot(t_vec3 v1, t_vec3 v2);
t_vec3	vcross(t_vec3 v1, t_vec3 v2);

t_vec3	vadd_(t_vec3 v1, t_vec3 v2);
t_vec3	vsub_(t_vec3 v1, t_vec3 v2);
t_vec3	vmul_(t_vec3 v1, t_vec3 v2);
t_vec3	vdiv_(t_vec3 v1, t_vec3 v2);

t_vec3	vadd(t_vec3 v1, float t);
t_vec3	vsub(t_vec3 v1, float t);
t_vec3	vmul(t_vec3 v1, float t);
t_vec3	vdiv(t_vec3 v1, float t);

/* 벡터의 길이 */
float	vnorm2(t_vec3 v);
float	vnorm(t_vec3 v);
t_vec3	vunit(t_vec3 v);

/* Quaternion rotation*/
t_vec3	vqut_rotate(float theta, t_vec3 n, t_vec3 v1);
t_vec3	vqut_mul(float theta, t_vec3 v1, t_vec3 v2);
t_vec3	vmul_qut(float theta, t_vec3 v1, t_vec3 v2);
/* Euler rotation */
t_vec3	vroll(t_vec3 v1, float alpha);
t_vec3	vpitch(t_vec3 v1, float alpha);
t_vec3	vyaw(t_vec3 v1, float alpha);
t_vec3	vrotate(t_vec3 v1, float a, float b, float r);

/* 벡터곱 연산 결과
	행벡터 곱하기 열벡터 -> 스칼라
	열벡터 곱하기 행백터 -> 행렬
	행렬 곱하기 열벡터 -> 벡터
	똑같은 벡터의 내적 -> 벡터의 놈 -> 제곱합 -> 스칼라
*/
/* inner product 방향이 일치하는 만큼만 곱한 것 (결과값은 스칼라)
두 벡터의 차원(길이)은 같아야 함
앞은 행 벡터, 뒤는 열 벡터가 와야 함 x^{T}y
*/

#endif
