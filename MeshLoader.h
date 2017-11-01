#ifndef __MESHLOADER_H__
#define __MESHLOADER_H__

/*
================================================================================
Classe          : MeshLoader
Auteur(s)       : Romain PERRIN
Date :          : 2017-10-31
Description     : permet de lire un fichier .obj et de remplir les VBO (Mesh)
================================================================================
*/

#include "Mesh.h"

class MeshLoader
{
public:
	// méthode de lecture d'un fichier .obj et remplissant les buffers de mesh
	static int read(const char *filename, Mesh& mesh);
};

#endif

