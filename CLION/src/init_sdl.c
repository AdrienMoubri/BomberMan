/*
** init_sdl.c for my_ftl in /home/mathieu/Desktop/prog_c/MY_FTL/moubri_a/sdl
**
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
**
** Started on  Sat Apr 15 10:19:29 2017 MOUBRI Adrien
** Last update Sun May 14 19:01:28 2017 MOUBRI Adrien
*/

#include "bfm.h"

static const t_load_img       g_img_map[] =
  {
    {"bulbasaur", "my_bfm_img/bulbasaur.png", "my_bfm_img/bulbasaur_back.png"},
    {"charmander", "my_bfm_img/charmander.png", "my_bfm_img/charmander_back.png"},
    {"dragonair", "my_bfm_img/dragonair.png", "my_bfm_img/dragonair_back.png"},
    {"mewtwo", "my_bfm_img/mewtwo.png", "my_bfm_img/mewtwo_back.png"},
    {"squirtle", "my_bfm_img/squirtle_back.png", "my_bfm_img/squirtle.png"},
    {"pikachu", "my_bfm_img/pikachu.png", "my_bfm_img/pikachu_back.png"},
    {"torchic", "my_bfm_img/torchic.png", "my_bfm_img/torchic_back.png"},
    {NULL, NULL, NULL}
  };

void	select_img(t_env *env)
{
  int	i;

  i = 0;

  if (env->screen->hero != NULL)
    free(env->screen->hero);
  if (env->screen->creature!= NULL)
    free(env->screen->creature);
  if (!env->hero->team->selected)
    env->screen->hero = IMG_Load("my_bfm_img/hero.png");
  else
    {
      while (g_img_map[i].key)
	{
	  if (my_strcmp(env->hero->team->selected->digimon->name, g_img_map[i].key) == 0)
	    {
	      env->screen->hero = IMG_Load(g_img_map[i].back);
	    }
	  i += 1;
	}
    }
  i = 0;
  while (g_img_map[i].key)
    {
      if (my_strcmp(env->creature->name, g_img_map[i].key) == 0)
	{
	  env->screen->creature = IMG_Load(g_img_map[i].front);
	  my_putstr(g_img_map[i].front);
	}
      i += 1;
    }
}

void	init_menu(t_env *env)
{
  SDL_BlitSurface(env->screen->menu, NULL, env->screen->ecran, \
		  &(env->screen->positionMenu));
  env->screen->police = TTF_OpenFont("angelina.ttf", 35);
  env->screen->text = TTF_RenderText_Blended(env->screen->police, \
					      "Press a key to continue ", env->screen->couleurNoire);
  SDL_BlitSurface(env->screen->text, NULL, \
		  env->screen->ecran, &(env->screen->positionMenu));
  SDL_Flip(env->screen->ecran);
}

void	init_screen(t_env *env)
{
  env->screen = malloc (sizeof (t_screen));
  if (env->screen)
    {
      SDL_Init(SDL_INIT_VIDEO);
      TTF_Init();
      env->screen->ecran = NULL;
      env->screen->menu = NULL;
      env->screen->ecran = SDL_SetVideoMode(WIDTH_WINDOW, WIDTH_WINDOW, \
                                            32, SDL_HWSURFACE | SDL_DOUBLEBUF);
      SDL_WM_SetCaption("The adventure of sacha", NULL);
      env->screen->menu = IMG_Load("my_bfm_img/menu.png");
      env->screen->town = IMG_Load("my_bfm_img/town_background.png");
      env->screen->battle = IMG_Load("my_bfm_img/fight_background.png");
      env->screen->hero = IMG_Load("my_bfm_img/hero.png");
      env->screen->positionMenu.x = 0;
      env->screen->positionMenu.y = 0;
      env->screen->positionBackground.x = 0;
      env->screen->positionBackground.y = 0;
      env->screen->positionCreature.x = 400;
      env->screen->positionCreature.y = 100;
      env->screen->positionText.x = 15;
      env->screen->positionText.y = 420;
      env->screen->positionCadre.x = 0;
      env->screen->positionCadre.y = 400;
      env->screen->cadre = SDL_CreateRGBSurface(0, 500, 100, 32, 1, 0xff,0xff,0xff);
      init_menu(env);
    }
}

void	free_sdl(t_env *env)
{
  TTF_CloseFont(env->screen->police);
  SDL_FreeSurface(env->screen->menu);
  SDL_FreeSurface(env->screen->hero);
  SDL_FreeSurface(env->screen->cadre);
  SDL_FreeSurface(env->screen->text);
  SDL_FreeSurface(env->screen->creature);
  SDL_FreeSurface(env->screen->background);
  SDL_FreeSurface(env->screen->ecran);
  TTF_Quit();
  SDL_Quit();
}
