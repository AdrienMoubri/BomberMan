#include "bfm.h"


void draw_Menu(t_env *env)
{
    SDL_FillRect(env->screen->ecran, NULL, SDL_MapRGB(env->screen->ecran->format, 255, 255, 255));
    SDL_BlitSurface(env->screen->menu, NULL, env->screen->ecran, &(env->screen->positionMenu));
    SDL_BlitSurface(env->screen->rect_text_haut, NULL, env->screen->ecran, &(env->screen->positionTextHaut));
    SDL_BlitSurface(env->screen->rect_text_bas, NULL, env->screen->ecran, &(env->screen->positionTextBas));
    SDL_BlitSurface(env->screen->text, NULL, env->screen->ecran, &(env->screen->positionText));
    SDL_BlitSurface(env->screen->selector, NULL, env->screen->ecran, &(env->screen->positionSelector));
    SDL_Flip(env->screen->ecran);
}

void draw_Game(t_env *env)
{
    SDL_FillRect(env->screen->ecran, NULL, SDL_MapRGB(env->screen->ecran->format, 255, 255, 255));
    SDL_BlitSurface(env->screen->map, NULL, env->screen->ecran, &(env->screen->positionMenu));
    // utiliser la liste à la place
    t_hero_elem *hero_i = env->heroes->first;
    for(int i = 0; i < env->heroes->nb_elem; i++, hero_i = hero_i->next) {

        /*SDL_BlitSurface(env->heroes->first->hero->image->hero_img, &(env->sizeHero), env->screen->ecran,
                        &(hero_i->hero->position));*/

        t_hero_img_elem *img = find_hero_img(hero_i->hero->numHero, hero_i->hero->orientation, env->heroes_img);
        if ( img != NULL)
            SDL_BlitSurface(img->hero->hero_img, &(env->sizeHero), env->screen->ecran, &(hero_i->hero->position));
        if (env->sizeHero.x + env->sizeHero.w >= env->heroes->first->hero->image->hero_img->w)
            env->sizeHero.x = 0;
        else
            env->sizeHero.x += env->sizeHero.w;
    }
    SDL_Flip(env->screen->ecran);
}
