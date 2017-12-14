/*
** annexe.c for malloc in /home/daine/EPI/rendu/C/PSU_2016_malloc
**
** Made by david.maidenberg@epitech.eu
** Login   <david.maidenberg@epitech.eu>
**
** Started on  Fri Feb 10 08:15:46 2017 david.maidenberg@epitech.eu
** Last update Fri Feb 10 15:12:11 2017 david.maidenberg@epitech.eu
*/

#include "libHeader.h"

void			show_alloc_mem(void)
{
  void			*tmp;
  char			store;
  size_t		size;

  tmp = g_root - DEBUG_OFFSET;
  store = ~(*(char *)tmp);
  size = pow(2, store);
  tmp += size;
  while (tmp < g_end)
    {
      store = ~(*(char *)tmp);
      if (store > 0)
	{
	  size = pow(2, store);
	  printf("%p - %p : %lu\n", tmp, tmp + size, size);
	}
      tmp += size;
    }
}

char			my_binaryLog(size_t size)
{
  char			store;

  store = (char)log2(size);
  if (size > pow(2, store))
    ++store;
  return (store);
}

char			is_in_freeList(void *node, char offset)
{
  t_list		*tmp;

  tmp = g_freeList[(int)offset];
  while (tmp != NULL)
    {
      if (tmp == node)
	return (0);
      tmp = tmp->next;
    }
  return (1);
}

void			*new_block(char size)
{
  if (size > MAX_POW_ALLOC)
    return (NULL);
  return (search_tree(size, 0));
}
