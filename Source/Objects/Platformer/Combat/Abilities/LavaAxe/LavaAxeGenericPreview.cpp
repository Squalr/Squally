#include "LavaAxeGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

LavaAxeGenericPreview* LavaAxeGenericPreview::create()
{
	LavaAxeGenericPreview* instance = new LavaAxeGenericPreview();

	instance->autorelease();

	return instance;
}

LavaAxeGenericPreview::LavaAxeGenericPreview()
{
	this->axe = Sprite::create(ObjectResources::Physics_LavaAxe_LavaAxe);

	this->axe->setScale(0.05f);

	this->previewNode->addChild(this->axe);
}

LavaAxeGenericPreview::~LavaAxeGenericPreview()
{
}

HackablePreview* LavaAxeGenericPreview::clone()
{
	return LavaAxeGenericPreview::create();
}

void LavaAxeGenericPreview::onEnter()
{
	super::onEnter();
}

void LavaAxeGenericPreview::initializePositions()
{
	super::initializePositions();
}
