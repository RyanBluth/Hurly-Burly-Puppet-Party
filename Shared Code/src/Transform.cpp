#pragma once

#include "Transform.h"

Transform::Transform():
	translationVector(0.f, 0.f, 0.f),
	scaleVector(1.f, 1.f, 1.f),
	orientation(1.f, 0.f, 0.f, 0.f),
	NodeHierarchical(nullptr)
{
}

Transform::~Transform(){
}

void Transform::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix){
	for(unsigned long int i = 0; i < children.size(); ++i){
		dynamic_cast<Transform *>(children.at(i))->draw(projectionMatrix, viewMatrix);
	}
}

void Transform::update(){
}

void Transform::scale(float _scaleX, float _scaleY, float _scaleZ){
	scaleVector.x *= _scaleX;
	scaleVector.y *= _scaleY;
	scaleVector.z *= _scaleZ;
}

void Transform::scale(glm::vec3 _scale){
	scaleVector *= _scale;
}

void Transform::scaleX(float _scaleX){
	scaleVector.x *= _scaleX;
}

void Transform::scaleY(float _scaleY){
	scaleVector.y *= _scaleY;
}

void Transform::scaleZ(float _scaleZ){
	scaleVector.z *= _scaleZ;
}

void Transform::translate(float _translateX, float _translateY, float _translateZ){
	translationVector.x += _translateX;
	translationVector.y += _translateY;
	translationVector.z += _translateZ;
}

void Transform::translate(glm::vec3 _translate){
	translationVector += _translate;
}

void Transform::translateX(float _translateX){
	translationVector.x += _translateX;
}

void Transform::translateY(float _translateY){
	translationVector.y += _translateY;
}

void Transform::translateZ(float _translateZ){
	translationVector.z += _translateZ;
}

void Transform::rotate(glm::quat _rotation, bool _local){
	if(_local){
		orientation = orientation * _rotation;
	}else{
		orientation = _rotation * orientation;
	}
}

void Transform::rotate(float _angle, float _x, float _y, float _z, bool _local){
	this->rotate(glm::quat(glm::angleAxis(_angle, glm::vec3(_x, _y, _z))), _local);
}

glm::mat4 Transform::getTranslationMatrix(){
	return glm::translate(translationVector);
}

glm::mat4 Transform::getScaleMatrix(){
	return glm::scale(scaleVector);
}

glm::mat4 Transform::getOrientationMatrix(){
	return glm::toMat4(orientation);
}

glm::mat4 Transform::getModelMatrix(){
	return getTranslationMatrix() * getOrientationMatrix() * getScaleMatrix();
}

void Transform::addChild(Transform * _child){
	_child->setParent(this);
	children.push_back(_child);
}

void Transform::removeChildAtIndex(int _index){
	children.erase(children.begin()+_index-1);
}

void Transform::setParent(Transform * _parent){
	this->parent = _parent;
}