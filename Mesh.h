#ifndef __MESH_H__
#define __MESH_H__

/*
================================================================================
Classe          : Mesh
Auteur(s)       : Romain PERRIN
Date :          : 2017-10-31
Description     : structure permettant de stocker un maillage et son apparence
================================================================================
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <vector>
#include <vector>

class Mesh
{
protected:
	// le nom du Mesh
	std::string name;
	// un VAO qui sert à référencer et encapsuler une liste de buffers génériques VBO
	GLuint _vertexArray;
	// VBO contenant les positions
	GLuint _positionBuffer;
	// VBO contenant les normales
	GLuint _normalBuffer;
	// VBO contenant les index
	GLuint _indexBuffer;
	// VBO contenant les textures
	GLuint _textureBuffer;
public:
	// constructeur
	Mesh(std::string name);
	// ajouter un buffer de positions
	void setPositionBuffer(const std::vector<float>& positionBuffer);
	// ajouter un buffer de normales
	void setNormalBuffer(const std::vector<float>& normalBuffer);
	// ajouter un buffer d'index
	void setIndexBuffer(const std::vector<float>& indexBuffer);
};

#endif 
