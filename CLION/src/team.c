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

int		add_team_to_hero(t_hero *hero)
{
  t_team	*team;
  t_digimon	*digimon;

  team = malloc(sizeof (t_team));
  if (team)
    {
      digimon = NULL;
      team->first = digimon;
      team->last = digimon;
      team->nb_elem = 0;
      team->selected = NULL;
      hero->team = team;
      return (1);
    }
  return (0);
}

void		del_elem(t_hero *hero, t_digimon *digimon)
{
  if (digimon != NULL)
    {
      if (digimon->prev)
        {
          digimon->prev->next = digimon->next;
          if (digimon->next)
            digimon->next->prev = digimon->prev;
          else
	    hero->team->last = digimon->prev;
        }
      else if (digimon->next)
        {
          hero->team->first = digimon->next;
          digimon->next->prev = NULL;
        }
      else
        {
          hero->team->first = NULL;
	  hero->team->last = NULL;
        }
      hero->team->nb_elem -= 1;
      free(digimon);
    }
}

void		add_digimon_to_team(t_digimon *node, t_hero *hero)
{
  if (node)
    {
      node->next = NULL;
      if (!hero->team->first)
        {
          hero->team->first = node;
          node->prev = NULL;
        }
      else
        {
          hero->team->last->next = node;
          node->prev = hero->team->last;
        }
      hero->team->last = node;
      hero->team->nb_elem += 1;
    }
}

void		del_digimon_from_team(t_digimon *node, t_hero *hero)
{
  t_digimon	*digimon;

  digimon = hero->team->first;
  while (digimon != NULL && node != digimon)
    {
      digimon = digimon->next;
    }
  free(digimon->digimon->name);
  free(digimon->digimon);
  del_elem(hero, digimon);
}
