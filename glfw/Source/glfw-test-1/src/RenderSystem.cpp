#include "RenderSystem.h"

RenderSystem::RenderSystem():
	shaderArray(new std::vector<ShaderInterface*>)
{
}

RenderSystem::~RenderSystem(void){
	delete shaderArray->at(0);
	delete shaderArray;
}

void RenderSystem::destroyRenderSystem(){
	RenderSystem *renderSystem = &getInstance();
	delete renderSystem;
}

RenderSystem& RenderSystem::getInstance(){
	static RenderSystem *renderSystem;
	if(renderSystem == nullptr){
		renderSystem = new RenderSystem();
	}
	return *renderSystem;
}
void RenderSystem::render(GLFWwindow * _context, std::vector<Entity *> * _renderChildren, glm::mat4 _projectionMatrix, glm::mat4 _viewMatrix){
	glfwMakeContextCurrent(_context);

	float ratio;
	int width, height;
	GLUtils::checkForError(0,__FILE__,__LINE__);
	glfwGetFramebufferSize(_context, &width, &height);
	GLUtils::checkForError(0,__FILE__,__LINE__);
	ratio = width / static_cast<float>(height);
	GLUtils::checkForError(0,__FILE__,__LINE__);
	glViewport(0, 0, width, height);
	GLUtils::checkForError(0,__FILE__,__LINE__);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GLUtils::checkForError(0,__FILE__,__LINE__);
	glEnable(GL_DEPTH_TEST);
	GLUtils::checkForError(0,__FILE__,__LINE__);

	//Back-face culling
	/*glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CW); // GL_CCW for counter clock-wise
	GLUtils::checkForError(0,__FILE__,__LINE__);*/

	//not needed because we aren't actually using the glTranslate/Rotate/Scale functions
	//glLoadIdentity();

	for(Entity * e : *_renderChildren){
		e->draw(_projectionMatrix, _viewMatrix);
	}

	GLUtils::checkForError(0,__FILE__,__LINE__);
}