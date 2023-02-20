/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:59:14 by mqaos             #+#    #+#             */
/*   Updated: 2023/02/20 14:35:38 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void	sort(t_list **a, t_list **b, int size3, int lenmax)
{
	while (b && (*b)->index != size3 - 1)
	{
		if (lenmax < (size3 / 2))
			rb(b, 1);
		else
			rrb(b, 1);
	}
	pa(a, b, 1);
}


int	countmove(t_list *r, int size3)
{
	int		lenmax;
	t_list	*reset;

	lenmax = 0;
	reset = r;
	while (r && r->index != size3 - 1)
	{
		lenmax++;
		r = r->next;
	}
	r = reset;
	return (lenmax);
}

void	pushtostackb(t_list **a, t_list **b, int x, int size2)
{
	int	i;
	int	max;

	i = 0;
	while (x--)
	{
		max = i;
		i += size2;
		while ((max != i))
		{
			if ((*a)->index <= i && max++)
			{
				if ((*a)->index > (i - (size2 / 2)))
				{
					pb(a, b, 1);
					rb(b, 1);
				}
				else
					pb(a, b, 1);
			}
			else
				ra(a, 1);
		}
	}
}

void	pushtoa(t_list	**a, t_list **b, int size3)
{
	int		lenmax;
	int		slenmax;
	t_list	*r;

	while ((*b) && size3)
	{
		r = (*b);
		lenmax = countmove(r, size3);
		slenmax = countmove(r, size3 - 1);
		if (abs(slenmax - (size3 / 2)) > abs(lenmax - (size3 / 2))
			&& (*b)->next)
		{
			sort(a, b, size3 - 1, slenmax);
			sort(a, b, size3, lenmax);
			sa(a, 1);
			size3--;
		}
		else
			sort(a, b, size3, lenmax);
		size3--;
	}
}

void	myalgo(t_list **a, int size)
{
	t_list	*b;
	int		size2;
	int		size3;
	int		x;

	size3 = size;
	b = NULL;
	x = 0;
	if (size >= 500)
	{
		size2 = size / 8; 
		x = 8;
	}
	else
	{
		size2 = size / 4;
		x = 4;
	}
	pushtostackb(a, &b, x, size2);
	while (*a && a)
		pb(a, &b, 1);
	pushtoa(a, &b, size3);
}

void	forcfree(t_list	*clone)
{
	t_list	*help;

	while (clone)
	{
		help = clone;
		clone = clone->next;
		free(help);
	}
}

void	checkarg(char **arg)
{
	int	i;
	int	j;
	int	x;

	i = 1;
	x = 0;
	while (arg[i])
	{
		j = -1;
		while (arg[i][++j])
		{
			if (arg[i][j] >= '0' && arg[i][j] <= '9')
				x = 1;
			if ((arg[i][j] >= '0' && arg[i][j] <= '9') &&
			(arg[i][j + 1] == '-' || arg[i][j + 1] == '+') &&
			(arg[i][j + 2] >= '0' && arg[i][j + 2] <= '9'))
				errr();
		}
		if (x == 0)
			errr();
		i++;
	}
}

int	checkrepeat(t_list **ls)
{
	t_list	*ls2;
	t_list	*rest;

	rest = (*ls);
	while ((*ls)->next)
	{
		ls2 = (*ls)->next;
		while (ls2)
		{
			if ((*ls)->content == ls2->content)
			{
				forcfree(*ls);
				write(2, "Error", 5);
				exit(0);
			}
			ls2 = ls2->next;
		}
		(*ls) = (*ls)->next;
	}
	(*ls) = rest;
	return (0);
}

char	**splitargv(char	*argv[])
{
	char	*spl;
	int		i;
	char	**tmp;

	i = 1;
	spl = NULL;
	while (argv[i])
	{
		spl = ft_join(spl, argv[i]);
		spl = ft_join(spl, " ");
		i++;
	}
	tmp = ft_split(spl, ' ');
	free(spl);
	return (tmp);
}

int	main(int argc, char *argv[])
{
	int		i;
	char	**spl;
	t_list	*a;
	t_list	*clone;

	if (argc < 2)
		return (0);
	i = -1;
	a = NULL;
	checkarg(argv);
	spl = splitargv(argv);
	i = feedlst(spl, &a, i);
	checkrepeat(&a);
	clone = clonelst(spl);
	indexin(&a, &clone);
	quick_sort(&a, i);
	myalgo(&a,i);
	forcfree(clone);
	// lstbinary(&a);
	// bitonicsort(&a, i + 1);
}
