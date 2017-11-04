#ifndef __LIGHT_H__
#define __LIGHT_H__

/*
================================================================================
Classe          : Light
Auteur(s)       : Romain PERRIN
Date :          : 2017-11-03
Description     : contient les informations sur une source de lumi�re (position, couleur, type)
================================================================================
*/

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light
{
protected:
	// contient la position de la source de lumi�re
	glm::vec3 _lightPosition;
	// contient la couleur de la source de lumi�re
	glm::vec3 _lightColor;
	// TODO type
public:
	// constructeur vide
	Light();
	// constructeur avec param�tres
	Light(glm::vec3& lightPosition, glm::vec3& lightColor);
	// ajoute ou remplace la position de la source de lumi�re
	void setLightPosition(glm::vec3& lightPosition);
	// ajoute ou remplace la couleur de la source de lumi�re
	void setLightColor(glm::vec3& lightColor);
	// retourne la position de la source de lumi�re
	glm::vec3 getLightPosition();
	// retourne la couleur de la source de lumi�re
	glm::vec3 getLightColor();
};

#endif
