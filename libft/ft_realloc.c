/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:14:54 by jholterh          #+#    #+#             */
/*   Updated: 2025/01/27 17:33:53 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t new_size, size_t old_size)
{
	void	*ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(p);
		return (NULL);
	}
	if (p == NULL)
		return (malloc(new_size));
	ptr = malloc(new_size);
	if (!ptr)
		return (NULL);
	if (new_size < old_size)
		copy_size = new_size;
	else
		copy_size = old_size;
	ft_memcpy(ptr, p, copy_size);
	free(p);
	return (ptr);
}
