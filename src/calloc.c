/*
** calloc.c for malloc in /home/daine/EPI/rendu/C/PSU_2016_malloc
**
** Made by david.maidenberg@epitech.eu
** Login   <david.maidenberg@epitech.eu>
**
** Started on  Fri Feb 10 13:54:47 2017 david.maidenberg@epitech.eu
** Last update Fri Feb 10 13:59:26 2017 david.maidenberg@epitech.eu
*/

#include "libHeader.h"

void				*calloc(size_t nmemb, size_t size)
{
  char				*tmp;
  size_t			store;

  store = nmemb * size;
  if ((tmp = malloc(store)) == NULL)
    return (NULL);
  memset(tmp, 0, store);
  return (tmp);
}
