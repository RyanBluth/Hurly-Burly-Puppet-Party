#pragma once

#include "MeshEntity.h"

#include "MeshInterface.h"
#include "shader/Shader.h"

#include "RenderOptions.h"
#include "MatrixStack.h"

MeshEntity::MeshEntity(MeshInterface * _mesh, Transform * _transform, Shader * _shader):
	Entity(_transform),
	NodeTransformable(_transform),
	NodeChild(nullptr),
	NodeRenderable(),
	mesh(_mesh),
	shader(_shader)
{

}

MeshEntity::~MeshEntity(void){
	delete transform;
	transform = nullptr;
	delete mesh;
	if(shader != nullptr){
		shader->decrementAndDelete();		
	}
	transform = nullptr;
	mesh = nullptr;
	shader = nullptr;
}

void MeshEntity::render(vox::MatrixStack * _matrixStack, RenderOptions * _renderOptions){
	//push transform
	if(_matrixStack != nullptr && _renderOptions != nullptr){
		_matrixStack->pushMatrix();
		_matrixStack->applyMatrix(transform->getModelMatrix());
	
		if(mesh != nullptr){
			mesh->load();
			mesh->clean();
		}
		if(_renderOptions->overrideShader == nullptr){
			_renderOptions->shader = shader;
		}else{
			_renderOptions->shader = _renderOptions->overrideShader;
		}
		if(mesh != nullptr){
			mesh->render(_matrixStack, _renderOptions);
		}
		Entity::render(_matrixStack, _renderOptions);
		//pop transform
		_matrixStack->popMatrix();
	}
}

void MeshEntity::update(Step * _step){
	Entity::update(_step);
}

void MeshEntity::removeChildAtIndex(int _index){
	NodeHierarchical::removeChildAtIndex(_index);
}

void MeshEntity::setShader(Shader * _shader, bool _configureDefaultAttributes){
	if(_shader != nullptr){
		if(_shader->isCompiled){
			shader = _shader;
			if(_configureDefaultAttributes){
				if(mesh != nullptr){
					load();
				}
			}
		}else{
			throw "shader not compiled; cannot setShader";
		}
	}
}

Shader* MeshEntity::getShader(){
	return shader;
}

void MeshEntity::setShaderOnChildren(Shader * _shader){
	for(NodeChild * child : children){
		MeshEntity * me = dynamic_cast<MeshEntity*>(child);
		if(me != nullptr){
			me->setShaderOnChildren(_shader);
		}
	}
	setShader(_shader, true);
}

void MeshEntity::unload(){
	if(loaded){
		if(mesh != nullptr){
			mesh->unload();
		}
		if(shader != nullptr){
			shader->unload();	
		}
	}
	Entity::unload();
}

void MeshEntity::load(){
	if(!loaded){
		if(mesh != nullptr){
			mesh->load();
			mesh->clean();	
		}
	
		if(shader != nullptr){
			shader->load();
			if(mesh != nullptr ){
				mesh->configureDefaultVertexAttributes(shader);
			}
		}
	}
	Entity::load();
}