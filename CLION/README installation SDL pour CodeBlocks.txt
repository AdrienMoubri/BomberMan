T�l�charger SDL : Windows : Mingw : https://www.libsdl.org/release/SDL-devel-1.2.15-mingw32.tar.gz

extraire le dossier SDL dans le dossier de CodeBlocks C:/ProgrammeFiles/CodeBlocks/lib (si le dossier lib n'existe pas cr�er le)

Maintenant allez dans le dossier C:/ProgrammeFiles/CodeBlocks/SDL/includes/SDL copiez tout les fichiers .h

ouvrez CodeBlocks lancer un nouveau projet. selectionner SDL comme type de projet. Une nouvelle fen�tre vas s'ouvrir. cherchez le dossier o� est installer SDL (C:/ProgrammeFiles/CodeBlocks/lib/SDL1.2.5 chez moi)

une nouvelle fen�tre vas s'ouvrir fermez l�.


Autre systeme d'exploitation : suivre la tuto 
https://openclassrooms.com/courses/apprenez-a-programmer-en-c/installation-de-la-sdl




k
Installation

Dans ce .zip, vous trouverez :

SDL_image.h: le seul header dont a besoin la biblioth�queSDL_Image. Placez-le dansC:\Program Files\CodeBlocks\SDL-1.2.13\include, c'est-�-dire � c�t� des autres headers de la SDL ;
SDL_image.lib: copiez dansC:\Program Files\CodeBlocks\SDL-1.2.13\lib. Oui, je sais, je vous ai dit que normalement les.lib�taient des fichiers r�serv�s � Visual, mais ici exceptionnellement le.libfonctionnera m�me avec le compilateurmingw;
plusieurs DLL : placez-les toutes dans le dossier de votre projet (� c�t� deSDL.dll, donc).
Ensuite, vous devez modifier les options de votre projet pour � linker � avec le fichierSDL_image.lib.

Si vous �tes sous Code::Blocks par exemple, allez dans le menuProjects / Build options. Dans l'ongletLinker, cliquez sur le boutonAddet indiquez o� se trouve le fichierSDL_image.lib(fig. suivante).

S�lection de SDL_image.lib
Si on vous demande Keep as a relative path?, r�pondez ce que vous voulez, �a ne changera rien dans l'imm�diat. Je recommande de r�pondre par la n�gative, personnellement.

Ensuite, vous n'avez plus qu'� refaire la m�me chose pour SDL_TTF.lib