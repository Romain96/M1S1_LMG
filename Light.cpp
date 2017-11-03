/*
================================================================================
Classe          : Light
Auteur(s)       : Romain PERRIN
Date :          : 2017-11-03
Description     : contient les informations sur une source de lumière (position, couleur, type)
================================================================================
*/

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Light.h"

/*
Fonction        : Light (constructeur vide)
Argument(s)     : /
retour          : /
Commentaires    : par défaut la source est à l'origine et de couleur blanche
*/
Light::Light() : _lightPosition(0.f, 0.f, 0.f), _lightColor(1.f, 1.f, 1.f)
{}

/*
Fonction        : Light (constructeur avec paramètres)
Argument(s)     : un vec3 contenant la position de la source de lumière et un autre contenant la couleur
retour          : /
Commentaires    : TODO ajouter le type de source
*/
Light::Light(glm::vec3& lightPosition, glm::vec3& lightColor)
{
	this->_lightPosition = lightPosition;
	this->_lightColor = lightColor;
}

/*
Fonction        : addLightPosition
Argument(s)     : un vec3 contenant la nouvelle position de la source de lumière
retour          : /
Commentaires    : /
*/
void Light::addLightPosition(glm::vec3& lightPosition)
{
	this->_lightPosition = lightPosition;
}

/*
Fonction        : addLightColor
Argument(s)     : un vec3 contenant la nouvelle couleur de la source de lumière
retour          : /
Commentaires    : /
*/
void Light::addLightColor(glm::vec3& lightColor)
{
	this->_lightColor = lightColor;
}

/*
Fonction        : getLightPosition
Argument(s)     : /
retour          : un vec3 contenant la position actuelle de la source de lumière
Commentaires    : /
*/
glm::vec3 Light::getLightPosition()
{
	return this->_lightPosition;
}

/*
Fonction        : getLightColor
Argument(s)     : /
retour          : un vec3 contenant la couleur de la source de lumière
Commentaires    : /
*/
glm::vec3 Light::getLightColor()
{
	return this->_lightColor;
}