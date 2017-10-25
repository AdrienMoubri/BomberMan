Télécharger SDL : Windows : Mingw : https://www.libsdl.org/release/SDL-devel-1.2.15-mingw32.tar.gz

extraire le dossier SDL dans le dossier de CodeBlocks C:/ProgrammeFiles/CodeBlocks/lib (si le dossier lib n'existe pas créer le)

Maintenant allez dans le dossier C:/ProgrammeFiles/CodeBlocks/SDL/includes/SDL copiez tout les fichiers .h

ouvrez CodeBlocks lancer un nouveau projet. selectionner SDL comme type de projet. Une nouvelle fenètre vas s'ouvrir. cherchez le dossier où est installer SDL (C:/ProgrammeFiles/CodeBlocks/lib/SDL1.2.5 chez moi)

une nouvelle fenètre vas s'ouvrir fermez là.


Autre systeme d'exploitation : suivre la tuto 
https://openclassrooms.com/courses/apprenez-a-programmer-en-c/installation-de-la-sdl




k
Installation

Dans ce .zip, vous trouverez :

SDL_image.h: le seul header dont a besoin la bibliothèqueSDL_Image. Placez-le dansC:\Program Files\CodeBlocks\SDL-1.2.13\include, c'est-à-dire à côté des autres headers de la SDL ;
SDL_image.lib: copiez dansC:\Program Files\CodeBlocks\SDL-1.2.13\lib. Oui, je sais, je vous ai dit que normalement les.libétaient des fichiers réservés à Visual, mais ici exceptionnellement le.libfonctionnera même avec le compilateurmingw;
plusieurs DLL : placez-les toutes dans le dossier de votre projet (à côté deSDL.dll, donc).
Ensuite, vous devez modifier les options de votre projet pour « linker » avec le fichierSDL_image.lib.

Si vous êtes sous Code::Blocks par exemple, allez dans le menuProjects / Build options. Dans l'ongletLinker, cliquez sur le boutonAddet indiquez où se trouve le fichierSDL_image.lib(fig. suivante).

Sélection de SDL_image.lib
Si on vous demande Keep as a relative path?, répondez ce que vous voulez, ça ne changera rien dans l'immédiat. Je recommande de répondre par la négative, personnellement.

Ensuite, vous n'avez plus qu'à refaire la même chose pour SDL_TTF.lib