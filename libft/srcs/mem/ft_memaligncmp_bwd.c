/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memaligncmp_bwd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svet <svet@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 11:57:14 by svet              #+#    #+#             */
/*   Updated: 2020/05/08 18:55:43 by svet             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

size_t	ft_memaligncmp_bwd(const void *const *const ds,
				const void *const *const sr, size_t nbytes, unsigned OP_T align)
{
	unsigned OP_T		t;
	const unsigned OP_T	dst = (const unsigned OP_T)*(OP_T**)ds;
	const unsigned OP_T	src = (const unsigned OP_T)*(const OP_T **)sr;

	t = src;
	if ((t | dst) & (align - 1))
	{
		if ((t ^ dst) & (align - 1) || nbytes < (align))
			t = nbytes;
		else
			t &= align - 1;
		return (t);
	}
	return (0);
}
