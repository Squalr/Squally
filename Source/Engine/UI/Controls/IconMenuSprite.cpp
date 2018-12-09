#include "IconMenuSprite.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

IconMenuSprite* IconMenuSprite::create(
	std::string normalSprite,
	std::string selectedSprite,
	std::string spriteNormal,
	std::string spriteSelectedResource)
{
	return IconMenuSprite::create(
		Sprite::create(normalSprite),
		Sprite::create(selectedSprite),
		Sprite::create(spriteNormal),
		Sprite::create(spriteSelectedResource)
	);
}

IconMenuSprite* IconMenuSprite::create(
	Sprite* normalSprite,
	Sprite* selectedSprite,
	std::string spriteNormal,
	std::string spriteSelectedResource)
{
	return IconMenuSprite::create(
		normalSprite,
		selectedSprite,
		Sprite::create(spriteNormal),
		Sprite::create(spriteSelectedResource)
	);
}

IconMenuSprite* IconMenuSprite::create(
	Sprite* normalSprite,
	Sprite* selectedSprite,
	Node* nodeNormal,
	Node* nodeSelected)
{
	IconMenuSprite* instance = new IconMenuSprite(
		normalSprite,
		selectedSprite,
		nodeNormal,
		nodeSelected);

	instance->autorelease();

	return instance;
}

IconMenuSprite::IconMenuSprite(
	Sprite* normalSprite,
	Sprite* selectedSprite,
	Node* nodeNormal,
	Node* nodeSelected) : MenuSprite(nodeNormal, nodeSelected)
{
	this->normalContentSprite = normalSprite;
	this->selectedContentSprite = selectedSprite;

	Vec2 center = this->getContentSize() / 2.0f;

	this->normalContentSprite->setPosition(center);
	this->selectedContentSprite->setPosition(center);

	this->sprite->addChild(this->normalContentSprite);
	this->spriteSelected->addChild(this->selectedContentSprite);
}

IconMenuSprite::~IconMenuSprite()
{
}

void IconMenuSprite::setIconOffset(Vec2 offset)
{
	Vec2 center = this->getContentSize() / 2.0f;

	this->normalContentSprite->setPosition(center + offset);
	this->selectedContentSprite->setPosition(center + offset);
}