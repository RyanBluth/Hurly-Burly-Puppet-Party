#pragma once

#include "MeshInterface.h"
#include "RenderOptions.h"
#include "Texture.h"
#include "Material.h"
#include "MatrixStack.h"

MeshInterface::MeshInterface(GLenum polygonalDrawMode, GLenum drawMode):
	drawMode(drawMode),
	polygonalDrawMode(polygonalDrawMode),
	loaded(false),
	dirty(true),
	shouldRenderLights(true),
	shouldRenderTextures(true),
	shouldRenderExtras(true),
	shouldRenderShadows(true)
{
	load();
	clean();
}

MeshInterface::~MeshInterface(){
	glDeleteVertexArrays(1, &vaoId);
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
	for(Texture * t : textures){
		t->decrementAndDelete();
	}
	for(Material * m : materials){
		m->decrementAndDelete();
	}
	vaoId = 0;
	vboId = 0;
	iboId = 0;
	GLUtils::checkForError(0,__FILE__,__LINE__);
}

GLsizei MeshInterface::getStride(){
	return sizeof(Vertex);
}

GLsizei MeshInterface::getVertCount(){
	return vertices.size();
}

void MeshInterface::load(){
	if(!loaded){
		glBindVertexArray(0);

		// Vertex Array Object (VAO)
		glGenVertexArrays(1, &vaoId);
		glBindVertexArray(vaoId);

		// Vertex Auffer Object (VBO)
		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), drawMode);

		// Index Buffer Object (IBO)
		glGenBuffers(1, &iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), drawMode);

		// Initialize textures
		for (Texture * texture : textures){
			texture->load();
		}

		// Disable VAO
		glBindVertexArray(0);
		GLUtils::checkForError(true,__FILE__,__LINE__);
		loaded = true;
	}
}

void MeshInterface::unload(){
	if(loaded){
		glDeleteBuffers(1, &iboId);
		glDeleteBuffers(1, &vboId);
		glDeleteVertexArrays(1, &vaoId);
		for (Texture * texture : textures){
			texture->unload();
		}
		iboId = 0;
		vboId = 0;
		vaoId = 0;

		loaded = false;
		dirty = true;
	}
}

void MeshInterface::clean(){
	if(dirty){
		// Vertex Buffer Object (VBO)
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * (vertices.size()), vertices.data(), GL_DYNAMIC_DRAW);
		GLUtils::checkForError(0,__FILE__,__LINE__);

		// Index Buffer Object (IBO)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (indices.size()), indices.data(), GL_DYNAMIC_DRAW);
		GLUtils::checkForError(0,__FILE__,__LINE__);
		dirty = false;
	}
}

void MeshInterface::render(MatrixStack * _matrixStack, RenderOptions * _renderOption){
	if(glIsVertexArray(vaoId) == GL_TRUE){
		if(glIsBuffer(vboId) == GL_TRUE){
			if(glIsBuffer(iboId) == GL_TRUE){
				GLUtils::checkForError(0,__FILE__,__LINE__);
				// Bind VAO
				GLUtils::checkForError(0,__FILE__,__LINE__);
				glBindVertexArray(vaoId);
				// Specify _shader attributes
				/*if(_renderOption->overrideShader != nullptr){
					//configureDefaultVertexAttributes(_renderOption->overrideShader);
					glUseProgram(_renderOption->overrideShader->getProgramId());	
				}else{
					glUseProgram(_renderOption->shader->getProgramId());	
					//configureDefaultVertexAttributes(_renderOption->shader);
				}*/
				glUseProgram(_renderOption->shader->getProgramId());	

				GLUtils::checkForError(0,__FILE__,__LINE__);

				//Model View Projection
				configureModelViewProjection(_matrixStack, _renderOption);

				//TODO - A flag in the shader should be set to disable these
				if(shouldRenderTextures){
					configureTextures(_matrixStack, _renderOption);
				}
				if(shouldRenderLights){
					configureLights(_matrixStack, _renderOption);
				}
				if(shouldRenderExtras){
					configureExtras(_matrixStack, _renderOption);
				}
				if(shouldRenderShadows){
					configureShadows(_matrixStack, _renderOption);
				}

				//Alpha blending
				// Should these be here or only once in the main render loop?
				glEnable (GL_BLEND);
				glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//Texture repeat
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				// Draw (note that the last argument is expecting a pointer to the indices, but since we have an ibo, it's actually interpreted as an offset)
				glDrawRangeElements(polygonalDrawMode, 0, vertices.size(), indices.size(), GL_UNSIGNED_INT, 0);
				//glDrawElements(drawMode, vertices.size(), GL_UNSIGNED_BYTE, 0);
				GLUtils::checkForError(0,__FILE__,__LINE__);

				// Disable VAO
				glBindVertexArray(0);
			}else{
				std::cout << "ibo bad" << std::endl << std::endl;
			}
		}else{
			std::cout << "vbo bad" << std::endl << std::endl;
		}
	}else{
		std::cout << "vao bad" << std::endl << std::endl;
	}
}

void MeshInterface::configureTextures(MatrixStack * _matrixStack, RenderOptions * _renderOption){
	// Pass the _shader the number of textures
	glUniform1i(glGetUniformLocation(_renderOption->shader->getProgramId(), GL_UNIFORM_ID_NUM_TEXTURES), textures.size());
	// Bind each texture to the texture sampler array in the frag _shader
	for(unsigned long int i = 0; i < textures.size(); i++){
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures.at(i)->textureId);
		glUniform1i(glGetUniformLocation(_renderOption->shader->getProgramId(), GL_UNIFORM_ID_TEXTURE_SAMPLER), i);
	}
}

