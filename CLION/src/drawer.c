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
    // draw MAP
    for (int x = 0; x < WIDTH_MAP; x++)
    {
        for (int y = 0; y < HEIGHT_MAP; y++)
        {
            if (env->map->case_tab[x][y].type > 2)
            {
                SDL_Surface *surfaceItem;
                switch(env->map->case_tab[x][y].type) {
                    case 3:
                        surfaceItem = env->bomb_image->explo_left_img;
                        break;
                    case 4:
                        surfaceItem = env->bomb_image->explo_right_img;
                        break;
                    case 5:
                        surfaceItem = env->bomb_image->explo_center_img;
                        break;
                    case 6:
                        surfaceItem = env->bomb_image->explo_horizontal_img;
                        break;
                    case 7:
                        surfaceItem = env->bomb_image->explo_top_img;
                        break;
                    case 8:
                        surfaceItem = env->bomb_image->explo_bot_img;
                        break;
                    case 9:
                        surfaceItem = env->bomb_image->explo_vertical_img;
                        break;
                    case 10:
                        surfaceItem = env->bomb_image->bomb_img;
                        break;
                    case 22:
                        surfaceItem = env->des_case.tile_img;
                        break;
                }
                SDL_BlitSurface(surfaceItem, NULL, env->screen->ecran, &(env->map->case_tab[x][y].position));
            }
        }
    }
    //draw Heroes
    for(int i = 0; i < env->heroes->nb_elem; i++, hero_i = hero_i->next) {

        hero_i->hero->positionImg = hero_i->hero->position;
        hero_i->hero->positionImg.y -= 16;
        t_hero_img_elem *img = find_hero_img(hero_i->hero->numHero, hero_i->hero->orientation, env->heroes_img);
        if ( img != NULL && hero_i->hero->play)
            SDL_BlitSurface(img->hero->hero_img, &(env->sizeHero), env->screen->ecran, &(hero_i->hero->positionImg));
        // annimate player
        if (env->sizeHero.x + env->sizeHero.w >= env->heroes->first->hero->image->hero_img->w)
            env->sizeHero.x = 0;
        else
            env->sizeHero.x += env->sizeHero.w;
    }
    SDL_Flip(env->screen->ecran);
}
