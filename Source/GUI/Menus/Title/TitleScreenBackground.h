#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"
#include "GUI/Menus/Title/HackerMode.h"
#include "GUI/Menus/Tutorial/TutorialScreen.h"
#include "GUI/Components/FloatingSprite.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/InfiniteParallaxNode.h"

using namespace cocos2d;
using namespace experimental;

class TitleScreenBackground : public Node
{
public:
	static TitleScreenBackground * create();

	void SetMatrixClickCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick);
	void InitializePositions();

private:
	TitleScreenBackground();
	~TitleScreenBackground();

	void InitializeListeners();
	void OnHackerModeEnabled(EventCustom* args);

	FloatingSprite * squally;
	Sprite* background;
	FloatingSprite* backgroundVines;
	FloatingSprite* backgroundTrees;
	FloatingSprite* midgroundTrees;
	Sprite* tree;
	Animation* eyes1Anim;
	Animation* eyes2Anim;
	Sprite* eyes1;
	Sprite* eyes2;
	FloatingSprite* foregroundVines;
	InfiniteParallaxNode* fog;
	InfiniteParallaxNode* foregroundFog;
	FloatingSprite* foregroundGrassBottom;
	FloatingSprite* foregroundGrassTop;
	Sprite* foregroundLight;

	ParticleSystem* etherParticles;
	ParticleSystem* windParticles;
	ParticleSystem* fireflyParticles;

	MenuSprite* ether;

	Label* hackerModeLabel;
};
