/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:15 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/24 13:36:47 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_struct(t_data *data)
{
	t_lexer	*temp;

	temp = data->first;
	while (temp->next)
	{
		printf("----------------------\n");
		printf("Pos : %i\n", temp->pos);
		printf("string : %s\n", temp->token_str);
		printf("token : %i\n", temp->token);
		printf("adr : %p\n", temp);
		printf("prev adr : %p\n", temp->prev);
		printf("next adr : %p\n", temp->next);
		printf("----------------------\n");
		temp = temp->next;
	}
	printf("----------------------\n");
	printf("Pos : %i\n", temp->pos);
	printf("string : %s\n", temp->token_str);
	printf("token : %i\n", temp->token);
	printf("adr : %p\n", temp);
	printf("prev adr : %p\n", temp->prev);
	printf("next adr : %p\n", temp->next);
	printf("----------------------\n");
}

int	new_node(char *str, t_token token, t_data *data)
{
	t_lexer		*new;
	t_lexer		*temp;

	new = malloc(sizeof(t_lexer));
	if (!new)
	{
		free(str);	
		free_all(data, ERR_MAL, 1);
	}
	new->token_str = str;
	new->token = token;
	new->pos = ++data->pos;
	new->next = NULL;
	if (data->first == NULL)
	{
		new->prev = NULL;
		data->first = new;
		return (0);
	}
	temp = data->first;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (0);
}

int	check_double_token(t_data *data)
{
	t_lexer *current;
	t_lexer *temp;

	current = data->first;
	while (current->next)
	{
		temp = current->next;
		if (current->token && temp->token)
			return (1);
		current = temp;
	}
	return (0);
}

int	tokenize(char *str, int i, t_data *data)
{
	if (str[i] == '|')
		return (new_node(ft_substr(str, i, 1, data), 1, data), 1);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (new_node(ft_substr(str, i, 2, data), 5, data), 2);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (new_node(ft_substr(str, i, 2, data), 3, data), 2);
	else if (str[i] == '<')
		return (new_node(ft_substr(str, i, 1, data), 4, data), 1);
	else if (str[i] == '>')
		return (new_node(ft_substr(str, i, 1, data), 2, data), 1);
	else
		return (0);
}

int	save_cmds(char *str, t_data *data)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] && !is_white_space(str[i]) && str[i] != '>' && str[i] != '<'
		&& str[i] != '|')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] != c)
				return (-1);
		}
		i++;
	}
	if (i != 0)
		new_node(ft_substr(str, 0, i, data), 0, data);
	return (i);
}

int	lexer(char *line, t_data *data)
{
	int	i;
	int quotes;

	i = 0;
	while (line[i])
	{
		while (is_white_space(line[i]))
			i++;
		i += tokenize(line, i, data);
		quotes = save_cmds(&line[i], data);
		if (quotes < 0)
			return (1);
		i += quotes;
	}
	if (check_double_token(data))
		return (1);
	print_struct(data);
	return (0);
}
