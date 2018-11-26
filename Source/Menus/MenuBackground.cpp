#include "MenuBackground.h"

MenuBackground* MenuBackground::menuBackgroundInstance = nullptr;

MenuBackground* MenuBackground::claimInstance()
{
	MenuBackground* mouse = MenuBackground::getInstance();

	// Free the background from it's parent
	if (mouse->getParent() != nullptr)
	{
		mouse->getParent()->removeChild(MenuBackground::menuBackgroundInstance);
	}

	return MenuBackground::menuBackgroundInstance;
}

MenuBackground* MenuBackground::getInstance()
{
	if (menuBackgroundInstance == nullptr)
	{
		MenuBackground::menuBackgroundInstance = new MenuBackground();
	}

	return MenuBackground::menuBackgroundInstance;
}

MenuBackground::MenuBackground()
{
	this->background = Sprite::create(UIResources::Menus_Backgrounds_DarkBackground);
	this->fog = InfiniteParallaxNode::create(UIResources::Menus_Backgrounds_Fog);
	this->foregroundFog = InfiniteParallaxNode::create(UIResources::Menus_Backgrounds_Fog);
	this->backgroundTrees = FloatingSprite::create(UIResources::Menus_Backgrounds_LightTrees, Vec2(-24.0f, 8.0f), Vec2(7.0f, 5.0f));
	this->midgroundTrees = FloatingSprite::create(UIResources::Menus_Backgrounds_MidgroundTrees2, Vec2(16.0f, -8.0f), Vec2(7.0f, 5.0f));
	this->webs = Sprite::create(UIResources::Menus_Backgrounds_Webs);
	this->foregroundVines = FloatingSprite::create(UIResources::Menus_Backgrounds_Vines, Vec2(-24.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassBottom = FloatingSprite::create(UIResources::Menus_Backgrounds_BottomSoil, Vec2(-8.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundGrassTop = FloatingSprite::create(UIResources::Menus_Backgrounds_TopLeaves, Vec2(-32.0f, 0.0f), Vec2(7.0f, 5.0f));
	this->foregroundLight = Sprite::create(UIResources::Menus_Backgrounds_Light);

	this->windParticles = ParticleSystemQuad::create(ParticleResources::Wind);
	this->fireflyParticles = ParticleSystemQuad::create(ParticleResources::Fireflies2);

	this->fog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-92.0f, 0))));
	this->foregroundFog->runAction(RepeatForever::create(MoveBy::create(2.0f, Vec2(-196.0f, 0))));

	this->addChild(this->background);
	this->addChild(this->backgroundTrees);
	this->addChild(this->midgroundTrees);
	this->addChild(this->webs);
	this->addChild(this->fog);
	this->addChild(this->foregroundVines);
	this->addChild(this->fireflyParticles);
	this->addChild(this->windParticles);
	this->addChild(this->foregroundFog);
	this->addChild(this->foregroundGrassBottom);
	this->addChild(this->foregroundGrassTop);
	this->addChild(this->foregroundLight);
}

MenuBackground::~MenuBackground()
{
}

void MenuBackground::initializePositions()
{
	SmartNode::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->backgroundTrees->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 320.0f));
	this->webs->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 32.0f));
	this->midgroundTrees->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	this->fog->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 120.0f));
	this->foregroundFog->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 256.0f));
	this->foregroundVines->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 196.0f));
	this->foregroundGrassBottom->setPosition(Vec2(visibleSize.width / 2, 72.0f));
	this->foregroundGrassTop->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 32.0f));
	this->foregroundLight->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - foregroundLight->getContentSize().height / 2));
	this->windParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
	this->fireflyParticles->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
}
