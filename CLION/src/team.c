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

int		create_hero_list(t_env *env)
{
  t_hero_list	    *hero_l;
  t_hero_elem	    *hero_e;

  hero_l = malloc(sizeof (t_hero_list));
  if (hero_l)
    {
      hero_e = NULL;
      hero_l->first = hero_e;
      hero_l->last = hero_e;
      hero_l->nb_elem = 0;
      env->heroes = hero_l;
      return (1);
    }
  return (0);
}

void		del_elem(t_hero_list *hero_l, t_hero_elem *hero_e)
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

void		add_hero_to_list(t_hero_elem *hero_e, t_hero_list *hero_l)
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

void		del_hero_from_list(t_hero_elem *node, t_hero_list *hero)
{
    t_hero_elem	*hero_e;

  hero_e = hero->first;
  while (hero_e != NULL && node != hero_e)
    {
      hero_e = hero_e->next;
    }
  free(hero_e->hero->name);
  free(hero_e->hero);
  del_elem(hero, hero_e);
}
