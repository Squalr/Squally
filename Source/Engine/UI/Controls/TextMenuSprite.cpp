#include "TextMenuSprite.h"

TextMenuSprite* TextMenuSprite::create(
	Label* normalLabel,
	Label* selectedLabel,
	Label* clickedLabel, 
	std::string spriteNormal,
	std::string spriteSelectedResource,
	std::string spriteClickedResource)
{
	return TextMenuSprite::create(
		normalLabel,
		selectedLabel,
		clickedLabel, 
		Sprite::create(spriteNormal),
		Sprite::create(spriteSelectedResource),
		Sprite::create(spriteClickedResource));
}

TextMenuSprite* TextMenuSprite::create(
	Label* normalLabel,
	Label* selectedLabel,
	Label* clickedLabel,
	Node* spriteNormal,
	std::string spriteSelectedResource,
	std::string spriteClickedResource)
{
	TextMenuSprite* instance = new TextMenuSprite(
		normalLabel,
		selectedLabel,
		clickedLabel,
		spriteNormal, 
		Sprite::create(spriteSelectedResource), 
		Sprite::create(spriteClickedResource));

	instance->autorelease();

	return instance;
}

TextMenuSprite* TextMenuSprite::create(
	Label* normalLabel,
	Label* selectedLabel,
	Label* clickedLabel, 
	Node* nodeNormal, 
	Node* nodeSelected, 
	Node* nodeClicked)
{
	TextMenuSprite* instance = new TextMenuSprite(
		normalLabel,
		selectedLabel,
		clickedLabel,
		nodeNormal,
		nodeSelected,
		nodeClicked);

	instance->autorelease();

	return instance;
}

TextMenuSprite::TextMenuSprite(
	Label* normalLabel,
	Label* selectedLabel,
	Label* clickedLabel,
	Node* nodeNormal,
	Node* nodeSelected,
	Node* nodeClicked) : MenuSprite(nodeNormal, nodeSelected, nodeClicked)
{
	this->normalContentLabel = normalLabel;
	this->selectedContentLabel = selectedLabel;
	this->clickedContentLabel = clickedLabel;
	this->normalContent = nodeNormal;
	this->selectedContent = nodeSelected;
	this->clickedContent = nodeClicked;

	Vec2 center = this->getContentSize() / 2.0f;

	normalLabel->setPosition(center);
	selectedLabel->setPosition(center);
	clickedLabel->setPosition(center);

	this->setCascadeOpacityEnabled(true);

	nodeNormal->addChild(normalLabel);
	nodeSelected->addChild(selectedLabel);
	nodeClicked->addChild(clickedLabel);
}

TextMenuSprite::~TextMenuSprite()
{
}

void TextMenuSprite::setTextOffset(Vec2 offset)
{
	Vec2 center = this->getContentSize() / 2.0f;

	this->normalContentLabel->setPosition(center + offset);
	this->selectedContentLabel->setPosition(center + offset);
	this->clickedContentLabel->setPosition(center + offset);
}