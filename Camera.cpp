/*
================================================================================
Classe          : Camera
Auteur(s)       : Romain PERRIN
Date :          : 2017-11-01
Description     : gestion de la camera (view matrix et projection matrix)
================================================================================
*/

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

/*
Fonction        : Camera (constructeur vide)
Argument(s)     : /
retour          : /
Commentaires    : /
*/
Camera::Camera(): _viewMatrix(), _projectionMatrix()
{}

/*
Fonction        : setViewMatrix
Argument(s)     : 3 vec3 : eye, center et view (paramètres de glm::lookAt)
retour          : /
Commentaires    : /
*/
void Camera::setViewMatrix(glm::vec3& eye, glm::vec3& center, glm::vec3& up)
{
	this->_eye = eye;
	this->_center = center;
	this->_up = up;
	this->_viewMatrix = glm::lookAt(eye, center, up);
}

/*
Fonction        : setProjectionMatrix
Argument(s)     : 4 float : fovY, aspect, zNear et zFar (paramètres de glm::perpective)
retour          : un vec3 contenant la couleur spéculaire actuelle du matériau
Commentaires    : /
*/
void Camera::setProjectionMatrix(float fovY, float aspect, float zNear, float zFar)
{
	this->_fovY = fovY;
	this->_aspect = aspect;
	this->_zNear = zNear;
	this->_zFar = zFar;
	this->_projectionMatrix = glm::perspective(fovY, aspect, zNear, zFar);
}

/*
Fonction        : getViewMatrix
Argument(s)     : /
retour          : une mat4 contenant la view matrix actuelle
Commentaires    : /
*/
glm::mat4 Camera::getViewMatrix()
{
	return this->_viewMatrix;
}

/*
Fonction        : getProjectionMatrix
Argument(s)     : /
retour          : une mat4 contenant la projection matrix
Commentaires    : /
*/
glm::mat4 Camera::getProjectionMatrix()
{
	return this->_projectionMatrix;
}