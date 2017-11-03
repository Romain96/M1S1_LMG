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

#include <vector>
#include <string>
#include "Mesh.h"

class MeshLoader
{
private:
	// méthodes privées
	static std::string _doubleSlash(std::string s);
	static std::string _replaceSlash(std::string s);
	static std::vector<std::string> _splitSpace(std::string s);
	static std::string _getDirectory(std::string s);
	float *_vectorToFloat(std::vector<float>& vec);
public:
	// méthode de lecture d'un fichier .obj et remplissant les buffers de mesh
	static bool read(const char *filename, Mesh& mesh);
};

#endif

