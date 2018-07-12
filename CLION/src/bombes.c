/*
** team.c for bfm in /home/mathieu/Desktop/prog_c/Battle_For_Midgard
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Wed May 10 10:54:30 2017 MOUBRI Adrien
** Last update Sat May 13 12:43:39 2017 MOUBRI Adrien
*/

#include "bfm.h"

int		create_bomb_list(t_hero *env)
{
  t_bomb_list	    *hero_l;
  t_bomb_elem	    *hero_e;

  hero_l = malloc(sizeof (t_bomb_list));
  if (hero_l)
    {
      hero_e = NULL;
      hero_l->first = hero_e;
      hero_l->last = hero_e;
      hero_l->nb_elem = 0;
      env->bombes = hero_l;
      return (1);
    }
  return (0);
}

void		del_bomb_elem(t_bomb_list *hero_l, t_bomb_elem *hero_e)
{
  if (hero_e != NULL)
    {
      if (hero_e->prev)
        {
          hero_e->prev->next = hero_e->next;
          if (hero_e->next)
            hero_e->next->prev = hero_e->prev;
          else
	    hero_l->last = hero_e->prev;
        }
      else if (hero_e->next)
        {
          hero_l->first = hero_e->next;
          hero_e->next->prev = NULL;
        }
      else
        {
          hero_l->first = NULL;
	  hero_l->last = NULL;
        }
      hero_l->nb_elem -= 1;
      free(hero_e);
    }
}

void		add_bomb_to_list(t_bomb_elem *hero_e, t_bomb_list *hero_l)
{
  if (hero_e)
    {
      hero_e->next = NULL;
      if (!hero_l->first)
        {
          hero_l->first = hero_e;
          hero_e->prev = NULL;
        }
      else
        {
          hero_l->last->next = hero_e;
          hero_e->prev = hero_l->last;
        }
      hero_l->last = hero_e;
      hero_l->nb_elem += 1;
    }
}

void		del_bomb_from_list(t_bomb_elem *node, t_bomb_list *hero)
{
  t_bomb_elem	*hero_e;

  hero_e = hero->first;
  while (hero_e != NULL && node != hero_e) {
      hero_e = hero_e->next;
  }
  free(hero_e->bomb);
  del_bomb_elem(hero, hero_e);
}

void		del_bomb(t_bomb_elem *node, t_bomb_list *hero, t_map *map)
{
    for (int x = 0; x < WIDTH_MAP; x++)
    {
        for (int y = 0; y < HEIGHT_MAP; y++)
        {
            if (map->case_tab[x][y].type >= 3 && map->case_tab[x][y].type != 10 && map->case_tab[x][y].type != 22)
            {
                map->case_tab[x][y].type = 0;
            }
        }
    }
    del_bomb_from_list(node, hero);
}