#include "Camera.h"

Camera::Camera():
	forwardVectorLocal(1.f, 0.f, 0.f),
	forwardVectorRotated(1.f, 0.f, 0.f),
	upVectorLocal(0.f, 1.f, 0.f),
	upVectorRotated(0.f, 1.f, 0.f),
	rightVectorLocal(0.f, 0.f, 1.f),
	rightVectorRotated(0.f, 0.f, 1.f),
	transform(new Transform()),
	fieldOfView(45.0f),
	horizontalAngle(3.14f),
	verticalAngle(0.0f),
	speed(0.1f),
	mouseSpeed(0.05f),
	mouse(&Mouse::getInstance())
{
	transform->translateX(-5);

	Dimension screenDimensions = System::getScreenDimensions();
	lastMouseY	= screenDimensions.height/2;
	lastMouseX	= screenDimensions.width/2;
}

Camera::~Camera(){
}

void Camera::update(){
	Dimension screenDimensions = System::getScreenDimensions();

	double centerX = (double)screenDimensions.width*0.5;
	double centerY = (double)screenDimensions.height*0.5;

	double offsetX = 0.;
	double offsetY = 0.;

	if(abs(centerX - mouse->mouseX()) > 0.01){
		offsetX = centerX - mouse->mouseX();
	}
	if(abs(centerY - mouse->mouseY()) > 0.01){
		offsetY = centerY - mouse->mouseY();
	}

	double deltaX = lastMouseX - offsetX;
	double deltaY = lastMouseY - offsetY;

	if(deltaX != 0 || deltaY != 0){
		horizontalAngle	= mouseSpeed * (float)vox::deltaTimeCorrection * (float)offsetX;
		verticalAngle	= mouseSpeed * (float)vox::deltaTimeCorrection * (float)offsetY;
		
		transform->orientation = glm::rotate(transform->orientation, verticalAngle, rightVectorLocal);
		transform->orientation = glm::rotate(transform->orientation, horizontalAngle, upVectorLocal);
		
		forwardVectorRotated	= transform->orientation * forwardVectorLocal;
		upVectorRotated			= transform->orientation * upVectorLocal;
		rightVectorRotated		= transform->orientation * rightVectorLocal;
	}

	glfwSetCursorPos(vox::currentContext, centerX, centerY);

	lastMouseX = offsetX;
	lastMouseY = offsetY;
}

glm::mat4 Camera::getViewMatrix(){
	return glm::lookAt(
		transform->translationVector,	// Camera is here        
		transform->translationVector + forwardVectorRotated, // and looks here : at the same position, plus "direction"
		upVectorRotated				// Head is up (set to 0,-1,0 to look upside-down)
	);
}

glm::mat4 Camera::getProjectionMatrix(){
	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	return glm::perspective(fieldOfView, 4.0f / 3.0f, 0.1f, 100.0f);
}