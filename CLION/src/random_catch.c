/*
** random_catch.c for random_capture.c in /home/vikerns/Battle/letors_p/etape2end
** 
** Made by LE TORS DE CRECY Pierre
** Login   <letors_p@etna-alternance.net>
** 
** Started on  Wed May 10 00:32:06 2017 LE TORS DE CRECY Pierre
** Last update Sun May 14 22:32:49 2017 MOUBRI Adrien
*/

#include "bfm.h"
/*
void				magic_catch(t_env *env)
{
  t_digimon			*node;
  char				str[80];

  node = malloc(sizeof(t_digimon));
  if (node)
    {
      node->digimon = malloc(sizeof(t_creature));
      if (node->digimon)
	{
	  node->digimon->pv_max = env->creature->pv_max * 2;
	  node->digimon->pv = node->digimon->pv_max;
	  node->digimon->pm = env->creature->pm_max * 2;
	  node->digimon->pm_max = env->creature->pm_max *2;
	  node->digimon->lvl = env->creature->lvl;
	  node->digimon->name = my_strdup(env->creature->name);
	  add_digimon_to_team(node, env->hero);
	  free(env->creature->name);
	  free(env->creature);
	  env->creature = get_creature();
	  my_strcat(str,"Succesfully add a ");
	  my_strcat(str, node->digimon->name);
	  my_strcat(str," in your team");
	  set_text(str, env);
	  env->fight = 0;
	}
    }
}

void				random_catch(t_env *env)
{
  int				delta_pv;
  int				percent;

  delta_pv = env->creature->pv_max - env->creature->pv;
  percent = 30 + (delta_pv / env->creature->pv_max) * 100;
  if (my_rand() <= percent)
    {
      magic_catch(env);
    }
  else
    my_putstr("The magic_ball bounce off");
}

void				chance_catch(t_env *env)
{
  
  if (env->hero->magic_ball > 0)
    {
      env->hero->magic_ball--;
      my_putstr("You have ");
      my_put_nbr(env->hero->magic_ball);
      my_putstr(" magic_ball left\n");
      if (env->hero->team->selected)
	random_catch(env);
      else if (my_rand() < 60)
	magic_catch(env);
      else
	{
	  my_putstr("The creature run away\n");
	  free(env->creature->name);
	  free(env->creature);
	  env->creature = get_creature();
	  env->fight = 0;
	}
    }
  else
    set_text("You don't have a magic ball", env);
}
*/