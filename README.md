# Projet de LMG

## Description

Projet réalisé dans le cadre de l'UE "Logiciels et Matériels Graphiques".

Le projet final comporte une scène se composant :
* une skybox
* plusieurs cubemap notament pour les murs, le sol, le plafond et les "lampadaires"
* un modèle chargé à l'aide de la bibliothèque assimp
* une caméra permettant de se déplacer et de progresser dans la scène (mouvements avec les flèches directionnelles, déplacement caméra à la souris)
* plusieurs sources de lumières dont une source directionnelle (le soleil), 4 sources ponctuelle (les "lampadaires") et un spot (flashlight style FPS pointant dans la direction de la caméra pour simuler une lampe torche)
* des raccourcis clavier : W (en qwerty Z en azerty) pour activer ou désactiver le mode Wireframe et S pour afficher ou non la skybox

## Organisation

Auteurs : 
* BALZAN Juan
* PERRIN Romain

> Mention spéciale à [Learn OpenGL](https://learnopengl.com/) et [Open.gl](https://open.gl/) qui nous ont été d'une aide considérable lors du développement.

Programmation : C++

Bibliothèques : 
* glad
* GLFW
* SOIL (chargement d'images)
* glm (fonctions mathématiques)
* assimp (chargement de modèles au format .obj)