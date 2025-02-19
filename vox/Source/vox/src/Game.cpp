#pragma once

#include <stdlib.h>

#include "Game.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Vox.h"
#include "MatrixStack.h"
#include "VoxRenderOptions.h"
#include "GLUtils.h"


Game::Game(bool _isRunning) :
	accumulator(0.0),
	lastTimestep(0.0),
	mouse(&Mouse::getInstance()),
	keyboard(&Keyboard::getInstance()),
	isRunning(_isRunning),
	printFPS(true),
	currentScene(nullptr),
	currentSceneKey(""),
	switchingScene(false),
	newSceneKey(""),
	deleteOldScene(false),
	kc_lastKey(0),
	kc_code(0),
	kc_active(false),
	kc_just_active(false)
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	viewPortWidth = width;
	viewPortHeight = height;
	viewPortX = 0;
	viewPortY = 0;
	lastTime = glfwGetTime();
	nbFrames = 0;
}

Game::~Game(void){
	for(auto scene : scenes){
		delete scene.second;
	}
	scenes.clear();
}

void Game::performGameLoop(){
#ifdef VOX_LIMIT_FRAMERATE
	double time = glfwGetTime();
	accumulator += time - lastTimestep;
	lastTimestep = time;
	//std::cout << accumulator << std::endl;
	if(accumulator >= vox::step.targetFrameDuration){
		accumulator -= vox::step.targetFrameDuration;
#endif
		vox::calculateDeltaTimeCorrection();
		glfwPollEvents();
		update(&vox::step);
		draw();

		glfwSwapBuffers(vox::currentContext);
		manageInput();
		isRunning = !glfwWindowShouldClose(vox::currentContext);

		if(switchingScene){
			if(deleteOldScene){
				scenes.erase(currentSceneKey);
				delete currentScene;
			}
			currentSceneKey = newSceneKey;
			currentScene = scenes.at(currentSceneKey);
			switchingScene = false;
			newSceneKey = "";
		}	
#ifdef VOX_LIMIT_FRAMERATE
	}
#endif
}

void Game::update(Step * _step){

	if(printFPS){
		printFps();
	}
	if(keyboard->keyDown(GLFW_KEY_ESCAPE)){
		glfwSetWindowShouldClose(vox::currentContext, true);
	}
	if(kc_just_active){
		kc_just_active = false;
	}
	switch(kc_code){
	case 0:
		if(keyboard->keyJustUp(GLFW_KEY_UP)){
			kc_lastKey = GLFW_KEY_UP;
			kc_code += 1;
		}
		break;
	case 1:
		if(keyboard->keyJustUp(GLFW_KEY_UP)){
			if(kc_lastKey == GLFW_KEY_UP){
				kc_lastKey = GLFW_KEY_UP;
				kc_code += 1;
			}else{
				kc_code = 0;
			}
		}
		break;
	case 2:
		if(keyboard->keyJustUp(GLFW_KEY_DOWN)){
			if(kc_lastKey == GLFW_KEY_UP){
				kc_lastKey = GLFW_KEY_DOWN;
				kc_code += 1;
			}else{
				kc_code = 0;
			}
		}
		break;
	case 3:
		if(keyboard->keyJustUp(GLFW_KEY_DOWN)){
			if(kc_lastKey == GLFW_KEY_DOWN){
				kc_lastKey = GLFW_KEY_DOWN;
				kc_code += 1;
			}else{
				kc_code = 0;
			}
		}
		break;
	case 4:
		if(keyboard->keyJustUp(GLFW_KEY_LEFT)){
			if(kc_lastKey == GLFW_KEY_DOWN){
				kc_lastKey = GLFW_KEY_LEFT;
				kc_code += 1;
			}else{
				kc_code = 0;
			}
		}
		break;
	case 5:
		if(keyboard->keyJustUp(GLFW_KEY_RIGHT)){
			if(kc_lastKey == GLFW_KEY_LEFT){
				kc_lastKey = GLFW_KEY_RIGHT;
				kc_code += 1;
			}else{
				kc_code = 0;
			}
		}
		break;
	case 6:
		if(keyboard->keyJustUp(GLFW_KEY_LEFT)){
			if(kc_lastKey == GLFW_KEY_RIGHT){
				kc_lastKey = GLFW_KEY_LEFT;
				kc_code += 1;
			}else{
				kc_code = 0;
			}
		}
		break;
	case 7:
		if(keyboard->keyJustUp(GLFW_KEY_RIGHT)){
			if(kc_lastKey == GLFW_KEY_LEFT){
				kc_lastKey = GLFW_KEY_RIGHT;
				kc_code += 1;
			}else{
				kc_code = 0;
			}
		}
		break;
	case 8:
		if(keyboard->keyJustUp(GLFW_KEY_B)){
			if(kc_lastKey == GLFW_KEY_RIGHT){
				kc_lastKey = GLFW_KEY_B;
				kc_code += 1;
			}else{
				kc_code = 0;
			}
		}
		break;
	case 9:
		if(keyboard->keyJustUp(GLFW_KEY_A)){
			if(kc_lastKey == GLFW_KEY_B){
				kc_active = !kc_active;
				kc_just_active = true;
			}
			kc_code = 0;
		}
		break;
	}
	
	if(currentScene != nullptr/* && vox::step.deltaTimeCorrection < 5*/){
		currentScene->update(_step);
	}
}

void Game::draw(void){
	vox::MatrixStack ms;
	VoxRenderOptions ro(nullptr, nullptr, nullptr);
	ro.kc_active = kc_active;
	currentScene->render(&ms, &ro);
}

void Game::manageInput(){
	keyboard->update();
	mouse->update();
}

void Game::printFps(){
	// Measure speed
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0){
		// If last printf() was more than 1 sec ago
		// printf and reset timer
		printf("%f FPS\n", double(nbFrames));
		nbFrames = 0;
		lastTime += 1.0;
	}
}

void Game::switchScene(std::string _newSceneKey, bool _deleteOldScene){
	deleteOldScene = _deleteOldScene;
	if(scenes.count(_newSceneKey) > 0){
		switchingScene = true;
		newSceneKey = _newSceneKey;
	}else{
		switchingScene = false;
		newSceneKey = "";
	}
}




void Game::toggleFullScreen(){
	// Toggle fullscreen flag.
	vox::fullscreen = !vox::fullscreen;
	//get size
	int w, h;
	//if(vox::fullscreen){
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	w = mode->width;
	h = mode->height;

	if(!vox::fullscreen){
		w /= 2;
		h /= 2;
	}
	// Create the new window.
	GLFWwindow * window;
#ifdef _DEBUG
	window = glfwCreateWindow(w, h, "VOX",  nullptr, nullptr);
#else
	window = glfwCreateWindow(w, h, "VOX",  vox::fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
#endif
	if(!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	vox::initWindow(window);
	glfwDestroyWindow(vox::currentContext);
	glfwMakeContextCurrent(window);
	vox::currentContext = window;

	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	viewPortWidth = width;
	viewPortHeight = height;
	viewPortX = 0;
	viewPortY = 0;
	

	for(std::pair<std::string, Scene *> s : scenes){
		s.second->unload();
	}
	ResourceManager::unload();
	
	ResourceManager::load();
	for(std::pair<std::string, Scene *> s : scenes){
		s.second->load();
	}
	//resourceManager->load();

	checkForGlError(0,__FILE__,__LINE__);
}

void Game::setViewport(float _x, float _y, float _w, float _h){
	viewPortX = _x;
	viewPortY = _y;
	viewPortWidth = _w;
	viewPortHeight = _h;
}