#include "CatapultGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

CatapultGenericPreview* CatapultGenericPreview::create()
{
	CatapultGenericPreview* instance = new CatapultGenericPreview();

	instance->autorelease();

	return instance;
}

CatapultGenericPreview::CatapultGenericPreview()
{
	this->previewCatapult = SmartAnimationNode::create(ObjectResources::Traps_Catapult_Animations);

	this->previewCatapult->setScale(0.35f);

	this->previewNode->addChild(this->previewCatapult);
}

CatapultGenericPreview::~CatapultGenericPreview()
{
}

HackablePreview* CatapultGenericPreview::clone()
{
	return CatapultGenericPreview::create();
}

void CatapultGenericPreview::onEnter()
{
	super::onEnter();
}

void CatapultGenericPreview::initializePositions()
{
	super::initializePositions();

	this->previewCatapult->setPosition(Vec2(0.0f, -48.0f));
}
