/*
** tree_handler.c for malloc in /home/daine/EPI/rendu/C/PSU_2016_malloc
**
** Made by david.maidenberg@epitech.eu
** Login   <david.maidenberg@epitech.eu@epitech.net>
**
** Started on  Fri Feb 10 16:09:37 2017 david.maidenberg@epitech.eu
** Last update Sun Feb 12 14:59:05 2017 david.maidenberg@epitech.eu
*/

#include "libHeader.h"

void			split_block(void *node, char real_size,
				    char split_size)
{
  char			tmp_size;
  size_t		calc_size;
  void			*tmp;

  tmp_size = real_size - (char)1;
  while (tmp_size >= split_size)
    {
      calc_size = (size_t )pow(2, tmp_size);
      tmp = node + calc_size;
      *((char *)tmp) = tmp_size;
      add_to_freeList(tmp + 1, tmp_size);
      --tmp_size;
    }
}

void			*single_add(char size)
{
  size_t		store;
  void			*tmp;

  store = (size_t)(pow(2, g_block_size));
  tmp = g_end - 1;
  if (sbrk(store) == (void *)-1)
    return (NULL);
  g_end += store;
  *(char *)tmp = g_block_size;
  ++g_block_size;
  if (g_block_size > size)
    split_block(tmp, g_block_size - (char)1, size);
  *(char *)tmp = ~size;
  return (tmp + 1);
}

void			*grow_up(char size)
{
  void			*tmp;

  if (g_block_size >= 63)
    return (NULL);
  if (size <= g_block_size)
    return (single_add(size));
  else
    {
      tmp = g_end - 1;
      while (g_block_size < size)
	grow_up(g_block_size);
      return (tmp + 1);
    }
}

void			*grow_down(char size)
{
  void			*tmp;
  char			store;

  store = size + (char)1;
  while (store < g_block_size)
    {
      if ((tmp = search_tree(store, 1)) != NULL)
        {
	  split_block(tmp, store, size);
	  *((char *)tmp) = ~size;
	  return (tmp + 1);
        }
      ++store;
    }
  return (grow_up(size));
}

void			*search_tree(char size, char mod)
{
  t_list		*tmp;
  char			store;

  store = size - (char)MIN_SIZE;
  if (g_freeList[(int)store] != NULL)
    {
      tmp = g_freeList[(int)store];
      g_freeList[(int)store] = tmp->next;
      if (tmp->next != NULL)
	tmp->next->prev = NULL;
      memset(tmp, 0, 16);
      if (mod == 0)
        {
	  *(((char *)tmp - 1)) = ~size;
	  return (tmp);
        }
      else
	return ((char *)tmp - 1);
    }
  return ((mod == 0) ? grow_down(size) : NULL);
}
