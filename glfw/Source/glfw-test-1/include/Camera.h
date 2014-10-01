#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "System.h"

class Camera : public Node{
public:
	Camera();
	~Camera();

	//tracks the changes in mouse position and uses them to rotate the camera
	void update();

	Mouse * mouse;

	Transform * transform;

	glm::vec3 forwardVectorLocal;	// Direction the camera's front would be pointing at if it weren't rotated at all
	glm::vec3 forwardVectorRotated;	// Direction the camera's front is pointing at (local * orientation)
	glm::vec3 upVectorLocal;		// Direction the camera's top would be pointing at if it weren't rotated at all
	glm::vec3 upVectorRotated;		// Direction the camera's top is pointing at (local * orientation)
	glm::vec3 rightVectorLocal;		// Direction the camera's right side would be pointing at if it weren't rotated at all
	glm::vec3 rightVectorRotated;	// Direction the camera's right side is pointing at (local * orientation)

	float fieldOfView;
	float pitch;
	float yaw;

	float speed;
	float mouseSpeed;

	glm::quat lastOrientation;

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

private :
	double lastMouseX;
	double lastMouseY;
};