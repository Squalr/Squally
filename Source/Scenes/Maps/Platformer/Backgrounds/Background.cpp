#include "Background.h"

#include "Engine/UI/HUD/Hud.h"

using namespace cocos2d;

Background* Background::create(ValueMap* initProperties, std::string name, Node* child)
{
	Background* instance = new Background(initProperties, name, child);

	instance->autorelease();

	return instance;
}

Background::Background(ValueMap* properties, std::string name, Node* child) : SerializableLayer(properties, name)
{
	this->background = Hud::create();

	child->setAnchorPoint(Vec2::ZERO);

	this->background->addChild(child);
	this->addChild(this->background);
}

Background::~Background()
{
}
