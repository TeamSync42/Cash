/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_w.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:26:47 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:27:51 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_letter_w(t_lexer *lexer)
{
	if (lexer_match(lexer, 'h')
		&& lexer_match(lexer, 'i')
		&& lexer_match(lexer, 'l')
		&& lexer_match(lexer, 'e')
		&& !is_word_char(lexer->next_char))
	{
		return (lexer_emit(lexer, TOK_WHILE));
	}
	return (lex_word(lexer));
}
