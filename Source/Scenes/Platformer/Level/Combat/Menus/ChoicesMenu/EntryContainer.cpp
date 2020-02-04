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
}

EntryContainer::~EntryContainer()
{
}
