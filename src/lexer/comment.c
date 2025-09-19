/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:21:12 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:21:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_comment(t_lexer *lexer)
{
	while (lexer->current_char != '\n' && lexer->current_char != '\0')
		lexer_next(lexer);
	return (lexer_emit(lexer, TOK_COMMENT));
}
