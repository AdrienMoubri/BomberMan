#include "bfm.h"

//
// Created by AMO on 04/12/2017.
//

/*
 * détection des collisions entre objet
 * TODO rajouter la collision entre les personnages
 */

int collisionObject(SDL_Rect box, SDL_Rect wall)
{
    int leftW, leftB;
    int rightW, rightB;
    int topW, topB;
    int bottomW, bottomB;

    leftB = box.x;
    rightB = box.x + box.w;
    topB = box.y;
    bottomB = box.y + box.h;

    leftW = wall.x;
    rightW = wall.x + wall.w;
    topW = wall.y;
    bottomW = wall.y + wall.h;

    if( bottomB <= topW )
        return 0;

    if( topB >= bottomW )
        return 0;

    if( rightB <= leftW )
        return 0;

    if( leftB >= rightW )
        return 0;

    return 1;
}

/*
 * détection des collisions entre le hero et les murs
 * TODO rajouter la collision entre les personnages
 */
int collisionCase(t_hero *hero, t_case map[WIDTH_MAP][HEIGHT_MAP])
{
    int posX = hero->positionCase->x;
    int posY = hero->positionCase->y;
    switch(hero->direction) {
        case 0:
            posY += 1;
            break;
        case 1:
            posX -= 1;
            break;
        case 2:
            posX += 1;
            break;
        case 3:
            posY -= 1;
            break;
    }
    if (map[posX][posY].type == 0)
        hero->positionCase = &(map[posX][posY]);
}
/*
 * une fois que le hero est sur la case suivante
 */
int finishedMovement(t_hero *hero)
{
    if (hero->position.x == hero->positionCase->position.x && hero->position.y == hero->positionCase->position.y)
        return 1;
    return 0;
}

/*
 * définit la direction de tout les heros
 */
void setDirections(t_env *env)
{
    t_hero_elem *hero_it = env->heroes->first;
    for(int i = 0; i < env->heroes->nb_elem; i++, hero_it = hero_it->next)
    {
        t_hero_img_elem *hero_img_it = env->heroes_img->first;
        for(int y = 0; y < env->heroes_img->nb_elem; y++, hero_img_it = hero_img_it->next)
        {
            if (hero_it->hero->direction == hero_img_it->hero->orientation && hero_it->hero->numHero == hero_img_it->hero->numHero)
                hero_it->hero->image = hero_img_it->hero;
        }
    }
}

/*
 * déplace le héro dans sa direction
 */
void move_hero(t_hero* hero)
{
    int deplacementX = 0;
    int deplacementY = 0;

    switch(hero->direction) {
        case 0:
            deplacementY += SPEED_HERO;
            break;
        case 1:
            deplacementX -= SPEED_HERO;
            break;
        case 2:
            deplacementX += SPEED_HERO;
            break;
        case 3:
            deplacementY -= SPEED_HERO;
            break;
    }
    hero->position.x += deplacementX;
    hero->position.y += deplacementY;
}