#pragma once
#include <glm/vec3.hpp>

struct Camera {
	glm::vec3 position;
	float angle_x, angle_y;
	float distance;
};

/* This file needs: (@mike)
	a frustum struct
	a function to determine if pos/radius is within a frustum
	help
*/