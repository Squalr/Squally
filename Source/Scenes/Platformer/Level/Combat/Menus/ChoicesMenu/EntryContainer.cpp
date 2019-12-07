#include "EntryContainer.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

EntryContainer* EntryContainer::create(
		Label* normalLabel,
		Label* selectedLabel, 
		Node* nodeNormal,
		Node* nodeSelected)
{
	EntryContainer* instance = new EntryContainer(
		normalLabel,
		selectedLabel,
		nodeNormal,
		nodeSelected);

	instance->autorelease();

	return instance;
}

EntryContainer::EntryContainer(
	Label* normalLabel,
	Label* selectedLabel, 
	Node* nodeNormal,
	Node* nodeSelected) : super(normalLabel, selectedLabel, nodeNormal, nodeSelected)
{
	this->storedOpacity = 255;
	this->storedEnabled = true;
}

EntryContainer::~EntryContainer()
{
}

void EntryContainer::disable(uint8_t newOpacity)
{
	super::disableInteraction(uint8_t(newOpacity * (float(this->storedOpacity) / 255.0f)));
}

void EntryContainer::enable()
{
	if (this->storedEnabled)
	{
		super::enableInteraction(this->storedOpacity);
	}
	else
	{
		super::disableInteraction(this->storedOpacity);
	}
}

void EntryContainer::disableInteraction(uint8_t newOpacity)
{
	super::disableInteraction(newOpacity);

	this->storedOpacity = newOpacity;
	this->storedEnabled = false;
}

void EntryContainer::enableInteraction(uint8_t newOpacity)
{
	super::enableInteraction(newOpacity);

	this->storedOpacity = newOpacity;
	this->storedEnabled = true;
}
