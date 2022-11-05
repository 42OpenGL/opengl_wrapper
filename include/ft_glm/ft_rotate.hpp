#pragma once

#include <glm/glm.hpp>

/*
    1. axis를 기준으로 rad만큼 돌아가는 행렬을 구한다.
        a) 로드리그 공식
        b) 쿼터니언
    2. mat과 위에서 만든 행렬을 곱한다.
    3. 결과를 반환한다.
*/
namespace ft
{
	glm::mat4 rotate(glm::mat4 mat, float rad, glm::vec3 axis)
	{
		glm::mat4 new_mat;

		float c = cosf(rad);
		float s = sinf(rad);
		float v = 1 - c;

		new_mat[0][0] = axis[0] * axis[0] * v + c;
		new_mat[0][1] = axis[0] * axis[1] * v + axis[2] * s;
		new_mat[0][2] = axis[0] * axis[2] * v - axis[1] * s;
		new_mat[0][3] = 0;
		
		new_mat[1][0] = axis[1] * axis[0] * v - axis[2] * s;
		new_mat[1][1] = axis[1] * axis[1] * v + c;
		new_mat[1][2] = axis[1] * axis[2] * v + axis[0] * s;
		new_mat[1][3] = 0;
		
		new_mat[2][0] = axis[2] * axis[0] * v + axis[1] * s;
		new_mat[2][1] = axis[2] * axis[1] * v - axis[0] * s;
		new_mat[2][2] = axis[2] * axis[2] * v + c;
		new_mat[2][3] = 0;
		
		new_mat[3][0] = 0;
		new_mat[3][1] = 0;
		new_mat[3][2] = 0;
		new_mat[3][3] = 1;

		new_mat = new_mat * mat;	
		return new_mat;
	}
}
