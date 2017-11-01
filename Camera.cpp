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

// constructeur avec matrices identités
Camera::Camera(): _viewMatrix(), _projectionMatrix()
{}

// définit une view matrix (ou remplace l'actuelle)
void Camera::defineViewMatrix(glm::vec3& eye, glm::vec3& center, glm::vec3& up)
{
	this->_eye = eye;
	this->_center = center;
	this->_up = up;
	this->_viewMatrix = glm::lookAt(eye, center, up);
}

// définit une projection matrix (ou remplace l'actuelle)
void Camera::defineProjectionMatrix(float fovY, float aspect, float zNear, float zFar)
{
	this->_fovY = fovY;
	this->_aspect = aspect;
	this->_zNear = zNear;
	this->_zFar = zFar;
	this->_projectionMatrix = glm::perspective(fovY, aspect, zNear, zFar);
}

// retourne la view matrix
glm::mat4 Camera::getViewMatrix()
{
	return this->_viewMatrix;
}

// retourne la projection matrix
glm::mat4 Camera::getProjectionMatrix()
{
	return this->_projectionMatrix;
}