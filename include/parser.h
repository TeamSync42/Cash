/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:25:58 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/09 18:49:40 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"
#include "libft.h"

typedef struct s_parser
{
	t_lexer	*lexer;
}	t_parser;

t_result	parser_init(t_parser *parser, t_lexer *lexer);
t_result	parser_parse(t_parser *parser, char *line);

#endif
