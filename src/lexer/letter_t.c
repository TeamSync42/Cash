/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_t.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:24:56 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:26:37 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_letter_t(t_lexer *lexer)
{
	if (lexer_match(lexer, 'i')
		&& lexer_match(lexer, 'm')
		&& lexer_match(lexer, 'e')
		&& !is_word_char(lexer->next_char))
	{
		return (lexer_emit(lexer, TOK_TIME));
	}
	if (lexer_match(lexer, 'h')
		&& lexer_match(lexer, 'e')
		&& lexer_match(lexer, 'n')
		&& !is_word_char(lexer->next_char))
	{
		return (lexer_emit(lexer, TOK_THEN));
	}
	return (lex_word(lexer));
}
