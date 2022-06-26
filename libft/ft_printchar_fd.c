/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 11:30:39 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/05/30 19:14:47 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printchar_fd(char c, int fd, int *nb_char)
{
	write(fd, &c, 1);
	*nb_char = *nb_char + 1;
}
