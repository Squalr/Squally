#include "Background.h"

#include "Engine/UI/HUD/Hud.h"

using namespace cocos2d;

Background* Background::create(Node* child)
{
	Background* instance = new Background(child);

	instance->autorelease();

	return instance;
}

Background::Background(Node* child) : super()
{
	this->background = Hud::create();

	if (child != nullptr)
	{
		child->setAnchorPoint(Vec2::ZERO);

		this->background->addChild(child);
	}

	this->addChild(this->background);
}

Background::~Background()
{
}
