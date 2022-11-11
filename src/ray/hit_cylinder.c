/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:19:35 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/11 18:28:02 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

static t_bool	set_eqaution(t_eqtn *eqtn, t_cylinder *cy,
					t_ray *ray, t_hit_record *rec);
static t_bool	is_hit_cylinder(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_eqtn *eqtn);
static t_bool	check_base_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_eqtn *eqtn);
static t_bool	check_top_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_eqtn *eqtn);

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_eqtn		eqtn;

	cy = cy_obj->element;
	if (set_eqaution(&eqtn, cy, ray, rec) == FALSE)
		return (FALSE);
	if (is_hit_cylinder(cy, ray, rec, &eqtn) == FALSE)
		return (FALSE);
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}

static t_bool	set_eqaution(t_eqtn *eqtn, t_cylinder *cy,
					t_ray *ray, t_hit_record *rec)
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
	if (fabs(eqtn->a) <= EPSILON || eqtn->discriminant <= 0)
		return (FALSE);
	eqtn->sqrtd = sqrt(eqtn->discriminant);
	eqtn->root = (-eqtn->half_b - eqtn->sqrtd) / eqtn->a;
	if (eqtn->root < rec->tmin || rec->tmax < eqtn->root)
	{
		eqtn->root = (-eqtn->half_b + eqtn->sqrtd) / eqtn->a;
		if (eqtn->root < rec->tmin || rec->tmax < eqtn->root)
			return (FALSE);
	}
	eqtn->root_modified = FALSE;
	return (TRUE);
}

static t_bool	is_hit_cylinder(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_eqtn *eqtn)
{
	t_point3	p;
	t_vec3		pc;
	float		height;

	p = ray_at(ray, eqtn->root);
	pc = vsub_(p, cy->center_base);
	height = vdot(pc, cy->normal);
	if (height < 0)
		return (check_base_cap(cy, ray, rec, eqtn));
	if (height > cy->height)
		return (check_top_cap(cy, ray, rec, eqtn));
	rec->t = eqtn->root;
	rec->p = p;
	rec->normal = vunit(vsub_(rec->p,
				vadd_(cy->center_base, vmul(cy->normal, height))));
	return (TRUE);
}

static t_bool	check_base_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_eqtn *eqtn)
{
	float	dn;
	float	t;
	t_vec3	pc;

	dn = vdot(ray->dir, cy->normal);
	if (fabs(dn) <= EPSILON)
		return (FALSE);
	t = vdot(vsub_(cy->center_base, ray->orig), cy->normal) / dn;
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	pc = vsub_(ray_at(ray, t), cy->center_base);
	if (fabs(vdot(pc, cy->normal)) > EPSILON || vnorm(pc) > cy->radius)
		return (FALSE);
	eqtn->root = t;
	eqtn->root_modified = TRUE;
	rec->t = eqtn->root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vmul(cy->normal, -1);
	return (TRUE);
}

static t_bool	check_top_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_eqtn *eqtn)
{
	float	dn;
	float	t;
	t_vec3	pc;

	dn = vdot(ray->dir, cy->normal);
	if (fabs(dn) <= EPSILON)
		return (FALSE);
	t = vdot(vsub_(cy->center_top, ray->orig), cy->normal) / dn;
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	pc = vsub_(ray_at(ray, t), cy->center_top);
	if (fabs(vdot(pc, cy->normal)) > EPSILON || vnorm(pc) > cy->radius)
		return (FALSE);
	eqtn->root = t;
	eqtn->root_modified = TRUE;
	rec->t = eqtn->root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = cy->normal;
	return (TRUE);
}
