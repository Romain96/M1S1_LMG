# M1S1 : Logiciels et matériels graphiques - Projet

## Description

Idée : utiliser les savoirs et compétences de base acquises en séances de TP pour développer un jeu vidéo ?

navigation (modèle de caméra)
chargement de contenu 3D
environnement (terrain, sky, eau)
apparence : lighting, texturing (rendu)
VFX : effets spéciaux (particle)
...
-----------------------------------------------------------------------------

A partir de ce qui a été fait dans les TP, créer :

- TP 1 : classe "Mesh" (VAO, VBO), class "MeshLoader"

- TP 2 : classe "ShaderProgram" (create program, add shaders [vertex, fragment, geometry, tesselation control and evaluation, compute], load shaders from file)

- TP 3 : classe "Camera" (view and projection matrix) [elle sera mise à jour à chaque interaction de souris/clavier]

- TP 4 : classe Light, class Material (Kd, Ks, shininess)

- TP 5 : classe Texture (ajouter un std::vector<Texture*> à votre classe Material)

A partir d'ici, vous pouvez créer une classe 3DModel contenant un Mesh et un Material.

- Autres: class "Terrain" (charger texture "heightmap" [carte de hauteur] => grille 2D au sol + "vertex shader" génère l'altitude "z" grâce à la texture)

-----------------------------------------------------------------------------

Pas sûr => Idées Pascal : BONUS : selon le niveau, chacun essaie d'ajouter une contribution sur un sujet spécifique ? Exemple :

végétation : un arbre complet à la SpeedTree (animé), ou herbe animé ?
eau : animation => vagues ?
character : perso 3D (keyframe ?, skeleton ?)
???

## Organisation

* programmation : C++
* bibliothèques : GLEW, GLUT (freeglut), GLM
* Auteur(s) : Romain PERRIN
