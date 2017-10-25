/*
** attacks.c for attacks.c in /home/vikerns/Battle/letors_p/etape2
** 
** Made by LE TORS DE CRECY Pierre
** Login   <letors_p@etna-alternance.net>
** 
** Started on  Mon May  8 21:33:06 2017 LE TORS DE CRECY Pierre
** Last update Sun May 14 22:42:08 2017 MOUBRI Adrien
*/

#include "bfm.h"

void			slash(t_env *env)
{
  //int			*pv_left;
  char			str[80];

  //  pv_left = &env->creature->pv;
  if (env->hero->team->selected)
    {
      env->creature->pv -= 15;
      env->hero->team->selected->digimon->pm -= 3;
      my_strcat(str,"You deal 15 damages and loose 3 mp's");
    }
  else
    my_strcat(str,"No Digimon selected! \n");
  set_text(str, env);
}

void			fire(t_env *env)
{
  //  int			*pv_left;
  char			str[80];

  if (env->hero->team->selected)
    {
      //  pv_left = &env->hero->team->selected->digimon->pv;
      env->creature->pv -= 30;
      env->hero->team->selected->digimon->pm -= 7;
      my_strcat(str, "You deal 30 damages and loose 7 mp's");
    }
  else
    my_strcat(str,"No Digimon selected! \n");
  set_text(str, env);
}

void			gamble(t_env *env)
{
  int			i;
  char			str[80];

  i = (my_rand() % 20) + 1;
  if (env->hero->team->selected)
    {
       if (my_rand() < 50)
	{
	  env->hero->team->selected->digimon->pv -= i;
	  my_strcat(str, "You inflict yourself ");
	}
      else
	{
	  env->creature->pv -= i;
	  my_strcat(str, "You deal ");
	}
      my_put_nbr(i);
      my_putstr(" damages \n");
      my_putstr("You'r Digimon have ");
      my_put_nbr(env->hero->team->selected->digimon->pv);
      my_putstr("pv left! \n");
    }
  else
    my_strcat(str, "No Digimon selected! \n");
}

void			rest(t_env *env)
{
  int			*mana_left;
  char			str[80];

  if (env->hero->team->selected)
    {
      mana_left = &env->hero->team->selected->digimon->pm;
      env->hero->team->selected->digimon->pm += 10;
      if (*mana_left > env->hero->team->selected->digimon->pm_max)
        *mana_left = env->hero->team->selected->digimon->pm_max;
      my_strcat(str, "You end your turn and recover 10 mp's");
    }
  else
    my_strcat(str, "No Digimon selected! \n");

}
