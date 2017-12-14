/*
** free.c for malloc in /home/daine/EPI/rendu/C/PSU_2016_malloc
**
** Made by david.maidenberg@epitech.eu
** Login   <david.maidenberg@epitech.eu>
**
** Started on  Fri Feb 10 13:55:39 2017 david.maidenberg@epitech.eu
** Last update Sun Feb 12 13:32:24 2017 david.maidenberg@epitech.eu
*/

#include "libHeader.h"

void				inner_left(void *tmp, void *merge,
					   char store, char offset)
{
  t_list			*list;

  *((char *)merge) = 0;
  *(char *)tmp = store + (char)1;
  list = merge + 1;
  if (g_freeList[(int)offset] == merge + 1)
    {
      g_freeList[(int)offset] = list->next;
      list = g_freeList[(int)offset];
      if (list != NULL && list->prev != NULL)
	list->prev = NULL;
    }
  else
    {
      if (list != NULL && list->next != NULL)
	list->next->prev = list->prev;
      if (list != NULL && list->prev != NULL)
	list->prev->next = list->next;
    }
}

void				free_left(void *tmp, char store,
					  char offset, size_t save)
{
  void				*merge;

  merge = tmp + save;
  if (is_in_freeList(merge + 1, offset) == 0)
    {
      inner_left(tmp, merge, store, offset);
      *((char *)tmp) = ~(*((char *)tmp));
      pthread_mutex_unlock(&g_lock);
      free(tmp + 1);
    }
  else
    {
      pthread_mutex_unlock(&g_lock);
      add_to_freeList(tmp + 1, *(char *)tmp);
    }
}

void				inner_right(void *tmp, void *merge,
					    char store, char offset)
{
  t_list			*list;

  *((char *)merge) = store + (char)1;
  *(char *)tmp = 0;
  list = merge + 1;
  if (g_freeList[(int)offset] == merge + 1)
    {
      g_freeList[(int)offset] = list->next;
      list->prev = NULL;
    }
  else
    {
      if (list->next != NULL)
	list->next->prev = list->prev;
      if (list->prev != NULL)
	list->prev->next = list->next;
    }
}

void				free_right(void *tmp, char store,
					   char offset, size_t save)
{
  void				*merge;

  merge = tmp - save;
  if (is_in_freeList(merge + 1, offset) == 0)
    {
      inner_right(tmp, merge, store, offset);
      *((char *)merge) = ~(*((char *)merge));
      pthread_mutex_unlock(&g_lock);
      free(merge + 1);
    }
  else
    {
      pthread_mutex_unlock(&g_lock);
      add_to_freeList(tmp + 1, *(char *)tmp);
    }
}

void				free(void *ptr)
{
  void				*tmp;
  char				store;
  char				offset;
  size_t			save;

  if (ptr == NULL || g_root == NULL || ptr < g_root || ptr > g_end)
    return ;
  pthread_mutex_lock(&g_lock);
  tmp = ptr - 1;
  store = ~(*(char *)tmp);
  *(char *)tmp = store;
  save = (size_t )(pow(2, store));
  offset = store - (char)MIN_SIZE;
  if (save <= 0)
    {
      pthread_mutex_unlock(&g_lock);
      return ;
    }
  if (((size_t )(tmp - g_root) / save) % 2 == 0)
    free_left(tmp, store, offset, save);
  else
    free_right(tmp, store, offset, save);
}
