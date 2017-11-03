/*
================================================================================
Classe          : MeshLoader
Auteur(s)       : Romain PERRIN
Date :          : 2017-10-31
Description     : permet de charger une mesh en lisant un fichier .obj
================================================================================
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "MeshLoader.h"

/*
Fonction        : _doubleSlash
Argument(s)     : une chaine de caractères
retour          : la même chaine de caractères dont les "//" ont été remplacés par des "/1/"
Commentaires    : /
*/
std::string MeshLoader::_doubleSlash(std::string s)
{
	std::string noDoubleSlash = "";

	// parcours de la chaine
	for (unsigned int i = 0; i < s.size(); i++)
	{
		// si on trouve deux '/' successifs on les remplace par "/1/"
		if (i < s.size() - 1 && s[i] == '/' && s[i + 1] == '/')
		{
			noDoubleSlash += "/1/";
			i++;
		}
		else
		{
			noDoubleSlash += s[i];
		}
	}
	return noDoubleSlash;
}

/*
Fonction        : _replaceSlash
Argument(s)     : une chaine de caractères
retour          : la même chaine de caractères dont les "/" on été remplacés par " "
Commentaires    : /
*/
std::string MeshLoader::_replaceSlash(std::string s)
{
	std::string noSlash = "";

	// parcours de la chaine
	for (unsigned int i = 0; i < s.size(); i++)
	{
		// chaque '/' est remplacé par ' '
		if (s[i] == '/')
		{
			noSlash += " ";
		}
		else
		{
			noSlash += s[i];
		}
	}
	return noSlash;
}

/*
Fonction        : _splitSpace
Argument(s)     : une chaine de caractères
retour          : un vecteur contenant x chaines de caractères séparées avec le délimiteur " "
Commentaires    : /
*/
std::vector<std::string> MeshLoader::_splitSpace(std::string s)
{
	std::vector<std::string> list;
	std::string splitedString;

	// parcours de la chaine
	for (unsigned int i = 0; i < s.size(); i++)
	{
		// si on trouve un espace on ajoute la sous-chaine courante à la liste
		if (s[i] == ' ' || i == s.size() - 1)
		{
			if (i == s.size() - 1)
			{
				splitedString += s[i];
			}
			list.push_back(splitedString);
		}
		else
		{
			splitedString += s[i];
		}
	}
	return list;
}

/*
Fonction        : _getDirectory
Argument(s)     : une chaine de caractères
retour          : une chaine de caractères
Commentaires    : /
*/
std::string MeshLoader::_getDirectory(std::string s)
{
	std::string s1 = "", s2 = "";
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == '/' || s[i] == '\\')
		{
			s1 += s2 + "/";
			s2 = "";
		}
		else
		{
			s2 += s[i];
		}
	}
	return s1;
}

/*
Fonction        : _vectorToFloat
Argument(s)     : un vecteur de float
retour          : un float*
Commentaires    : /
*/
float *MeshLoader::_vectorToFloat(std::vector<float>& vec)
{
	float *t = NULL;
	t = (float *)malloc(vec.size() * sizeof(float));
	// cas particulier : erreur ou vecteur vide
	if (t == NULL || vec.empty())
	{
		float *t1 = (float *)malloc(sizeof(float) * 3);
		for (int i = 0; i < 3; i++)
		{
			t1[i] = 0.;
		}
		return t1;
	}
	// cas général
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		t[i] = vec[i];
	}
	return t;
}

