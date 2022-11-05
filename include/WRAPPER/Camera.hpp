#pragma once
#include <glm/glm.hpp>
#include <ft_glm/ft_rotate.hpp>

class Camera
{
	private:
		float		_step;
		glm::vec3	_eye;
		glm::vec3	_center;
		glm::vec3	_up;
		Camera() {}
	public: 
		Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float step = 0.042)
		: _eye(eye), _center(center), _up(up), _step(step)
		{
		}

		float getStep() const;
		void setStep(float step);

		void move_up( void );
		void move_down( void ); 
		void move_right( void ); 
		void move_left( void ); 
		void move_forward( void ); 
		void move_backward( void );

		const	glm::mat4 lookAt() const;
		void	rotate(float rad, glm::vec3 axis);
};

float Camera::getStep() const
{
	return (this->_step);
}

void Camera::setStep(float s)
{
	this->_step = s;
}

void Camera::move_up( void )
{
	this->_eye.z += this->_step;
	this->_center.z += this->_step;
}

void Camera::move_down( void )
{
	this->_eye.z -= this->_step;
	this->_center.z -= this->_step;
}

void Camera::move_right( void )
{
	this->_eye.x += this->_step;
	this->_center.x += this->_step;
}
 
void Camera::move_left( void )
{
	this->_eye.x -= this->_step;
	this->_center.x -= this->_step;
}

void Camera::move_forward( void )
{
	this->_eye.y -= this->_step;
	this->_center.y -= this->_step;
} 

void Camera::move_backward( void )
{
	this->_eye.y += this->_step;
	this->_center.y += this->_step;
}

const glm::mat4 Camera::lookAt() const
{
	return (glm::lookAt(this->_eye, this->_center, this->_up));
}


/*
	Rotate the camera's orientation around the reference axis.
*/
void Camera::rotate(float rad, glm::vec3 axis)
{
	glm::vec3 eye_to_center = this->_center - this->_eye;

	glm::mat4 rotate_mat = ft::rotate(glm::mat4(1.0f), rad, axis);
	eye_to_center = glm::vec3( rotate_mat * glm::vec4(eye_to_center, 0) );

	this->_center = this->_eye + eye_to_center;
}