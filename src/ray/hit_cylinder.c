/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:19:35 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/14 12:28:22 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

static t_bool		set_equation(t_eqtn *eqtn, t_cylinder *cy, t_ray *ray);
static t_bool		is_hit_cylinder(t_object *cy_obj, t_ray *ray,
						t_hit_record *rec, float root);
static float		check_cap(t_cylinder *cy, t_ray *ray,
						t_hit_record *rec, t_point3 center);
static t_hit_record	set_record(t_object *cy_obj, t_ray *ray,
						float root, float height);

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_eqtn		eqtn;

	cy = cy_obj->element;
	if (set_equation(&eqtn, cy, ray) == FALSE)
		return (FALSE);
	if (is_hit_cylinder(cy_obj, ray, rec, eqtn.root) == FALSE
		&& is_hit_cylinder(cy_obj, ray, rec, eqtn.root1) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	set_equation(t_eqtn *eqtn, t_cylinder *cy, t_ray *ray)
{
	t_vec3	oc;
	t_vec3	v;
	float	v_dot_n;
	float	w_dot_h;

	v = ray->dir;
	oc = vsub_(ray->orig, cy->center_base);
	v_dot_n = vdot(v, cy->normal);
	w_dot_h = vdot(oc, cy->normal);
	eqtn->a = vnorm2(v) - v_dot_n * v_dot_n;
	eqtn->half_b = vdot(v, oc) - v_dot_n * w_dot_h;
	eqtn->c = vnorm2(oc) - w_dot_h * w_dot_h - cy->radius2;
	eqtn->discriminant = eqtn->half_b * eqtn->half_b - eqtn->a * eqtn->c;
	if (eqtn->a == 0 || eqtn->discriminant <= 0)
		return (FALSE);
	eqtn->sqrtd = sqrt(eqtn->discriminant);
	eqtn->root = (-eqtn->half_b - eqtn->sqrtd) / eqtn->a;
	eqtn->root1 = (-eqtn->half_b + eqtn->sqrtd) / eqtn->a;
	return (TRUE);
}

static t_bool	is_hit_cylinder(t_object *cy_obj, t_ray *ray,
					t_hit_record *rec, float root)
{
	t_point3	p;
	t_vec3		pc;
	float		height;
	t_cylinder	*cy;

	cy = cy_obj->element;
	p = ray_at(ray, root);
	pc = vsub_(p, cy->center_base);
	height = vdot(pc, cy->normal);
	if (height < 0)
		root = check_cap(cy, ray, rec, cy->center_base);
	else if (height > cy->height)
		root = check_cap(cy, ray, rec, cy->center_top);
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	*rec = set_record(cy_obj, ray, root, height);
	return (TRUE);
}

static float	check_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_point3 center)
{
	float	dn;
	float	t;
	t_vec3	pc;

	dn = vdot(ray->dir, cy->normal);
	if (fabs(dn) <= EPSILON)
		return (-1);
	t = vdot(vsub_(center, ray->orig), cy->normal) / dn;
	if (t < rec->tmin || rec->tmax < t)
		return (-1);
	pc = vsub_(ray_at(ray, t), center);
	if (fabs(vdot(pc, cy->normal)) > EPSILON || vnorm(pc) > cy->radius)
		return (-1);
	return (t);
}

static t_hit_record	set_record(t_object *cy_obj, t_ray *ray,
					float root, float height)
{
	t_hit_record	rec;
	t_cylinder		*cy;

	cy = cy_obj->element;
	rec.t = root;
	rec.p = ray_at(ray, rec.t);
	if (height < 0)
		rec.normal = vmul(cy->normal, -1);
	else if (height > cy->height)
		rec.normal = cy->normal;
	else
		rec.normal = vunit(vsub_(rec.p,
					vadd_(cy->center_base, vmul(cy->normal, height))));
	rec.albedo = cy_obj->albedo;
	record_set_face_normal(ray, &rec);
	return (rec);
}
