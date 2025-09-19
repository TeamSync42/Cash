/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:43:42 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 15:51:56 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

static t_lex_fn	get_fn(int idx)
{
	return ((t_lex_fn[128]){lex_eof, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_error, NULL, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, NULL, lex_error, lex_dquote, lex_comment,
		lex_dollar, lex_error, lex_amp, lex_squote, lex_group, lex_group,
		lex_word, lex_word, lex_error, lex_word, lex_word, lex_word, lex_number,
		lex_number, lex_number, lex_number, lex_number, lex_number, lex_number,
		lex_number, lex_number, lex_number, lex_word, lex_delim, lex_redir_in,
		lex_word, lex_redir_out, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_error, lex_error, lex_error, lex_error, lex_error, lex_error,
		lex_error, lex_error, lex_error, lex_word, lex_word, lex_word, lex_word,
		lex_letter_e, lex_word, lex_word, lex_word, lex_letter_i, lex_word,
		lex_word, lex_word, lex_word, lex_word, lex_word, lex_word, lex_word,
		lex_word, lex_word, lex_letter_t, lex_word, lex_word, lex_letter_w,
		lex_word, lex_word, lex_word, lex_error, lex_pipe, lex_error,
		lex_word, lex_error}[idx]);
}

t_token	lexer_advance(t_lexer *lexer)
{
	char		c;
	t_lex_fn	fn;

	if (lexer->end)
		return (lexer_emit(lexer, TOK_EOF));
	while (true)
	{
		c = lexer_next(lexer);
		lexer->start = lexer->character - 1;
		lexer->abs_start = lexer->iterator - 1;
		if ((unsigned char)c > 0x7fu)
			return (lexer_emit(lexer, TOK_ERROR));
		fn = get_fn(c);
		if (fn)
			return (fn(lexer));
	}
}
