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
#include <string>
#include <iostream>
#include <fstream>
// Graphics
// - GLEW (always before "gl.h")
#include <GL/glew.h>
// - GL
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
// - GLUT
#include <GL/glut.h>
#include "ShaderProgram.h"

/*
Fonction        : ShaderProgram (constructeur)
Argument(s)     : /
retour          : /
Commentaires    : instancie un ShaderProgram sans shader
*/
ShaderProgram::ShaderProgram()
{
        // pas de shader
        this->_hasVertexShader = false;
        this->_hasFragmentShader = false;
        this->_hasComputeShader = false;
        this->_hasTesselationControlShader = false;
        this->_hasTesselationEvaluationShader = false;
        this->_hasGeometryShader = false;
	// idem pour les identifiants de shaders
	this->_vertexShader = 0;
	this->_fragmentShader = 0;
	this->_computeShader = 0;
	this->_tesselationControlShader = 0;
	this->_hasTesselationEvaluationShader = 0;
	this->_geometryShader = 0;
}

/*
Fonction        : getShaderProgram
Argument(s)     : /
retour          : le ShaderProgram
Commentaires    : /
*/
GLuint ShaderProgram::getShaderProgram()
{
        return this->_shaderProgram;
}

/*
Fonction        : createShaderProgram
Argument(s)     : /
retour          : /
Commentaires    : /
*/
void ShaderProgram::createShaderProgram()
{
	this->_shaderProgram = glCreateProgram();
}

