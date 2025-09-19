/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:11:59 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/19 16:12:20 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

#define KEY0 "\x1b[94m"
#define KEY1 "\x1b[96m"
#define TEXT "\x1b[93m"
#define VALUE "\x1b[93m"
#define CLEAR "\x1b[m"
#define ITALIC "\x1b[3m"
#define GREY "\x1b[37m"

static const char *get_data(t_token t)
{
	return ((const char *[]){"error", "word", "var", "asgn", "<", ">", ">>",
		"<<", "<<??", "<<<", "<&", ">&", "<(", ">(", "|", "&&", "||", ";", "&",
		"\\n", "$(", "(", ")", "$((", "))", "[", "]", "[[", "]]", ";;", ";&", ";;&", "if",
		"then", "else", "fi", "while", "do", "done", "for", "in", "case",
		"esac", "select", "time", "function", "coproc", "until", "elif",
		"comment", "EOF"}[t.type]);
}

void	print_token(t_token token)
{
	printf(ITALIC GREY"Token"CLEAR" ");
	printf("<"TEXT"%s"CLEAR"> ", get_data(token));
	printf("{"KEY0" type"CLEAR": ");
	printf(VALUE"%i"CLEAR","KEY0" pos"CLEAR": {"KEY1" line"CLEAR": ",
		token.type);
	printf(VALUE"%i"CLEAR","KEY1" start"CLEAR": ", token.pos.line);
	printf(VALUE"%i"CLEAR","KEY1" end"CLEAR": ", token.pos.start);
	printf(VALUE"%i"CLEAR","KEY1" absStart"CLEAR": ", token.pos.end);
	printf(VALUE"%i"CLEAR","KEY1" absEnd"CLEAR": ", token.pos.abs_start);
	printf(VALUE"%i"CLEAR" }\n", token.pos.abs_end);
}
