/*
** order.c for bfm in /home/mathieu/Desktop/prog_c/Battle_For_Midgard
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Wed May 10 11:16:06 2017 MOUBRI Adrien
** Last update Sun May 14 14:43:50 2017 MOUBRI Adrien
*/

#include "bfm.h"

void				quit_battle(t_env *env)
{
  env->play = 0;
}

void				help_me(t_env *env)
{
  free(env->creature->name);
  free(env->creature);
  env->creature = get_creature();
  env->fight = 0;
}

static const t_hero_order	g_order[] =
  {
    {SDLK_SPACE, chance_catch},
    {SDLK_w, help_me},
    {SDLK_ESCAPE, quit_battle},
    {SDLK_a, slash},
    {SDLK_z, fire},
    {SDLK_e, gamble},
    {SDLK_r, rest},
    {0, NULL}
  };

void				hero_order(t_env *env, SDL_Event *event)
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
  while (g_order[i].key)
    {
      if (event->key.keysym.sym == g_order[i].key)
	{
	  g_order[i].order(env);
	  return ;
	}
      i += 1;
    }
  my_putstr_color("red", "Commande unknow\n");
  hero_order(env, event);
}
