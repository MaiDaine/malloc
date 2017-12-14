/*
** realloc.c for malloc in /home/daine/EPI/rendu/C/PSU_2016_malloc
**
** Made by david.maidenberg@epitech.eu
** Login   <david.maidenberg@epitech.eu>
**
** Started on  Fri Feb 10 15:18:58 2017 david.maidenberg@epitech.eu
** Last update Fri Feb 10 15:30:27 2017 david.maidenberg@epitech.eu
*/

#include "libHeader.h"

void				*check_realloc(void *ptr, size_t size)
{
  if (ptr == NULL)
    return (malloc(size));
  else if (size == 0)
    {
      free(ptr);
      return (malloc(0));
    }
  return ((void *)1);
}

void				*realloc(void *ptr, size_t size)
{
  void				*tmp;
  char				store;
  size_t			calc;
  size_t			i;

  if ((tmp = check_realloc(ptr, size)) != (void *)1)
    return (tmp);
  store = ~(*((char *)(ptr - 1)));
  if (store < 0)
    return (malloc(size));
  i = (size_t )pow(2, store);
  if (i > size)
    return (ptr);
  if ((tmp = malloc(size)) == NULL)
    return (NULL);
  i = 0;
  calc = (size_t )pow(2, store);
  while (i < calc)
    {
      ((char *)tmp)[i] = ((char *)ptr)[i];
      ++i;
    }
  free(ptr);
  return (tmp);
}
