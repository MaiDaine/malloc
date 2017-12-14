/*
** malloc.c for malloc in /home/daine/EPI/rendu/C/PSU_2016_malloc
**
** Made by david.maidenberg@epitech.eu
** Login   <david.maidenberg@epitech.eu>
**
** Started on  Fri Feb 10 15:22:09 2017 david.maidenberg@epitech.eu
** Last update Sun Feb 12 13:30:12 2017 david.maidenberg@epitech.eu
*/

#include "libHeader.h"

int  g_pageSize = 0;
void *g_root = NULL;
void *g_end = NULL;
char g_block_size = 0;
void *g_freeList[25];
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

void			insert_to_freeList(void *node, char size)
{
  char			store;
  t_list		*tmp;
  t_list		*tmp_next;

  store = size - (char)MIN_SIZE;
  tmp = node;
  tmp->prev = NULL;
  if (g_freeList[(int)store] == NULL)
    {
      g_freeList[(int)store] = node;
      tmp->next = NULL;
    }
  else
    {
      tmp_next = g_freeList[(int)store];
      tmp->next = tmp_next;
      tmp_next->prev = tmp;
      g_freeList[(int)store] = node;
    }
}

void			add_to_freeList(void *node, char size)
{
  if (size == (g_block_size - 1)
      && ((node - 1) == g_root + (size_t)pow(2, size)))
    {
      --g_block_size;
      sbrk((-1 * (size_t)pow(2, size)));
      g_end = sbrk(0);
      return ;
    }
  insert_to_freeList(node, size);
}

void			init_memory(char size)
{
  char			actual;

  actual = -1;
  while (++actual < 25)
    g_freeList[(int)actual] = NULL;
  *((char *)g_root) = g_block_size;
  split_block(g_root, g_block_size, size);
}

void			*init_malloc(char size)
{
  size_t		store;
  void			*init;

  g_pageSize = getpagesize();
  init = sbrk(0);
  g_root = init + 7;
  store = (size < 12) ? (size_t )g_pageSize
    : (((size_t )pow(2, size) / g_pageSize) + 1) * g_pageSize;
  if (sbrk(store) == (void *)-1)
    return (NULL);
  g_block_size = my_binaryLog(store);
  g_end = sbrk(0);
  init_memory(size);
  *((char *)g_root) = ~size;
  return (g_root + (char)1);
}

void			*malloc(size_t size)
{
  void			*ret;

  pthread_mutex_lock(&g_lock);
  if (size < 32)
    size = 31;
  if (g_pageSize == 0 || g_root == NULL)
    ret = (init_malloc(my_binaryLog(size + 1)));
  else
    ret = (new_block(my_binaryLog(size + 1)));
  pthread_mutex_unlock(&g_lock);
  return (ret);
}
