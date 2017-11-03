#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

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

#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

class ShaderProgram
{
protected:
        GLuint _shaderProgram;
        // shaders : valeurs de GL_SHADER_TYPE
        GLuint _vertexShader;                    // GL_VERTEX_SHADER
        GLuint _fragmentShader;                  // GL_FRAGMENT_SHADER
        GLuint _computeShader;                   // GL_COMPUTE_SHADER
        GLuint _tesselationControlShader;        // GL_TESS_CONTROL_SHADER
        GLuint _tesselationEvaluationShader;     // GL_TESS_EVALUATION_SHADER
        GLuint _geometryShader;                  // GL_GEOMETRY_SHADER
        // booléens indiquant qu'un shader a été ajouté
        bool _hasVertexShader;
        bool _hasFragmentShader;
        bool _hasComputeShader;
        bool _hasTesselationControlShader;
        bool _hasTesselationEvaluationShader;
        bool _hasGeometryShader;
private:
        // méthode intermédiaire de test de la compilation d'un shader
        bool __checkCompilationStatus(GLuint shader);
public:
        // constructeur
        ShaderProgram();
        // retourne la shaderProgram
        GLuint getShaderProgram();
		// crée le shaderProgram
		void createShaderProgram();
        // ajoute un shader (ou remplace le shader existant) depuis une chaine de caractères
        void addShaderFromString(GLenum shaderType, const char *shaderCode);
        // ajoute un shader (ou remplace la shader existant) depuis un fichier
        void addShaderFromFile(GLenum shaderType, const std::string& shaderFile);
        // compile tous les shaders renseignés
        void compileShaders();
        // attache tous les shaders renseignés au shaderProgram
        void attachShaders();
        // link le shaderProgram
        void linkProgram();
};

#endif
