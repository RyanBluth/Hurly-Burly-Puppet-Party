#include "MousePerspectiveCamera.h"
#include "Mouse.h"
#include "Transform.h"
#include "System.h"

MousePerspectiveCamera::MousePerspectiveCamera():
	PerspectiveCamera(),
	NodeTransformable(new Transform()),
	//NodeAnimatable(),
	NodeUpdatable(),
	mouse(&Mouse::getInstance()),
	speed(0.1f),
	mouseSpeed(0.05f)
{
	Dimension screenDimensions = vox::getScreenDimensions();
	lastMouseY = screenDimensions.height/2;
	lastMouseX = screenDimensions.width/2;
}

MousePerspectiveCamera::~MousePerspectiveCamera(){
}

void MousePerspectiveCamera::update(Step* _step){

	Dimension screenDimensions = vox::getScreenDimensions();

	double centerX = static_cast<double>(screenDimensions.width)*0.5;
	double centerY = static_cast<double>(screenDimensions.height)*0.5;

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

	if(deltaX != 0){
		pitch += (mouseSpeed * static_cast<float>(offsetY));
	}if(deltaY != 0){
		yaw += (mouseSpeed * static_cast<float>(offsetX));
	}

	PerspectiveCamera::update(_step);

	glfwSetCursorPos(vox::currentContext, centerX, centerY);

	lastMouseX = offsetX;
	lastMouseY = offsetY;
}