void MeshInterface::configureLights(MatrixStack * _matrixStack, RenderOptions * _renderOption){
	glm::mat4 model = _matrixStack->currentModelMatrix;
	GLuint modelUniformLocation = glGetUniformLocation(_renderOption->shader->getProgramId(), GL_UNIFORM_ID_MODEL_MATRIX);
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, &model[0][0]);

	// Pass the _shader the number of lights & materials
	glUniform1i(glGetUniformLocation(_renderOption->shader->getProgramId(),	GL_UNIFORM_ID_NUM_LIGHTS), _renderOption->lights->size());
	glUniform1i(glGetUniformLocation(_renderOption->shader->getProgramId(), GL_UNIFORM_ID_NUM_MATERIALS), materials.size());

	// Pass each material to the _shader
	for(unsigned long int i = 0; i < materials.size(); i++){
		const char * mat = GLUtils::buildGLArryReferenceString(GL_UNIFORM_ID_MATERIAL_TYPE, i);
		GLuint materialUniformLocation = glGetUniformLocation(_renderOption->shader->getProgramId(), mat);
		int materialType = static_cast<int>(materials.at(i)->data.type);
		glUniform1f(materialUniformLocation, materialType);
	}

	//Pass the paramaters for each light to the _shader
	for(unsigned long int i = 0; i < _renderOption->lights->size(); i++){
		const char * pos = GLUtils::buildGLArryReferenceString(GL_UNIFORM_ID_LIGHTS_POSITION, i);
		const char * ins = GLUtils::buildGLArryReferenceString(GL_UNIFORM_ID_LIGHTS_INTENSITIES, i);
		GLuint lightUniformLocation = glGetUniformLocation(_renderOption->shader->getProgramId(), pos);
		glUniform3f(lightUniformLocation, _renderOption->lights->at(i)->data.position.x, _renderOption->lights->at(i)->data.position.y, _renderOption->lights->at(i)->data.position.z);
		GLuint intensitiesUniformLocation = glGetUniformLocation(_renderOption->shader->getProgramId(), ins);
		glUniform3f(intensitiesUniformLocation, _renderOption->lights->at(i)->data.intensities.x, _renderOption->lights->at(i)->data.intensities.y, _renderOption->lights->at(i)->data.intensities.z);
	}
}

void MeshInterface::configureModelViewProjection(MatrixStack * _matrixStack, RenderOptions * _renderOption){
	glm::mat4 mvp = _matrixStack->projectionMatrix * _matrixStack->viewMatrix * _matrixStack->currentModelMatrix;
	GLuint mvpUniformLocation = glGetUniformLocation(_renderOption->shader->getProgramId(),  GL_UNIFORM_ID_MODEL_VIEW_PROJECTION);
	glUniformMatrix4fv(mvpUniformLocation, 1, GL_FALSE, &mvp[0][0]);
	GLUtils::checkForError(0,__FILE__,__LINE__);
}

void MeshInterface::configureShadows(MatrixStack* _matrixStack, RenderOptions* _renderOption){
	//Configure DepthMVP
	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0);

	glm::vec3 lightInvDir = glm::vec3(0.5, 2, 2);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));

	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * _matrixStack->getCurrentMatrix();
	depthMVP = biasMatrix * depthMVP;
	glUniformMatrix4fv(glGetUniformLocation(_renderOption->shader->getProgramId(), GL_UNIFORM_ID_DEPTH_MVP), 1, GL_FALSE, &depthMVP[0][0]);

	if(_renderOption->shadowMapTextureId != 0){
		glActiveTexture(GL_TEXTURE0 + textures.size());
		glBindTexture(GL_TEXTURE_2D, _renderOption->shadowMapTextureId);
		glUniform1i(glGetUniformLocation(_renderOption->shader->getProgramId(), GL_UNIFORM_ID_SHADOW_MAP_SAMPLER), textures.size());
	}
}

void MeshInterface::configureExtras(MatrixStack * _matrixStack, RenderOptions * _renderOption){
}

void MeshInterface::configureDefaultVertexAttributes(Shader *_shader){
	GLUtils::configureVertexAttributes(_shader->get_aVertexPosition(), 3, 0, vaoId, getStride());
	GLUtils::configureVertexAttributes(_shader->get_aVertexColor(), 4, sizeof(float) * 3, vaoId, getStride());
	GLUtils::configureVertexAttributes(_shader->get_aVertexNormals(), 3, sizeof(float) * 7, vaoId, getStride());
	GLUtils::configureVertexAttributes(_shader->get_aVertexUVs(), 2, sizeof(float) * 10, vaoId, getStride());
}

void MeshInterface::pushVert(Vertex _vertex){
	vertices.push_back(_vertex);
	dirty = true;
}

void MeshInterface::pushTexture2D(Texture* _texture){
	++_texture->referenceCount;
	textures.push_back(_texture);
}

void MeshInterface::pushMaterial(Material* _material){
	++_material->referenceCount;
	materials.push_back(_material);
}

void MeshInterface::setNormal(unsigned long int _vertId, float _x, float _y, float _z){
	vertices.at(_vertId).nx = _x;
	vertices.at(_vertId).ny = _y;
	vertices.at(_vertId).nz = _z;

	dirty = true;
}

void MeshInterface::setUV(unsigned long _vertId, float _u, float _v){
	vertices.at(_vertId).u = _u;
	vertices.at(_vertId).v = _v;
}
void TriMesh::pushTri(GLuint _v0, GLuint _v1, GLuint _v2){
	indices.push_back(_v0);
	indices.push_back(_v1);
	indices.push_back(_v2);

	dirty = true;
}
void QuadMesh::pushQuad(GLuint _v0, GLuint _v1, GLuint _v2, GLuint _v3){
	indices.push_back(_v0);
	indices.push_back(_v1);
	indices.push_back(_v2);
	indices.push_back(_v3);

	dirty = true;
}