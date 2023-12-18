#pragma once
#include "common.h"
#include "shape.h"
#include <vector>
#include <learnopengl/shader.h>
#include "common.h"


class object_
{
public:
	Shader shader;
	object_(Shader &shader);

	virtual void Draw();
	virtual void drawMeshes(glm::mat4 transform, glm::mat4 scaleMat);
	virtual void init() = 0;
};

