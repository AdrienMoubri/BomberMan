/*
** game.c for bfm.h in /home/mathieu/Desktop/prog_c/Battle_For_Midgard
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Wed May 10 10:23:51 2017 MOUBRI Adrien
** Last update Sun May 14 18:33:06 2017 MOUBRI Adrien
*/

#include "bfm.h"

t_hero			*create_hero(char *name)
{
  t_hero		*hero;
  char			*new_name;

  my_putstr_color("blue", "Hero creation in progress...\n");
  hero = malloc(sizeof (t_hero));
  if (hero)
    {
      my_putstr_color("blue", "Hero creation done !\n");
      my_putstr_color("blue", "Welcome ");
      hero->name = my_strdup(name);
      hero->team = NULL;
      hero->shroom = 0;
      hero->magic_ball = 5;
      hero->rupees = START_PRICE;
      add_team_to_hero(hero);
      new_name = hero->name;
      my_putstr_color("blue", new_name);
      my_putstr("\n");
    }
  return (hero);
}

static t_creature	g_creatures[] =
  {
    {"bulbasaur", 1, 10, 10, 20, 20},
    {"charmander", 1, 10, 10, 20, 20},
    {"dragonair", 1, 40, 40, 20, 20},
    {"mewtwo", 1, 100, 100, 50, 50},
    {"pikachu", 1, 10, 10, 20, 20},
    {"squirtle", 1, 10, 10, 20, 20},
    {"torchic", 1, 10, 10, 20, 20},
    {NULL, 0, 0, 0, 0, 0}
  };

t_creature*		get_creature()
{
  int			rnd;
  t_creature*		crea;

  rnd = my_rand() % NBCREA;
  if ((crea = malloc(sizeof(t_creature))) == NULL)
    return (NULL);
  crea->name = my_strdup(g_creatures[rnd].name);
  if (!crea->name)
    return (NULL);
  crea->lvl = g_creatures[rnd].lvl;
  crea->pv = g_creatures[rnd].pv;
  crea->pv_max = g_creatures[rnd].pv_max;
  crea->pm = g_creatures[rnd].pm;
  crea->pm_max = g_creatures[rnd].pm_max;
  return (crea);
}

t_env			*init_game(char* name)
{
  t_env			*env;

  env = malloc(sizeof(t_env));
  if (env)
    {
      env->creature = NULL;
      env->hero = NULL;
      env->fight = 0;
      env->play = 1;
      env->hero = create_hero(name);
      env->creature = get_creature();
    }
  return (env);
}

void			rand_rupees(t_env *env)
{
  int			rupees_rand;

  rupees_rand = (my_rand() %  31) + 90;
  env->hero->rupees = env->hero->rupees + rupees_rand;
  my_putstr("You received ");
  my_put_nbr(rupees_rand);
  my_putstr(" new rupees! \n");
}

void			play(t_env *env, SDL_Event *event)
{
  char			*name;

  while (env->play)
    {
      name = env->creature->name;
      if (env->fight)
	{
	  hero_order(env, event);
	  if (env->hero->team->selected && env->creature->pv > 0 && env->fight)
	    mob_random(env);
	  else if (env->fight && env->creature->pv <= 0)
	    {
	      my_putstr("You defeated ");
	      my_putstr(name);
	      my_putstr("\n");
	      free(name);
	      free(env->creature);
	      env->creature = get_creature();
	      rand_rupees(env);
	      env->fight = 0;
	    }
	}
      else
	{
	  //	  env->screen->bakcground_pos = FIGHT_SCREEN;
	  order_out_battle(env, event);
	}
    }
}
