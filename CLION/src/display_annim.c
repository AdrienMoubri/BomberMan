/*
** display_annim.c for my_ftl in /home/mathieu/Desktop/prog_c/MY_FTL/moubri_a/sdl
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Sat Apr 15 10:52:47 2017 MOUBRI Adrien
** Last update Sun May 14 22:01:48 2017 MOUBRI Adrien
*/

#include <unistd.h>
#include "bfm.h"

void		display_screen(t_env *env)
{
  if (env->fight)
    {
      select_img(env);
      env->screen->background = env->screen->battle;
      SDL_FillRect(env->screen->ecran, NULL,					\
		   SDL_MapRGB(env->screen->ecran->format, 255, 255, 255));
      SDL_BlitSurface(env->screen->background, NULL, env->screen->ecran,	\
		      &(env->screen->positionBackground));
      SDL_BlitSurface(env->screen->creature, NULL, env->screen->ecran,  \
                      &(env->screen->positionCreature));
      SDL_BlitSurface(env->screen->hero, NULL, env->screen->ecran,	\
		      &(env->screen->positionHero));      
    }
  else
    {
      env->screen->background = env->screen->town;
      SDL_FillRect(env->screen->ecran, NULL,					\
		   SDL_MapRGB(env->screen->ecran->format, 255, 255, 255));
      SDL_BlitSurface(env->screen->background, NULL, env->screen->ecran,	\
		      &(env->screen->positionBackground));
    }
  SDL_FillRect(env->screen->cadre, NULL,					\
	       SDL_MapRGB(env->screen->cadre->format, 0, 0, 0));
  SDL_BlitSurface(env->screen->cadre, NULL, env->screen->ecran,	\
		  &(env->screen->positionCadre));
  SDL_BlitSurface(env->screen->text, NULL, env->screen->ecran,	\
		  &(env->screen->positionText));
  SDL_Flip(env->screen->ecran);
}

void		set_text(char *str, t_env *env)
{
  free(env->screen->text);
  env->screen->text = TTF_RenderText_Blended(env->screen->police,	\
					     str, env->screen->couleurNoire);
  SDL_BlitSurface(env->screen->cadre, NULL, env->screen->ecran,	\
		  &(env->screen->positionCadre));
  SDL_BlitSurface(env->screen->text, NULL, env->screen->ecran,	\
		  &(env->screen->positionText));
  SDL_Flip(env->screen->ecran);
}
/*
void            displays_ship_annim(t_screen *screen)
{
  int           i;

  i = 0;
  screen->positionship.x = 0;
  screen->positionship.y = 0;
  screen->positionBackground.x = 0;  
  screen->positionship.y = 100;
  while (i < 100)
    {
      SDL_FillRect(screen->ecran, NULL, \
                   SDL_MapRGB(screen->ecran->format, 255, 255, 255));
      screen->positionship.x = 2 * i - 200;
      SDL_BlitSurface(screen->background, NULL, screen->ecran,      \
                      &(screen->positionBackground));
      SDL_BlitSurface(screen->ship, NULL, screen->ecran,      \
                      &(screen->positionship));
      SDL_Flip(screen->ecran);
      sleep(0.4);
      i++;
    }
}

void            displays_jump_annim(t_screen *screen)
{
  int           i;

  i = 0;
  while (i < 100)
    {
      SDL_FillRect(screen->ecran, NULL, \
                   SDL_MapRGB(screen->ecran->format, 255, 255, 255));
      screen->positionship.x += 4;
      SDL_BlitSurface(screen->background, NULL, screen->ecran,      \
                      &(screen->positionBackground));
      SDL_BlitSurface(screen->ship, NULL, screen->ecran,      \
                      &(screen->positionship));
      SDL_Flip(screen->ecran);
      sleep(0.4);
      i++;
    }
  displays_ship_annim(screen);
}

void            displays_wizz_ship_annim(t_screen *screen)
{
  int           i;
  int           j;

  j = 0;
  i = 0;
  while (i < 100)
    {
      if (j <= 10)
        screen->positionship.x += 10;
      else if (j <= 20)
        screen->positionship.x -= 10;
      else
	j = 0;
      SDL_FillRect(screen->ecran, NULL, \
                   SDL_MapRGB(screen->ecran->format, 255, 255, 255));
      SDL_BlitSurface(screen->background, NULL, screen->ecran, \
                      &(screen->positionBackground));
      SDL_BlitSurface(screen->ship, NULL, screen->ecran, \
                      &(screen->positionship));
      SDL_BlitSurface(screen->enemy, NULL, screen->ecran, &(screen->positionE));
      SDL_Flip(screen->ecran);
      sleep(0.4);
      j++;
      i++;
    }
}

void            displays_enemy_annim(t_screen *screen)
{
  int		i;

  i = 0;
  screen->positionE.x = WIDTH_WINDOW;
  screen->positionE.y = 100;
  while (i < 100)
    {
      SDL_FillRect(screen->ecran, NULL,                                 \
                   SDL_MapRGB(screen->ecran->format, 255, 255, 255));
      screen->positionE.x =  WIDTH_WINDOW - (4 * i);
      SDL_BlitSurface(screen->background, NULL, screen->ecran,  \
                      &(screen->positionBackground));
      SDL_BlitSurface(screen->ship, NULL, screen->ecran,        \
                      &(screen->positionship));
      SDL_BlitSurface(screen->enemy, NULL, screen->ecran,        \
                      &(screen->positionE));
      SDL_Flip(screen->ecran);
      sleep(0.4);
      i++;
    }
}

void            displays_enemy_death_annim(t_screen *screen)
{
  int		i;

  i = 0;
  while (i < 100)
    {
      screen->positionE.y += 7;
      SDL_FillRect(screen->ecran, NULL,                                 \
                   SDL_MapRGB(screen->ecran->format, 255, 255, 255));
      SDL_BlitSurface(screen->background, NULL, screen->ecran,  \
                      &(screen->positionBackground));
      SDL_BlitSurface(screen->ship, NULL, screen->ecran,        \
                      &(screen->positionship));
      SDL_BlitSurface(screen->enemy, NULL, screen->ecran,        \
                      &(screen->positionE));
      SDL_Flip(screen->ecran);
      sleep(0.4);
      i++;
    }
}
*/
