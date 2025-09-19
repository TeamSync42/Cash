/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:46:05 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:06:02 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

bool	is_word_char(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == ':' || c == '@' || c == '#'
		|| c == '%' || c == '+' || c == '-'
		|| c == '?' || c == '/' || c == '$'
		|| c == '=' || c == '.' || c == '_'
		|| c == '[' || c == ']');
}

char	lexer_next(t_lexer *lexer)
{
	if (lexer->end)
		return ('\0');
	lexer->current_char = lexer->next_char;
	lexer->character++;
	if (lexer->current_char == '\0')
	{
		lexer->end = true;
		return ('\0');
	}
	if (lexer->current_char == '\n')
	{
		lexer->line++;
		lexer->character = 1;
	}
	lexer->next_char = lexer->input[++lexer->iterator];
	return (lexer->current_char);
}

bool	lexer_match(t_lexer *lexer, char c)
{
	if (lexer->next_char == c)
	{
		lexer_next(lexer);
		return (true);
	}
	return (false);
}

t_token	lexer_emit(t_lexer *lexer, t_token_type type)
{
	t_token	tok;

	tok.type = type;
	tok.fd = lexer->fd;
	tok.pos.start = lexer->start;
	tok.pos.abs_start = lexer->abs_start;
	tok.pos.end = lexer->character;
	tok.pos.abs_end = lexer->iterator;
	tok.pos.line = lexer->line;
	return (tok);
}
