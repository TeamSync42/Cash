/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:00:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/09 18:49:39 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CASH_H
# define CASH_H

# include "arguments.h"
# include "parser.h"
# include "lexer.h"

typedef struct s_cash
{
	t_arguments	args;
	t_lexer		lexer;
	t_parser	parser;
}	t_cash;

#endif
