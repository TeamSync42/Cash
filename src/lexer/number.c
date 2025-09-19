/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:07:37 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:10:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include <limits.h>

t_token	lex_number(t_lexer *lexer)
{
	lexer->fd = lexer->current_char - '0';
	while (lexer->next_char >= '0' && lexer->next_char <= '9')
	{
		if (lexer->fd > INT_MAX / 10
			|| (lexer->fd == INT_MAX / 10 && lexer->next_char > '7'))
		{
			lexer->fd = 1;
			return (lex_word(lexer));
		}
		lexer->fd = (lexer->fd << 3) + (lexer->fd << 1)
			+ (lexer_next(lexer) - '0');
	}
	if (lexer_match(lexer, '>'))
		return (lex_redir_out(lexer));
	if (lexer_match(lexer, '<'))
		return (lex_redir_in(lexer));
	lexer->fd = 1;
	return (lex_word(lexer));
}
