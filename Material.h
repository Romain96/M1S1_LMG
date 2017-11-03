#ifndef __MATERIAL_H__
#define __MATERIAL_H__

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

class Material
{
protected:
	// couleur diffuse du matériau
	glm::vec3 _kd;
	// couleur spéculaire du matériau
	glm::vec3 _ks;
	// shininess
	float _shininess;
public:
	// constructeur vide
	Material();
	// constucteur paramétré
	Material(glm::vec3& kd, glm::vec3& ks, float shininess);
	// ajoute ou remplace la couleur diffuse du matériau
	void setKd(glm::vec3& kd);
	// ajoute ou remplace la couleure spéculaire du matériau
	void setKs(glm::vec3& ks);
	// ajoute ou remplace la shininess du matériau
	void setShininess(float shininess);
	// retourne la couleur diffuse du matériau
	glm::vec3 getKd();
	// retourne la couleur spéculaire du matériau
	glm::vec3 getKs();
	// retourne la shininess du matériau
	float getShininess();
};

#endif
