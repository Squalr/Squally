#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/InfiniteParallaxNode.h"

using namespace cocos2d;

class PauseMenu : public Scene
{
public:
	static PauseMenu * create();

protected:
	PauseMenu();
	~PauseMenu();

private:
	void onEnter() override;
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnExitGame(Ref* pSender);

	MenuItemImage* closeItem;

	Sprite* background;
	Sprite* backgroundVines;
	Sprite* backgroundTrees;
	Sprite* midgroundTrees;
	Sprite* foregroundVines;
	InfiniteParallaxNode* fog;
	InfiniteParallaxNode* foregroundFog;
	Sprite* foregroundGrassBottom;
	Sprite* foregroundGrassTop;
	Sprite* foregroundLight;
	ParticleSystem* matrixParticles;
	ParticleSystem* windParticles;
	ParticleSystem* fireflyParticles;

	Sprite* pauseWindow;

	ParticleSystem* fireflies;
};

