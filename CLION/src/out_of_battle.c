/*
** out_of_battle.c for out_of_battle.c in /home/vikerns/Battle/letors_p/etape2
**
** Made by LE TORS DE CRECY Pierre
** Login   <letors_p@etna-alternance.net>
**
** Started on  Mon May  8 08:16:07 2017 LE TORS DE CRECY Pierre
** Last update Sun May 14 23:03:31 2017 MOUBRI Adrien
*/

#include "bfm.h"

void				quit(t_env *env)
{
  env->play = 0;
}

void				team(t_env *env)
{
  t_digimon			*creature;
  char				str[80];

  creature = env->hero->team->first;
  my_strcat(str, "Your team\n");
  while (creature != NULL)
    {
      my_strcat(str, creature->digimon->name);
      my_strcat(str, "\n");
      creature = creature->next;
    }
  my_strcat(str, "the choosen one is ");
  if (env->hero->team->selected)
    my_strcat(str, env->hero->team->selected->digimon->name);
  else
    my_strcat(str, "Null");
  set_text(str, env);
}

void				fight(t_env *env)
{
  env->fight = 1;
}

void				choosen_one(t_env *env, SDL_Event *event)
{
  t_digimon			*creature;

  team(env);
  SDL_WaitEvent(event);
  while (event->type != SDL_KEYUP)
    {
      SDL_WaitEvent(event);
    }
  if (env->hero->team->first)
    {
      creature = env->hero->team->first;
      if (event->key.keysym.sym == SDLK_z && creature->next)
	  creature = creature->next;
      else if (event->key.keysym.sym == SDLK_e && creature->next->next)
	  creature = creature->next->next;
      env->hero->team->selected = creature;
    }
}

static const t_hero_order	g_order[] =
  {
    {SDLK_ESCAPE, quit},
    {SDLK_a, team},
    {SDLK_z, choosen_one},
    {SDLK_e, merchant},
    {SDLK_r, eat_shroom},
    {SDLK_SPACE, fight},
    {0, NULL}
  };

void				order_out_battle(t_env *env, SDL_Event *event)
{
  int				i;

  i = 0;
  my_putstr("waiting_for_orders->");
  display_screen(env);
  SDL_WaitEvent(event);
  while (event->type != SDL_KEYUP)
    {
      SDL_WaitEvent(event);
    }
  my_putstr_color("clear", "");
  while (g_order[i].key != 0)
    {
      if (event->key.keysym.sym == g_order[i].key)
	{
	  if (g_order[i].key == SDLK_e || g_order[i].key == SDLK_z)
	      g_order[i].order(env, event);
    	  else
	    g_order[i].order(env);
	  return ;
	}
      i += 1;
    }
  my_putstr_color("red", "Commande unknow\n");
}
