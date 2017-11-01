#ifndef __CAMERA_H__
#define __CAMERA_H__

/*
================================================================================
Classe          : Camera
Auteur(s)       : Romain PERRIN
Date :          : 2017-11-01
Description     : gestion de la camera (view matrix et projection matrix)
================================================================================
*/

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
protected:
	// matrice view
	glm::mat4 _viewMatrix;
	// paramètres utilisateurs de la matrice view
	glm::vec3 _eye;
	glm::vec3 _center;
	glm::vec3 _up;
	// matrice projection
	glm::mat4 _projectionMatrix;
	// paramètres utilisateur de la matrice projection
	float _fovY;
	float _aspect;
	float _zNear;
	float _zFar;
public:
	// constructeur
	Camera();
	// définition d'une view matrix
	void defineViewMatrix(glm::vec3& eye, glm::vec3& center, glm::vec3& up);
	// définition d'une projection matrix
	void defineProjectionMatrix(float fovY, float aspect, float zNear, float zFar);
	// retourne la view matrix
	glm::mat4 getViewMatrix();
	// retourne la projection matrix
	glm::mat4 getProjectionMatrix();
};

#endif