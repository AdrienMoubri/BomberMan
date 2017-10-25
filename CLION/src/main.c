/*
** main.c for bfm in /home/mathieu/Desktop/prog_c/Battle_For_Midgard
**
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
**
** Started on  Wed May 10 10:04:03 2017 MOUBRI Adrien
** Last update Sun May 14 10:11:50 2017 MOUBRI Adrien
*/

#include <time.h>
#include "bfm.h"

void		free_universe(t_env *env)
{
  while (env->hero->team->first)
    {
      del_digimon_from_team(env->hero->team->first, env->hero);
    }
  free(env->hero->team);
  free(env->hero->name);
  free(env->hero);
  free(env->creature->name);
  free(env->creature);
  free(env);
}

int		main(int argc, char** argv)
{
  t_env		*env;
  char		*name;
  SDL_Event	*event;

  name = "sacha";
  srand(time(NULL));
  event = malloc (sizeof(SDL_Event));
  if (argc > 2 && my_strcmp(argv[1], "-n") == 0)
    {
      name = argv[2];
    }
  env = init_game(name);
  if (env && event)
    {
      init_screen(env);
      while (event->type != SDL_KEYUP)
        {
          SDL_WaitEvent(event);
        }
      play(env, event);
      free(event);
      free_universe(env);
      }
  return (0);
}
