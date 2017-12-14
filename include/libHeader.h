/*
** libHeader.h for malloc in /home/daine/test/testmalloc/SAVESAVE
**
** Made by david.maidenberg@epitech.eu
** Login   <david.maidenberg@epitech.eu@epitech.net>
**
** Started on  Fri Feb 10 16:22:08 2017 david.maidenberg@epitech.eu
** Last update Fri Feb 10 16:30:16 2017 Daine
*/

#ifndef LIBHEADER_H_
#define LIBHEADER_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

#define MAX_POW_ALLOC 62
#define DEBUG_OFFSET 7
typedef struct s_list t_list;
struct				s_list
{
  t_list			*prev;
  t_list			*next;
};

#define MIN_SIZE 5

void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t nmemb, size_t size);
void				free(void *ptr);

void				show_alloc_mem(void);

char				my_binaryLog(size_t size);
void				*search_tree(char size, char mod);
void				*new_block(char size);
void				add_to_freeList(void *node, char size);
void				split_block(void *node, char real_size, char split_size);
char				is_in_freeList(void *node, char offset);
void				*search_tree(char size, char mod);

extern int			g_pageSize;
extern void			*g_root;
extern void			*g_end;
extern char			g_block_size;
extern void			*g_freeList[];
extern pthread_mutex_t		g_lock;

#endif /* ! LIBHEADER_H_ */
