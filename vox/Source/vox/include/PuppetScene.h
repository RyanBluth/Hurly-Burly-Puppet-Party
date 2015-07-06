#pragma once

#include "LayeredScene.h"

class RandomGround;
class MousePerspectiveCamera;
class PerspectiveCamera;
class FollowCamera;
class MeshEntity;
class PuppetController;
class PuppetCharacter;
class GameJamCharacter;
class Catapult;
class PuppetContactListener;
class DialogHandler;
class AccelerometerParser;
class Box2DMeshEntity;
class Box2DDebugDrawer;
class SpriteSheetAnimation;
class Box2DSprite;
class SoundManager;
class Texture;
class Sprite;
class Box2DWorld;
class CylinderScreen;
class Character;
class TestCharacter;
class Character1;
class Character2;
class Character3;
class Character4;
class PuppetGame;
class Item;
class NodeBox2DBody;
class ParticleSystem;
class StructureBreakable;
class StandardFrameBuffer;
class RenderSurface;
class Shader;

 class PuppetScene abstract : public LayeredScene{
public:
	const float sceneHeight;
	const float sceneWidth;
	float duration;
	float currentTime;
	unsigned int countDown;
	std::vector<Sprite *> countDownNumbers;

	Sprite * splashMessage;
	bool displayingSplash;
	bool splashSoundPlayed;
	bool victoryTriggered;

	float splashDuration;
	float ghostPosition;
	double sceneStart;

	PuppetContactListener * cl;
	Box2DWorld * world;
	Box2DDebugDrawer * drawer;

	std::vector<PuppetCharacter *> players;

	MeshEntity * stageFloor;
	MeshEntity * stageFront;
	MeshEntity * background;
	ComponentShaderBase * shader;

	std::vector<Box2DMeshEntity *> boundaries;

	SoundManager * soundManager;
	SoundManager * countdownSoundManager;
	SoundManager * backgroundSoundManager;

	FollowCamera * gameCam;
	MousePerspectiveCamera * mouseCamera;

	bool mouseCam;

	std::vector<Item *> items;
	std::vector<StructureBreakable *> structures;

    ParticleSystem * particleSystem;

	Shader * screenSurfaceShader;
	RenderSurface * screenSurface;
	StandardFrameBuffer * screenFBO;
	MeshEntity * sun;
	float screenShaderSetting;

	UILayer * uiLayer;

	explicit PuppetScene(PuppetGame * _game, float time, float _width = 170.f, float _height = 50.f, float _size = 100.f, bool _fullCurtains = false);
	virtual ~PuppetScene();

	virtual void load() override;
	virtual void unload() override;
	virtual void update(Step * _step) override;
	virtual void render(vox::MatrixStack* _matrixStack, RenderOptions* _renderOptions) override;
	
	void assignControllers();
	virtual void triggerVictoryState();
    virtual void complete(std::string _switchTo = "");

	void destroyItem(Item * item);
	virtual void doCountDown();
	void playRandomBackgroundMusic();

	virtual void populateBackground();
	virtual void populateClouds();

	static bool comparePuppetId(PuppetCharacter * p1, PuppetCharacter * p2);
};