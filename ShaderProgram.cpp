/*
================================================================================
Classe          : ShaderProgram
Auteur(s)       : Romain PERRIN
Date :          : 2017-10-29
Description     : gère la création de shaderProgram, le chargement de shaders
                 depuis un fichier ou depuis une chaine de caractères, l'ajout
                 des shaders au shaderProgram, le linkage et la compilation
================================================================================
*/

#include <cstdlib>
#include <cstdio>
#include <GL/gl.h>
#include "ShaderProgram.h"

/*
Fonction        : ShaderProgram (constructeur)
Argument(s)     : /
retour          : /
Commentaires    : instancie un ShaderProgram sans shader
*/
ShaderProgram::ShaderProgram()
{
        this->shaderProgram = glCreateProgram();
        this->hasVertexShader = false;
        this->hasFragmentShader = false;
        this->hasComputeShader = false;
        this->hasTesselationControlShader = false;
        this->hasTesselationEvaluationShader = false;
        this->hasGeometryShader = false;
}

/*
Fonction        : getShaderProgram
Argument(s)     : /
retour          : le ShaderProgram
Commentaires    : /
*/
GLuint ShaderProgram::getShaderProgram()
{
        return this->shaderProgram;
}

/*
Fonction        : addShaderFromString
Argument(s)     : un type de shader (GLenum) et une chaine de caractères (code du shader)
retour          : /
Commentaires    : crée et ajoute le shader
*/
void ShaderProgram::addShaderFromString(GLenum shaderType, char *shader)
{
        // doc : GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
        switch (shaderType)
        {
                case GL_VERTEX_SHADER :
                        this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
                        glShaderSource(this->vertexShader, 1, shader, nullptr);
                        this->hasVertexShader = true;
                        break;

                case GL_FRAGMENT_SHADER :
                        this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                        glShaderSource(this->fragmentShader, 1, shader, nullptr);
                        this->hasFragmentShader = true;
                        break;

                case GL_TESS_CONTROL_SHADER :
                        this-> = glCreateShader(GL_TESS_CONTROL_SHADER);
                        glShaderSource(this->tesselationControlShader, 1, shader, nullptr);
                        this->hasTesselationControlShader = true;
                        break;

                case GL_TESS_EVALUATION_SHADER :
                        this-> = glCreateShader(GL_TESS_EVALUATION_SHADER);
                        glShaderSource(this->tesselationEvaluationShader, 1, shader, nullptr);
                        this->hasTesselationEvaluationShader = true;
                        break;

                case GL_GEOMETRY_SHADER :
                        this-> = glCreateShader(GL_GEOMETRY_SHADER);
                        glShaderSource(this->geometryShader, 1, shader, nullptr);
                        this->hasGeometryShader = true;
                        break;

                case GL_COMPUTE_SHADER :
                        this-> = glCreateShader(GL_COMPUTE_SHADER);
                        glShaderSource(this->computeShader, 1, shader, nullptr);
                        this->hasComputeShader = true;
                        break;

                default :
                        fprintf(stderr, "addShaderFromString : shaderType invalid !\n");
                        exit(1);
                        break;
        }
}

/*
Fonction        : addShaderFromFile
Argument(s)     : un type de shader (GLenum) et une chaine de caractères (nom du fichier à lire)
retour          : /
Commentaires    : /
*/

/*
Fonction        :
Argument(s)     :
retour          :
Commentaires    :
*/
