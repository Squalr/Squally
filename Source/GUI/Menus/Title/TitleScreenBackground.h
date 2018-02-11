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

	void setMatrixClickCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick);
	void initializePositions();

private:
	TitleScreenBackground();
	~TitleScreenBackground();

	void onEnter() override;
	void initializeListeners();
	void onHackerModeEnabled(EventCustom* args);
	void createSlimeAnimation();

	Node* squallyNode;
	Sprite* spellEffect;
	Sprite* squally;
	Sprite* squallyWand;
	Node* slimeNode;
	Sprite* slimeBubble;
	Sprite* slime;
	Animation* slimeAnimation;
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
