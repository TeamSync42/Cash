/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:18:08 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 11:52:17 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_INTERNAL_H
# define ARGUMENTS_INTERNAL_H

# include "arguments.h"

t_result	arguments_parse(t_arguments *args, int argc, char **argv);
t_result	parse_positional(t_arguments *args, char *arg);
t_result	parse_short(const t_arguments *args, int argc, char **argv,
				int *i);
t_result	parse_long(const t_arguments *args, int argc, char **argv,
				int *i);

#endif // ARGUMENTS_INTERNAL_H
