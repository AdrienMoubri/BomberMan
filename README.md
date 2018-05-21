# ETNA-bomberman

## Ce Projet utilise SDL 1.2.15
### Il vous faut installer les librairie suivantes :
* SDL1.2
* SDL_Text
* SDL_image.
----
###Liens SDL : 
* [SDL 1.2.15] (https://www.libsdl.org/download-1.2.php)
* [SDL Image 1.2] (https://www.libsdl.org/projects/SDL_image/release-1.2.html)
* [SDL TTF 2.0] (https://www.libsdl.org/projects/SDL_ttf/release-1.2.html)
----
## Ubuntu / Debian
### lancez les commandes suivantes :
* apt-get install libsdl-image1.2-dev
* apt-get install libsdl1.2-dev
* apt-get install libsdl-ttf2.0-dev
----
## MAC
### suivez les consignes suivantes
* [Installation SDL 1.2.15]
(https://openclassrooms.com/courses/apprenez-a-programmer-en-c/installation-de-la-sdl)
* [Installation SDL Image 1.2]
(https://openclassrooms.com/courses/apprenez-a-programmer-en-c/afficher-des-images)
* Attention bien prendre SDL_Image 1.2
* Même manip pour SDL TTF 1.2
----
## Windows
* Téléchargez : [SDL 1.2.15]
(https://www.libsdl.org/release/SDL-devel-1.2.15-mingw32.tar.gz)
* Téléchargez : [SDL Image 1.2]
(https://www.libsdl.org/projects/SDL_image/release/SDL_image-devel-1.2.12-VC.zip)
* Téléchargez : [SDL TTF] 
(https://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-devel-2.0.11-VC.zip)
* Ouvrez le fichier SDL-devel-1.2.15-mingw32.tar.gz et copier le dans un dossier facilement accessible
* Ouvrez les zip ouvrez des libraires SDL image et TTF puis dans le dossier include copier les fichier .h dans le dossier /SDL-1.2.15/include/SDL
* Ouvrez le dossier lib et copier tout le contenue dans le dossier /SDL-1.2.15/lib
* Définir la variable d'environnement 
SDLDIR avec le chemin des lib et des include de SDL 1.2.15