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

#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include <GL/gl.h>

class ShaderProgram
{
protected:
        GLuint shaderProgram;
        // shaders : valeurs de GL_SHADER_TYPE
        GLuint vertexShader;            // GL_VERTEX_SHADER
        GLuint fragmentShader;          // GL_FRAGMENT_SHADER
        GLuint computeShader;           // GL_COMPUTE_SHADER
        GLuint tesselationShader;       // GL_TESS_CONTROL_SHADER
        GLuint tesselationEvalShader;   // GL_TESS_EVALUATION_SHADER
        GLuint geometryShader;          // GL_GEOMETRY_SHADER
        // booléens indiquant qu'un shader a été ajouté
        bool hasVertexShader;
        bool hasFragmentShader;
        bool hasComputeShader;
        bool hasTesselationShader;
        bool hasTesselationEvalShader;
        bool hasGeometryShader;
public:
        // constructeur
        ShaderProgram();
        // retourne la shaderProgram
        GLuint getShaderProgram();
        // ajoute un shader (ou remplace le shader existant) depuis une chaine de caractères
        void addShaderFromString(GLenum shaderType, char *shader);
        // ajoute un shader (ou remplace la shader existant) depuis un fichier
        void addShaderFromFile(GLenum shaderType, char *shader);
        // supprime un shader (s'il existe)
        void removeShader(GLenum shaderType);
        // compile tous les shaders renseignés
        void compileShaders();
        // attache tous les shaders renseignés au shaderProgram
        void attachShaders();
        // link le shaderProgram
        void linkShaders();
};

#endif
