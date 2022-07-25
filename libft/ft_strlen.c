/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:34:24 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/25 12:03:17 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Computes the length of the string str, returns the number of characters
that precede the terminating NUL character*/
size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}
