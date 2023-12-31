#pragma once
#include "common.h"
#include <learnopengl/simplemesh.h>
#include <vector>

vector<sVertex> convertToVertexglmVector(const std::vector<float> dataArray);
void calculateNormalsSmooth(std::vector<sVertex>& vertices, const std::vector<unsigned int>& indices);

glm::mat4 setMVP(Shader shader, glm::mat4 transform = glm::mat4(1));