/*
Fonction        : read
Argument(s)     : le fichier .obj à lire et la Mesh a remplir avec les informations du fichier
retour          : vrai si OK, faux si erreur
Commentaires    : structure d'un fichier obj :
		 # commentaires
		 objname -> nom de l'objet
		 v float float float -> vertices (sommets) 
		 vt float float -> coordonnées de texture
		 vn float float float -> normales
		 f int/int/int int/int/int int/int/int -> faces triangulaires(chaque int est le numéro d'un sommet v)
*/
bool MeshLoader::read(const char *filename, Mesh& mesh)
{
	// variables temporaires
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> texture;
	std::vector<glm::vec3> normals;
	std::vector<int> indexVertices;
	std::vector<int> indexTexture;
	std::vector<int> indexNormals;

	// ouverture du fichier
	std::ifstream file(filename, std::ios::in);
	std::string objectName = "";

	if (file)
	{
		// lecture ligne par ligne
		for (std::string line; getline(file, line); )
		{
			// traitement des sommets identifiées par v float/float/float
			if (line[0] == 'v' && line[1] == ' ')
			{
				char x[255], y[255], z[255];
				sscanf(line.c_str(), "v %s %s %s", x, y, z);
				vertices.push_back(glm::vec3(strtod(x, NULL), strtod(y, NULL), strtod(z, NULL)));
			}
			// traitement des textures identifiées par vt float/float
			else if (line[0] == 'v' && line[1] == 't')
			{
				char x[255], y[255];
				sscanf(line.c_str(), "vt %s %s", x, y);
				texture.push_back(glm::vec3(strtod(x, NULL), strtod(y, NULL), 0.f));
			}
			// traitement des normales identifiées par vn float/float/float
			else if (line[0] == 'v' && line[1] == 'n')
			{
				char x[255], y[255], z[255];
				sscanf(line.c_str(), "vn %s %s %s", x, y, z);
				normals.push_back(glm::vec3(strtod(x, NULL), strtod(y, NULL), strtod(z, NULL)));
			}
			// traitement des faces
			else if (line[0] == 'f')
			{
				// supprime les // eventuels
				line = _doubleSlash(line);
				// ex : f 1/2/3 4/5/6 7/8/9 devient f 1 2 3 4 5 6 7 8 9
				line = _replaceSlash(line);
				// éclatement de la chaine
				std::vector<std::string> list = _splitSpace(line);
				// taille des données
				int dataSize = (int)list.size() / 3;

				for (int i = 0; i < (dataSize == 3 ? 3 : 4); i++)
				{
					indexVertices.push_back(strtol(list[i*3].c_str(), NULL, 10)-1);
					indexTexture.push_back(strtol(list[i * 3 + 1].c_str(), NULL, 10) - 1);
					indexNormals.push_back(strtol(list[i * 3 + 2].c_str(), NULL, 10) - 1);
				}
				// cas particulier : si n'y a que 3 sommets on duplique le dernier afin de créer un quad ayant l'apparence d'un triangle
				if (dataSize == 3)
				{
					indexVertices.push_back(strtol(list[0].c_str(), NULL, 10) - 1);
					indexTexture.push_back(strtol(list[1].c_str(), NULL, 10) - 1);
					indexNormals.push_back(strtol(list[2].c_str(), NULL, 10) - 1);
				}
				// TODO : traitement des matériaux
				// traitement de mtllib (on peut tester si line[0]==m puisque mtllib est le seul mot clef commençant par m
				else if (line[0] == 'm')
				{
					// TODO avec les matériaux
				}
				// traitement de usemtl
				else if (line[0] == 'u')
				{
					objectName = line.substr(7);
				}
			}
		}
		// fermeture du fichier
		file.close();

		// application des indices des sommets pour avoir toutes les faces
		std::vector<float> tv(0), tc(0), tn(0), tt(0);
		for (unsigned int i = 0; i < indexVertices.size(); i++)
		{
			if (indexVertices[i] < vertices.size())
			{
				// sommets
				tv.push_back(vertices[indexVertices[i]].x);
				tv.push_back(vertices[indexVertices[i]].y);
				tv.push_back(vertices[indexVertices[i]].z);
				// couleur
				//tc.push_back(colors[i].x);
				//tc.push_back(colors[i].y);
				//tc.push_back(colors[i].z);
				//tc.push_back(colors[i].a);
			}
		}

		for (unsigned int i = 0; i < indexNormals.size(); i++)
		{
			if (indexNormals[i] < normals.size())
			{
				tn.push_back(normals[indexNormals[i]].x);
				tn.push_back(normals[indexNormals[i]].y);
				tn.push_back(normals[indexNormals[i]].z);
			}
		}

		for (unsigned int i = 0; i < indexTexture.size(); i++)
		{
			if (indexTexture[i] < texture.size())
			{
				tt.push_back(texture[indexTexture[i]].x);
				tt.push_back(texture[indexTexture[i]].x);
			}
		}

		// remplir la mesh
		//mesh.addPositionBuffer(vertices);
	}
	else
	{
		fprintf(stderr, "MeshLoad::read : error while reading the file\n");
		return false;
	}
}