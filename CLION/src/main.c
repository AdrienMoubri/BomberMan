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
  srand(time(NULL));
  event = malloc (sizeof(SDL_Event));
  env = init_game(name);
  if (env && event)
    {
      init(env->simple_env);
      init_screen(env);
      while (env->play) {
        event->key.keysym.sym = 0;
        launch_menu(env, event);
        if (env->server)
            launch_gameServer(env, event);
        else
            launch_gameClient(env, event);
          SDL_PollEvent(event);
          pthread_cancel(env->simple_env->thread_recv);
          pthread_cancel(env->simple_env->thread_send);
          #ifdef WIN32
            closesocket(env->simple_env->socket_recv);
            closesocket(env->simple_env->socket_send);
          #else
            close(env->simple_env->socket_recv);
            close(env->simple_env->socket_send);
          #endif
      }
      free(event);
      free_universe(env);
    }
  return (0);
}
