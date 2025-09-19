/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:49:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:05:00 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "lexer.h"

bool		is_word_char(char c);

char		lexer_next(t_lexer *lexer);
bool		lexer_match(t_lexer *lexer, char c);
t_token		lexer_emit(t_lexer *lexer, t_token_type type);
t_token		lexer_advance(t_lexer *lexer);

typedef t_token	(*t_lex_fn)(t_lexer *lexer);

// All the lexing functions
t_token		lex_error(t_lexer *lexer);
t_token		lex_eof(t_lexer *lexer);
t_token		lex_comment(t_lexer *lexer);
t_token		lex_word(t_lexer *lexer);
t_token		lex_number(t_lexer *lexer);
t_token		lex_delim(t_lexer *lexer);
t_token		lex_redir_out(t_lexer *lexer);
t_token		lex_redir_in(t_lexer *lexer);
t_token		lex_squote(t_lexer *lexer);
t_token		lex_dquote(t_lexer *lexer);
t_token		lex_group(t_lexer *lexer);
t_token		lex_amp(t_lexer *lexer);
t_token		lex_pipe(t_lexer *lexer);
t_token		lex_dollar(t_lexer *lexer);

t_token		lex_letter_e(t_lexer *lexer);
t_token		lex_letter_i(t_lexer *lexer);
t_token		lex_letter_t(t_lexer *lexer);
t_token		lex_letter_w(t_lexer *lexer);

#endif // LEXER_INTERNAL_H
