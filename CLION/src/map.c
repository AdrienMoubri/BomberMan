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



/*
int		create_case_list(t_map *env)
{
  t_case_list	    *case_l;
  t_case_elem	    *case_e;

  case_l = malloc(sizeof (t_bomb_list));
  if (case_l)
    {
      case_e = NULL;
      case_l->first = case_e;
      case_l->last = case_e;
      case_l->nb_elem = 0;
      env->case_list = case_l;
      return (1);
    }
  return (0);
}

void		del_case_elem(t_case_list *case_l, t_case_elem *case_e)
{
  if (case_e != NULL)
    {
      if (case_e->prev)
        {
          case_e->prev->next = case_e->next;
          if (case_e->next)
            case_e->next->prev = case_e->prev;
          else
	    case_l->last = case_e->prev;
        }
      else if (case_e->next)
        {
          case_l->first = case_e->next;
          case_e->next->prev = NULL;
        }
      else
        {
          case_l->first = NULL;
	  case_l->last = NULL;
        }
      case_l->nb_elem -= 1;
      free(case_e);
    }
}

void		add_case_to_list(t_case_elem *case_e, t_case_list *case_l)
{
  if (case_e)
    {
      case_e->next = NULL;
      if (!case_l->first)
        {
          case_l->first = case_e;
          case_e->prev = NULL;
        }
      else
        {
          case_l->last->next = case_e;
          case_e->prev = case_l->last;
        }
      case_l->last = case_e;
      case_l->nb_elem += 1;
    }
}

void		del_case_from_list(t_case_elem *node, t_case_list *case_l)
{
  t_case_elem	*case_e;

  case_e = case_l->first;
  while (case_e != NULL && node != case_e)
    {
      case_e = case_e->next;
    }
  free(case_e->my_case->image);
  free(case_e->my_case);
  del_case_elem(case_l, case_e);
}*/
