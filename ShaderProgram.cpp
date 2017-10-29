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
        // pas de shader
        this->hasVertexShader = false;
        this->hasFragmentShader = false;
        this->hasComputeShader = false;
        this->hasTesselationControlShader = false;
        this->hasTesselationEvaluationShader = false;
        this->hasGeometryShader = false;
        // ni de code de shader
        this->vertexShaderCode = nullptr;
        this->fragmentShaderCode = nullptr;
        this->computeShaderCode = nullptr;
        this->tesselationControlShaderCode = nullptr;
        this->tesselationEvaluationShader = nullptr;
        this->geometryShaderCode = nullptr;
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
void ShaderProgram::addShaderFromString(GLenum shaderType, char *shaderCode)
{
        // doc : GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
        switch (shaderType)
        {
                case GL_VERTEX_SHADER :
                        this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
                        this->vertexShaderCode = shaderCode;
                        glShaderSource(this->vertexShader, 1, this->vertexShaderCode, nullptr);
                        this->hasVertexShader = true;
                        break;

                case GL_FRAGMENT_SHADER :
                        this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                        this->fragmentShaderCode = shaderCode;
                        glShaderSource(this->fragmentShader, 1, this->fragmentShaderCode, nullptr);
                        this->hasFragmentShader = true;
                        break;

                case GL_TESS_CONTROL_SHADER :
                        this-> = glCreateShader(GL_TESS_CONTROL_SHADER);
                        this->tesselationControlShaderCode = shaderCode;
                        glShaderSource(this->tesselationControlShader, 1, this->tesselationControlShaderCode, nullptr);
                        this->hasTesselationControlShader = true;
                        break;

                case GL_TESS_EVALUATION_SHADER :
                        this-> = glCreateShader(GL_TESS_EVALUATION_SHADER);
                        this->tesselationEvaluationShaderCode = shaderCode;
                        glShaderSource(this->tesselationEvaluationShader, 1, this->tesselationEvaluationShaderCode, nullptr);
                        this->hasTesselationEvaluationShader = true;
                        break;

                case GL_GEOMETRY_SHADER :
                        this-> = glCreateShader(GL_GEOMETRY_SHADER);
                        this->geometryShaderCode = shaderCode;
                        glShaderSource(this->geometryShader, 1, this->geometryShaderCode, nullptr);
                        this->hasGeometryShader = true;
                        break;

                case GL_COMPUTE_SHADER :
                        this-> = glCreateShader(GL_COMPUTE_SHADER);
                        this->computeShaderCode = shaderCode;
                        glShaderSource(this->computeShader, 1, this->computeShaderCode, nullptr);
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
void ShaderProgram::addShaderFromFile(GLenum shaderType, const std::string& shaderFile)
{
        std::ifstream file(shaderFile.c_str(), std::ios::in);
        std::string shaderCode;     // contiendra le code du shader

        if (file)
        {
                // initialiser une chaine de caractères pour contenir le contenu du fichier
                file.seekg(0, std::ios::end);
                shader.resize(file.tellg());
                file.seekg(0, std::ios::beg);
                // lecture du fichier
                file.read(shaderCode[0], shaderCode.size());
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

        if (this->hasVertexShader)
        {
                glCompileShader(this->vertexShader);
                compileVertexShader = __checkCompilationStatus(this->vertexShader);
        }
        if (this->hasFragmentShader)
        {
                glCompileShader(this->fragmentShader);
                compileFragmentShader = __checkCompilationStatus(this->fragmentShader);
        }
        if (this->hasTesselationControlShader)
        {
                glCompileShader(this->tesselationControlShader);
                compileTesselationControlShader = __checkCompilationStatus(this->tesselationControlShader);
        }
        if (this->hasTesselationEvaluationShader)
        {
                glCompileShader(this->tesselationEvaluationShader);
                compileTesselationEvaluationShader = __checkCompilationStatus(this->tesselationEvaluationShader);
        }
        if (this->hasGeometryShader)
        {
                glCompileShader(this->geometryShader);
                compileGeometryShader = __checkCompilationStatus(this->geometryShader);
        }
        if (this->hasComputeShader)
        {
                glCompileShader(this->computeShader);
                compileComputeShader = __checkCompilationStatus(this->computeShader);
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
        if (this->hasVertexShader)
        {
                glAttachShader(this->shaderProgram, this->vertexShader);
        }
        if (this->hasFragmentShader)
        {
                glAttachShader(this->shaderProgram, this->fragmentShader);
        }
        if (this->hasTesselationControlShader)
        {
                glAttachShader(this->shaderProgram, this->tesselationControlShader);
        }
        if (this->hasTesselationEvaluationShader)
        {
                glAttachShader(this->shaderProgram, this->tesselationEvaluationShader);
        }
        if (this->hasGeometryShader)
        {
                glAttachShader(this->shaderProgram, this->geometryShader);
        }
        if (this->hasComputeShader)
        {
                glAttachShader(this->shaderProgram, this->computeShader);
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
        glLinkProgram(this->shaderProgram);
        // vérifie les erreurs de linkage
        GLint linkStatus;
        glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &compileStatus);
        // s'il y a des erreurs
        if (linkStatus == GL_FALSE)
        {
                GLint logInfoLength = 0;
                glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &logInfoLength);
                // si le log est non vide
                if (logInfoLength > 0)
                {
                        // affichage des erreurs de compilation
                        GLchar *infoLog = new GLchar[logInfoLength];
                        GLsizei length = 0;
                        glGetProgramInfoLog(this->shaderProgram, logInfoLength, &length, infoLog);
                        // affichage du log
                        std::cout << infoLog << std::endl;
                }
                // si erreur -> arrêt
                fprintf("linkProgram : error while linking the shaderProgram !\n");
                exit(1);
        }
        // sinon OK
}
