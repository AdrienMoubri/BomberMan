/*
** creature_order.c for  in /home/vikerns/Battle/letors_p/etape2
** 
** Made by LE TORS DE CRECY Pierre
** Login   <letors_p@etna-alternance.net>
** 
** Started on  Mon May  8 22:28:49 2017 LE TORS DE CRECY Pierre
** Last update Sat May 13 16:20:24 2017 MOUBRI Adrien
*/

#include "bfm.h"

void		creature_killed(t_env *env)
{
  if (env->hero->team->selected->digimon->pv <= 0)
    {
      del_digimon_from_team(env->hero->team->selected, env->hero);
      env->hero->team->selected = NULL;
      env->fight = 0;
      my_putstr("Your Digimon has been slayed! \n");
    }
}

void		mob_attacking(t_env *env, int i)
{
  if (i == 1)
    creature_slash(env);
  else if (i == 2)
    creature_fire(env);
  else if (i == 3)
    creature_gamble(env);
  else if (i == 4)
    creature_rest(env);
  creature_killed(env);
}

void		mob_random(t_env *env)
{
  int		i;

  i = (my_rand() % 4) + 1;
  if (i == 4 && env->creature->pm >= env->creature->pm_max)
    mob_random(env);
  else
    mob_attacking(env, i);
}
