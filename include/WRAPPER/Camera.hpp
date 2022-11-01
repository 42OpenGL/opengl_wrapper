#pragma once
#include <glm/glm.hpp>

// TODO: camner wrapper 완료하기
class Camera
{
	public:
		glm::vec3	_eye;
		float		_step;
		glm::vec3	_center;
		glm::vec3	_up;
		Camera() {}
	public: 
		Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float step = 0.042)
		: _eye(eye), _center(center), _up(up), _step(step)
		{
		}
};