#pragma once

#include "Box2DDebugDraw.h"
#include "Scene.h"
#include "Sprite.h"
#include "SpriteMesh.h"
#include "shader/BaseComponentShader.h"
#include "shader/ShaderComponentTexture.h"

#include "GameJamScene.h"
#include "Box2DWorld.h"

#include "MatrixStack.h"

#include <GL/glew.h>

Box2DDebugDraw::Box2DDebugDraw(Scene * _scene, Box2DWorld * _world):
	shader(new BaseComponentShader()),
	scene(_scene),
	world(_world),
	spriteSegment(new Sprite()),
	spriteTransform(new Sprite()),
	spriteCircle(new Sprite()),
	spritePoly(new Sprite()),
	NodeTransformable(new Transform()),
	NodeChild(nullptr),
	drawing(false)
{
	shader->components.push_back(new ShaderComponentTexture(shader));
	shader->compileShader();
	
	
	spriteSegment->mesh->vertices.clear();
	spriteSegment->mesh->indices.clear();
	spriteSegment->mesh->polygonalDrawMode = GL_LINES;
	spriteSegment->mesh->pushVert(Vertex(0, 0, 0.0001f, 0, 0, 1.f, 1.f));
	spriteSegment->mesh->pushVert(Vertex(1, 0, 0.0001f, 0, 0, 1.f, 1.f));

	
	spriteTransform->mesh->vertices.clear();
	spriteTransform->mesh->indices.clear();
	spriteTransform->mesh->polygonalDrawMode = GL_LINES;
	spriteTransform->mesh->pushVert(Vertex(0, 0, 0.0001f, 255, 0, 0, 1.f));
	spriteTransform->mesh->pushVert(Vertex(1, 0, 0.0001f, 255, 0, 0, 1.f));
	spriteTransform->mesh->pushVert(Vertex(0, 0, 0.0001f, 0, 255, 0, 1.f));
	spriteTransform->mesh->pushVert(Vertex(0, 1, 0.0001f, 0, 255, 0, 1.f));

	
	spriteCircle->mesh->polygonalDrawMode = GL_POLYGON;
	spriteCircle->mesh->vertices.clear();
	spriteCircle->mesh->indices.clear();
	for (int32 i = 0; i < 30; ++i){
		float percent = (i / static_cast<float>(30-1));
		float rad = percent * 2 * 3.14159f;
		float x = cos(rad);
		float y = sin(rad);
		spriteCircle->mesh->pushVert(Vertex(x, y, 0.0001f, 0, 1.f, 1.f, 1.f));
	}
	
	spriteSegment->setShader(shader, true);
	spriteTransform->setShader(shader, true);
	spriteCircle->setShader(shader, true);
	spritePoly->setShader(shader, true);

	addChild(spriteSegment);
	addChild(spriteTransform);
	addChild(spriteCircle);
	addChild(spritePoly);
}

Box2DDebugDraw::~Box2DDebugDraw(){
	delete spriteSegment;
	delete spriteTransform;
	delete spriteCircle;
	delete spritePoly;
	delete shader;
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
	spritePoly->mesh->vertices.clear();
	spritePoly->mesh->indices.clear();
	spritePoly->mesh->polygonalDrawMode = GL_LINE_STRIP;

	for (int32 i = 0; i < vertexCount; ++i) {
		spritePoly->mesh->pushVert(Vertex(vertices[i].x, vertices[i].y, 0.0001f, color.r, color.g, color.b, 1.f));
	}
	spritePoly->mesh->indices.push_back(0);

	spritePoly->render(scene->matrixStack, scene->renderOptions);
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color& color){
	spritePoly->mesh->vertices.clear();
	spritePoly->mesh->indices.clear();
	spritePoly->mesh->polygonalDrawMode = GL_LINE_STRIP;
	
	for (int32 i = 0; i < vertexCount; ++i) {
		spritePoly->mesh->pushVert(Vertex(vertices[i].x, vertices[i].y, 0.0001f, color.r, color.g, color.b, 1.f));
	}
	spritePoly->mesh->indices.push_back(0);

	spritePoly->render(scene->matrixStack, scene->renderOptions);
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color){
	spriteCircle->mesh->polygonalDrawMode = GL_LINE_STRIP;//GL_POLYGON;
	spriteCircle->transform->translate(glm::vec3(center.x, center.y, 0), false);
	spriteCircle->transform->scale(glm::vec3(radius, radius, radius), false);
	spriteCircle->render(scene->matrixStack, scene->renderOptions);
}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){
	spriteCircle->mesh->polygonalDrawMode = GL_LINE_STRIP;//GL_POLYGON;
	spriteCircle->transform->translate(glm::vec3(center.x, center.y, 0), false);
	spriteCircle->transform->scale(glm::vec3(radius, radius, radius), false);
	spriteCircle->render(scene->matrixStack, scene->renderOptions);
}

void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
	spriteSegment->transform->translate(glm::vec3(p1.x, p1.y, 0), false);
	float x = p2.x - p1.x;
	float y = p2.y - p1.y;
	float mag = sqrt(x*x + y*y);
	spriteSegment->transform->setOrientation(glm::quat(glm::angleAxis(glm::degrees(atan2(y, x)), glm::vec3(0, 0, 1))));
	spriteSegment->transform->scale(glm::vec3(mag, mag, mag), false);
	spriteSegment->render(scene->matrixStack, scene->renderOptions);
}

void Box2DDebugDraw::DrawTransform(const b2Transform& xf){
	spriteTransform->transform->translate(xf.p.x, xf.p.y, 0, false);
	spriteTransform->transform->setOrientation(glm::quat(glm::angleAxis(glm::degrees(xf.q.GetAngle()), glm::vec3(0, 0, 1))));
	spriteTransform->render(scene->matrixStack, scene->renderOptions);
}

void Box2DDebugDraw::render(vox::MatrixStack * _matrixStack, RenderOptions * _renderOptions){
	glLineWidth(2.5f);
	if(drawing){
		world->b2world->DrawDebugData();
	}
}

void Box2DDebugDraw::load(){
	spriteTransform->load();
	spriteCircle->load();
	spritePoly->load();
	spriteSegment->load();
}

void Box2DDebugDraw::unload(){
	spriteTransform->unload();
	spriteCircle->unload();
	spritePoly->unload();
	spriteSegment->unload();
}