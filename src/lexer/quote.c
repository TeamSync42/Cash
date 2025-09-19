/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:12:48 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:19:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_dquote(t_lexer *lexer)
{
	bool	err;

	err = false;
	while (lexer->next_char != '"')
	{
		if (lexer->next_char == '\n' || lexer->next_char == '\0')
		{
			err = true;
			break ;
		}
		if (lexer->next_char == '\\')
			lexer_next(lexer);
		lexer_next(lexer);
	}
	if (err)
		return (lexer_emit(lexer, TOK_ERROR));
	lexer_next(lexer);
	return (lexer_emit(lexer, TOK_WORD));
}

t_token	lex_squote(t_lexer *lexer)
{
	bool	err;

	err = false;
	while (lexer->next_char != '\'')
	{
		if (lexer->next_char == '\n' || lexer->next_char == '\0')
		{
			err = true;
			break ;
		}
		lexer_next(lexer);
	}
	if (err)
		return (lexer_emit(lexer, TOK_ERROR));
	lexer_next(lexer);
	return (lexer_emit(lexer, TOK_WORD));
}
