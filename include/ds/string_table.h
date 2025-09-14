/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_table.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 05:51:44 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 13:18:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_TABLE_H
# define STRING_TABLE_H

# include <stdint.h>
# include <stdlib.h>

# define INITIAL_STRING_TABLE_CAPACITY 1024

typedef struct s_string_table
{
	char	**strings;
	size_t	count;
	size_t	capacity;
}	t_string_table;

int32_t	string_table_init(t_string_table *string_table);
void	string_table_cleanup(t_string_table *string_table);
size_t	string_table_add(t_string_table *string_table, const char *str);

#endif // STRING_TABLE_H
