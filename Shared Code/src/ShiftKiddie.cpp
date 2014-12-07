#pragma once

#include "ShiftKiddie.h"

#include "Transform.h"
#include "NodeHierarchical.h"

ShiftKiddie::ShiftKiddie() :
	NodeChild(nullptr),
	NodeTransformable(nullptr)
{
}

glm::vec3 ShiftKiddie::getPos(bool _relative){
	glm::vec4 res(transform->translationVector.x, transform->translationVector.y, transform->translationVector.z, 1);
	if(!_relative){
		NodeParent * _parent = parent;
		std::vector<glm::mat4> modelMatrixStack;
		while (_parent != nullptr){
			NodeHierarchical * ph = dynamic_cast<NodeHierarchical *>(_parent);
			NodeTransformable * pt = dynamic_cast<NodeTransformable *>(_parent);
			if(pt != NULL){
				modelMatrixStack.push_back(pt->transform->getModelMatrix());
			}
			if (ph != NULL){
				_parent = ph->parent;
			}else{
				break;
			}
		}
		
		glm::mat4 modelMatrix(1);
		for(unsigned long int i = modelMatrixStack.size(); i > 0; --i){
			modelMatrix = modelMatrix * modelMatrixStack.at(i-1);
		}
		res = modelMatrix * res;
	}
	return glm::vec3(res);
}

void ShiftKiddie::setPos(glm::vec3 _pos, bool _convertToRelative){
	glm::vec4 newPos(_pos, 1);
	if(_convertToRelative){
		NodeParent * _parent = parent;
		std::vector<glm::mat4> modelMatrixStack;
		while(_parent != nullptr){
			NodeHierarchical * t = dynamic_cast<NodeHierarchical *>(_parent);
			if (t != NULL){
				modelMatrixStack.push_back(dynamic_cast<NodeTransformable *>(_parent)->transform->getModelMatrix());
				_parent = t->parent;
			}else{
				break;
			}
		}

		glm::mat4 modelMatrix(1);
		for(unsigned long int i = modelMatrixStack.size(); i > 0; --i){
			modelMatrix = modelMatrix * modelMatrixStack.at(i-1);
		}
		newPos = glm::inverse(modelMatrix) * newPos;
	}
	transform->translationVector = glm::vec3(newPos.x, newPos.y, newPos.z);
}