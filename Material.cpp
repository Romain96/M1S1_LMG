/*
================================================================================
Classe          : Material
Auteur(s)       : Romain PERRIN
Date :          : 2017-11-03
Description     : contient les informations sur le matériau (coef diffus, coef spéculaire, shininess)
================================================================================
*/

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"

/*
Fonction        : Material (constructeur vide)
Argument(s)     : /
retour          : /
Commentaires    : /
*/
Material::Material() : _kd(0.f, 0.f, 0.f), _ks(0.f, 0.f, 0.f), _shininess(0.f)
{}

/*
Fonction        : Material (constructeur paramétré)
Argument(s)     : un vec3 contenant la kd, un vec3 contenant le ks et un float contenant la shininess
retour          : /
Commentaires    : /
*/
Material::Material(glm::vec3& kd, glm::vec3& ks, float shininess)
{
	this->_kd = kd;
	this->_ks = ks;
	this->_shininess = shininess;
}

/*
Fonction        : setKd
Argument(s)     : un vec3 contenant la nouvelle couleur diffuse du matériau
retour          : /
Commentaires    : /
*/
void Material::setKd(glm::vec3& kd)
{
	this->_kd = kd;
}

/*
Fonction        : setKs
Argument(s)     : un vec3 contenant la nouvelle couleur spéclaire du matériau
retour          : /
Commentaires    : /
*/
void Material::setKs(glm::vec3& ks)
{
	this->_ks = ks;
}

/*
Fonction        : setShininess
Argument(s)     : un float contenant le nouveau coefficient de shininess
retour          : /
Commentaires    : /
*/
void Material::setShininess(float shininess)
{
	this->_shininess = shininess;
}

/*
Fonction        : getKd
Argument(s)     : /
retour          : un vec3 contenant le couleur diffuse actuelle du matériau
Commentaires    : /
*/
glm::vec3 Material::getKd()
{
	return this->_kd;
}

/*
Fonction        : getKs
Argument(s)     : /
retour          : un vec3 contenant la couleur spéculaire actuelle du matériau
Commentaires    : /
*/
glm::vec3 Material::getKs()
{
	return this->_ks;
}

/*
Fonction        : getShininess
Argument(s)     : /
retour          : un float contenant le coefficient de shininess actuel du matériau
Commentaires    : /
*/
float Material::getShininess()
{
	return this->_shininess;
}