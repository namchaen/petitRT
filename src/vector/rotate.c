/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:09:02 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 17:09:47 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <stdlib.h>
#include <math.h>

t_vec3	vrotate(float theta, t_vec3 n, t_vec3 v1)
{
	t_vec3	v;

	v = vmul(vmul_(vmul_(n, v1), n), 1 - cos(theta));
	v = vadd_(vmul(v1, cos(theta)), v);
	v = vadd_(vmul(vcross(n, v1), sin(theta)), v);
	return (v);
}
