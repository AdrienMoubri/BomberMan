/*
** mob_attacks.c for mobs_attacks.c in /home/vikerns/Battle/letors_p/etape2
** 
** Made by LE TORS DE CRECY Pierre
** Login   <letors_p@etna-alternance.net>
** 
** Started on  Mon May  8 22:06:04 2017 LE TORS DE CRECY Pierre
** Last update Sat May 13 16:29:14 2017 MOUBRI Adrien
*/

#include "bfm.h"

void		creature_slash(t_env *env)
{
  int		*pv_left;

  pv_left = &env->hero->team->selected->digimon->pv;
  env->hero->team->selected->digimon->pv -= 15;
  env->creature->pm -= 3;
  my_putstr("The creature deals you 15 damages and loose 3 mp's \n");
  my_putstr("You'r Digimon have ");
  my_put_nbr(*pv_left);
  my_putstr("pv left! \n");
}

void		creature_fire(t_env *env)
{
  int		*pv_left;

  pv_left = &env->hero->team->selected->digimon->pv;
  env->hero->team->selected->digimon->pv -= 30;
  env->creature->pm -= 7;
  my_putstr("The creature deals you 30 damages and loose 7 mp's");
  my_putstr("\n");
  my_putstr("You'r Digimon have ");
  my_put_nbr(*pv_left);
  my_putstr("pv left! \n");
}

void		creature_gamble(t_env *env)
{
  int		i;
  int		*pv_left;
  int		*pvm_left;

  i = (my_rand() % 20) + 1;
  pv_left = &env->hero->team->selected->digimon->pv;
  pvm_left = &env->creature->pv;
  if (my_rand() < 50)
    {
      env->creature->pv -= i;
      my_putstr("The creature inflict itself ");
      my_put_nbr(i);
      my_putstr(" damages \nThe creature have \n");
      my_put_nbr(*pvm_left);
    }
  else
    {
      env->hero->team->selected->digimon->pv -= i;
      my_putstr("The creature deals you ");
      my_put_nbr(i);
      my_putstr(" damages\nYou'r Digimon have ");
      my_put_nbr(*pv_left);
    }
  my_putstr("pv_left! \n");
}

void		creature_rest(t_env *env)
{
  int		*mana_left;

  mana_left = &env->hero->team->selected->digimon->pm;
  env->creature->pm += 10;
  if (env->creature->pm > env->creature->pm_max)
    env->creature->pm = env->creature->pm_max;
  my_putstr("The creature end his turn and recover 10 mp's");
  my_putstr("\n");
  my_putstr("The creature have ");
  my_put_nbr(*mana_left);
  my_putstr("mana left! \n");
}
