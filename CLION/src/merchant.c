/*
** merchant.c for bfm in /home/mathieu/Desktop/prog_c/Battle_For_Midgard/letors_p/etape3
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Thu May 11 12:22:10 2017 MOUBRI Adrien
** Last update Sun May 14 22:18:38 2017 MOUBRI Adrien
*/

#include "bfm.h"
/*
void				buy_magic_box(int *argent, int *box, t_env *env)
{
  int				i;

  i = 1;
  if (*argent > (i * MAGIC_BOX_PRICE))
    {
      *box += i;
      *argent -= (i * MAGIC_BOX_PRICE);
      set_text("you bought a magic_box\n", env);
    }
  else
    {
      set_text("you don't have enough money for that ...\n", env);
    }
}

void				buy_shroom(int *argent, int *shroom, t_env *env)
{
  int				i;

  i = 1;
  if (*argent > (i * MUSHROOM_PRICE))
    {
      *shroom += i;
      *argent -= (i * MUSHROOM_PRICE);
      set_text("you bought a shroom\n", env);
    }
  else
    {
      set_text("you don't have enough money for that ...\n", env);
    }
}

void				merchant(t_env *env, SDL_Event *event)
{
  int				*argent;
  char				*str;

  argent = &(env->hero->rupees);
  str = "Vous avez : 320 Rupees\n a : 1 magic_box z : 1 mushroom \n votre choix->";
  set_text(str, env);
  SDL_WaitEvent(event);
  while (event->type != SDL_KEYUP)
    {
      SDL_WaitEvent(event);
    }
  if (event->key.keysym.sym == SDLK_a)
    {
      buy_magic_box(argent, &env->hero->magic_ball, env);
    }
  else if (event->key.keysym.sym == SDLK_z)
    {
      buy_shroom(argent, &env->hero->shroom, env);
    }
}

void				eat_that_shroom(t_creature *creature)
{
  int				pv_won;
  float				percent;

  percent = (my_rand() % 11) + 15;
  pv_won = percent / 100 * creature->pv_max;
  creature->pv += pv_won;
  if (creature->pv > creature->pv_max)
    creature->pv = creature->pv_max;
  my_putstr("Your digimon now have ");
  my_put_nbr(creature->pv);
  my_putstr("hp ! \n");
}

void				eat_shroom(t_env *env)
{
  t_creature			*creature;

  if (env->hero->team->selected)
    {
      creature = env->hero->team->selected->digimon;
      if (env->hero->shroom > 0)
	{
	  my_putstr("You have ");
	  my_put_nbr(env->hero->shroom);
	  my_putstr(" left.\n");
	  if (creature->pv != creature->pv_max)
	    {
	      env->hero->shroom -= 1;
	      eat_that_shroom(creature);
	    }
	  else
	    my_putstr("Your digimon don't feel hungry.\n");
	}
      else
	my_putstr("You don't have a shroom left !\n");
    }
  else
    my_putstr("please select a digimon.\n");
}
*/