#ifndef __MATERIAL_H__
#define __MATERIAL_H__

/*
================================================================================
Classe          : Material
Auteur(s)       : Romain PERRIN
Date :          : 2017-11-03
Description     : contient les informations sur le mat�riau (coef diffus, coef sp�culaire, shininess)
================================================================================
*/

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Material
{
protected:
	// couleur diffuse du mat�riau
	glm::vec3 _kd;
	// couleur sp�culaire du mat�riau
	glm::vec3 _ks;
	// shininess
	float _shininess;
public:
	// constructeur vide
	Material();
	// constucteur param�tr�
	Material(glm::vec3& kd, glm::vec3& ks, float shininess);
	// ajoute ou remplace la couleur diffuse du mat�riau
	void setKd(glm::vec3& kd);
	// ajoute ou remplace la couleure sp�culaire du mat�riau
	void setKs(glm::vec3& ks);
	// ajoute ou remplace la shininess du mat�riau
	void setShininess(float shininess);
	// retourne la couleur diffuse du mat�riau
	glm::vec3 getKd();
	// retourne la couleur sp�culaire du mat�riau
	glm::vec3 getKs();
	// retourne la shininess du mat�riau
	float getShininess();
};

#endif
