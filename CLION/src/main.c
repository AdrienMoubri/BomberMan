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
  free_sdl(env);
  free(env);
}
/*
 * initialisation du jeu puis lancement de la boucle principal
 * on free toutes le ressources à la fin du jeu
 */
int		main(int argc, char* argv[])
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
      launch_menu(env, event);
        if (env->server)
            launch_gameServer(env, event);
        else
            launch_gameClient(env, event);
      free(event);
      free_universe(env);
    }
  return (0);
}
