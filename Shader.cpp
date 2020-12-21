#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath) {
    // 1. получение исходного кода вершинного/фрагментного шейдера
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // убеждаемся, что объекты ifstream могут выбросить исключение:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
      // открываем файлы
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      // читаем содержимое файловых буферов
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // закрываем файлы
      vShaderFile.close();
      fShaderFile.close();
      // конвертируем в строковую переменную данные из потока
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
      // if geometry shader path is present, also load a geometry shader
      if (geometryPath != nullptr)
      {
        gShaderFile.open(geometryPath);
        std::stringstream gShaderStream;
        gShaderStream << gShaderFile.rdbuf();
        gShaderFile.close();
        geometryCode = gShaderStream.str();
      }
    }
    catch (std::ifstream::failure& e)
    {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. компилируем шейдеры
    unsigned int vertex, fragment;
    // вершинный шейдер
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // Фрагментный шейдер
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // Если был дан геометрический шейдер, то компилируем его
    unsigned int geometry;
    if (geometryPath != nullptr)
    {
      const char* gShaderCode = geometryCode.c_str();
      geometry = glCreateShader(GL_GEOMETRY_SHADER);
      glShaderSource(geometry, 1, &gShaderCode, nullptr);
      glCompileShader(geometry);
      checkCompileErrors(geometry, "GEOMETRY");
    }
    // Шейдерная программа
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (geometryPath != nullptr)
      glAttachShader(ID, geometry);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // После того, как мы связали шейдеры с нашей программой, удаляем их, т.к. они больше не нужны
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
      glDeleteShader(geometry);
  };

void Shader::checkCompileErrors(GLuint shader, const std::string& type) {
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
}