/*
Fonction        : addShaderFromString
Argument(s)     : un type de shader (GLenum) et une chaine de caractères (code du shader)
retour          : /
Commentaires    : crée et ajoute le shader
*/
void ShaderProgram::addShaderFromString(GLenum shaderType, const char *shaderCode)
{
        // doc : GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
        switch (shaderType)
        {
                case GL_VERTEX_SHADER :
			this->_vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(this->_vertexShader, 1, &shaderCode, nullptr);
			this->_hasVertexShader = true;
			break;

                case GL_FRAGMENT_SHADER :
                        this->_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                        glShaderSource(this->_fragmentShader, 1, &shaderCode, nullptr);
                        this->_hasFragmentShader = true;
                        break;

                case GL_TESS_CONTROL_SHADER :
                        this->_hasTesselationControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
                        glShaderSource(this->_tesselationControlShader, 1, &shaderCode, nullptr);
                        this->_hasTesselationControlShader = true;
                        break;

                case GL_TESS_EVALUATION_SHADER :
                        this->_tesselationEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
                        glShaderSource(this->_tesselationEvaluationShader, 1, &shaderCode, nullptr);
                        this->_hasTesselationEvaluationShader = true;
                        break;

                case GL_GEOMETRY_SHADER :
                        this->_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
                        glShaderSource(this->_geometryShader, 1, &shaderCode, nullptr);
                        this->_hasGeometryShader = true;
                        break;

                case GL_COMPUTE_SHADER :
                        this->_computeShader = glCreateShader(GL_COMPUTE_SHADER);
                        glShaderSource(this->_computeShader, 1, &shaderCode, nullptr);
                        this->_hasComputeShader = true;
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
void ShaderProgram::addShaderFromFile(GLenum shaderType, const std::string& shaderFile)
{
        std::ifstream file(shaderFile.c_str(), std::ios::in);
        std::string shaderCode;     // contiendra le code du shader

        if (file)
        {
                // initialiser une chaine de caractères pour contenir le contenu du fichier
                file.seekg(0, std::ios::end);
		shaderCode.resize(file.tellg());
                file.seekg(0, std::ios::beg);
                // lecture du fichier
                file.read(&shaderCode[0], shaderCode.size());
                // fermeture du fichier
                file.close();
        }

        // ajout du shader en utilisant la méthode précédente
        addShaderFromString(shaderType, shaderCode.c_str());

}

/*
Fonction        : __checkCompilationStatus
Argument(s)     : le type de shader
retour          : vrai si la compilation est OK faux sinon
Commentaires    : méthode intermédiaire appelée pour chaque shader par compileShaders()
*/
bool ShaderProgram::__checkCompilationStatus(GLuint shader)
{
        GLint compileStatus;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
        // si erreur de compilation
        if (compileStatus == GL_FALSE)
        {
                GLint logInfoLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logInfoLength);
                // si le log d'erreur est non vide
                if (logInfoLength > 0)
                {
                        // affichage des erreurs de compilation
                        GLchar *infoLog = new GLchar[logInfoLength];
                        GLsizei length = 0;
                        glGetShaderInfoLog(shader, logInfoLength, &length, infoLog);
                        // affichage du log
                        std::cout << infoLog << std::endl;

                        delete[] infoLog;
                }
                // il y avait des erreurs
                return false;
        }
        // pas d'erreur
        return true;
}

/*
Fonction        : compileShaders
Argument(s)     : /
retour          : /
Commentaires    : compile tous les shaders renseignés avec addShaderFromString et addShaderFromFile
*/
void ShaderProgram::compileShaders()
{
        bool compileVertexShader = true;
        bool compileFragmentShader = true;
        bool compileTesselationControlShader = true;
        bool compileTesselationEvaluationShader = true;
        bool compileGeometryShader = true;
        bool compileComputeShader = true;

        if (this->_hasVertexShader)
        {
                glCompileShader(this->_vertexShader);
                compileVertexShader = __checkCompilationStatus(this->_vertexShader);
        }
        if (this->_hasFragmentShader)
        {
                glCompileShader(this->_fragmentShader);
                compileFragmentShader = __checkCompilationStatus(this->_fragmentShader);
        }
        if (this->_hasTesselationControlShader)
        {
                glCompileShader(this->_tesselationControlShader);
                compileTesselationControlShader = __checkCompilationStatus(this->_tesselationControlShader);
        }
        if (this->_hasTesselationEvaluationShader)
        {
                glCompileShader(this->_tesselationEvaluationShader);
                compileTesselationEvaluationShader = __checkCompilationStatus(this->_tesselationEvaluationShader);
        }
        if (this->_hasGeometryShader)
        {
                glCompileShader(this->_geometryShader);
                compileGeometryShader = __checkCompilationStatus(this->_geometryShader);
        }
        if (this->_hasComputeShader)
        {
                glCompileShader(this->_computeShader);
                compileComputeShader = __checkCompilationStatus(this->_computeShader);
        }

        // si erreur(s) de compilation -> arrêt
        if ( !(compileVertexShader && compileFragmentShader && compileTesselationControlShader &&
                compileTesselationEvaluationShader && compileGeometryShader && compileComputeShader) )
                {
                        fprintf(stderr, "compileShaders : error while compiling shaders !\n");
                        exit(1);
                }
}

/*
Fonction        : attachShaders
Argument(s)     : /
retour          : /
Commentaires    : attache tous les shaders renseignés au shaderProgram
*/
void ShaderProgram::attachShaders()
{
        if (this->_hasVertexShader)
        {
                glAttachShader(this->_shaderProgram, this->_vertexShader);
        }
        if (this->_hasFragmentShader)
        {
                glAttachShader(this->_shaderProgram, this->_fragmentShader);
        }
        if (this->_hasTesselationControlShader)
        {
                glAttachShader(this->_shaderProgram, this->_tesselationControlShader);
        }
        if (this->_hasTesselationEvaluationShader)
        {
                glAttachShader(this->_shaderProgram, this->_tesselationEvaluationShader);
        }
        if (this->_hasGeometryShader)
        {
                glAttachShader(this->_shaderProgram, this->_geometryShader);
        }
        if (this->_hasComputeShader)
        {
                glAttachShader(this->_shaderProgram, this->_computeShader);
        }
}

/*
Fonction        : linkProgram
Argument(s)     : /
retour          : /
Commentaires    : link le shader program et recherche les erreurs de linkage
*/
void ShaderProgram::linkProgram()
{
        // link le shaderProgram
        glLinkProgram(this->_shaderProgram);
        // vérifie les erreurs de linkage
        GLint linkStatus;
        glGetProgramiv(this->_shaderProgram, GL_LINK_STATUS, &linkStatus);
        // s'il y a des erreurs
        if (linkStatus == GL_FALSE)
        {
                GLint logInfoLength = 0;
                glGetProgramiv(this->_shaderProgram, GL_INFO_LOG_LENGTH, &logInfoLength);
                // si le log est non vide
                if (logInfoLength > 0)
                {
                        // affichage des erreurs de compilation
                        GLchar *infoLog = new GLchar[logInfoLength];
                        GLsizei length = 0;
                        glGetProgramInfoLog(this->_shaderProgram, logInfoLength, &length, infoLog);
                        // affichage du log
                        std::cout << infoLog << std::endl;
                }
                // si erreur -> arrêt
                fprintf(stderr, "linkProgram : error while linking the shaderProgram !\n");
                exit(1);
        }
        // sinon OK
}
