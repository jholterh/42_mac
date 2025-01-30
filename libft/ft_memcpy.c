/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:29:21 by jholterh          #+#    #+#             */
/*   Updated: 2024/11/19 14:30:58 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// copies maximum n bytes from src to dest

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (dst);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (num > 0)
	{
		*(d++) = *(s++);
		num--;
	}
	return (dst);
}
