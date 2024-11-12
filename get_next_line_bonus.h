/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:45:25 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/12 22:06:21 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		stash_len(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *s, int c);
void	*ft_free_stuff(void *p1, void *p2, void *p3);

char	*get_next_line(int fd);

#endif
