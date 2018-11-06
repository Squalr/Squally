#include "TextMenuSprite.h"

TextMenuSprite* TextMenuSprite::create(
	Label* normalLabel,
	Label* selectedLabel,
	std::string spriteNormal,
	std::string spriteSelectedResource)
{
	return TextMenuSprite::create(
		normalLabel,
		selectedLabel,
		Sprite::create(spriteNormal),
		Sprite::create(spriteSelectedResource)
	);
}

TextMenuSprite* TextMenuSprite::create(
	Label* normalLabel,
	Label* selectedLabel,
	Node* spriteNormal,
	std::string spriteSelectedResource)
{
	TextMenuSprite* instance = new TextMenuSprite(
		normalLabel,
		selectedLabel,
		spriteNormal, 
		Sprite::create(spriteSelectedResource)
	);

	instance->autorelease();

	return instance;
}

TextMenuSprite* TextMenuSprite::create(
	Label* normalLabel,
	Label* selectedLabel,
	Node* nodeNormal, 
	Node* nodeSelected)
{
	TextMenuSprite* instance = new TextMenuSprite(
		normalLabel,
		selectedLabel,
		nodeNormal,
		nodeSelected);

	instance->autorelease();

	return instance;
}

TextMenuSprite::TextMenuSprite(
	Label* normalLabel,
	Label* selectedLabel,
	Node* nodeNormal,
	Node* nodeSelected) : MenuSprite(nodeNormal, nodeSelected)
{
	this->normalContentLabel = normalLabel;
	this->selectedContentLabel = selectedLabel;
	this->normalContent = nodeNormal;
	this->selectedContent = nodeSelected;

	Vec2 center = this->getContentSize() / 2.0f;

	normalLabel->setPosition(center);
	selectedLabel->setPosition(center);

	this->setCascadeOpacityEnabled(true);

	nodeNormal->addChild(normalLabel);
	nodeSelected->addChild(selectedLabel);
}

TextMenuSprite::~TextMenuSprite()
{
}

void TextMenuSprite::setTextOffset(Vec2 offset)
{
	Vec2 center = this->getContentSize() / 2.0f;

	this->normalContentLabel->setPosition(center + offset);
	this->selectedContentLabel->setPosition(center + offset);
}