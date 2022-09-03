#include "SpikedLogRailedGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

SpikedLogRailedGenericPreview* SpikedLogRailedGenericPreview::create()
{
	SpikedLogRailedGenericPreview* instance = new SpikedLogRailedGenericPreview();

	instance->autorelease();

	return instance;
}

SpikedLogRailedGenericPreview::SpikedLogRailedGenericPreview()
{
	this->previewSpikedLogRailed = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00);

	this->previewSpikedLogRailed->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikedLogRailed);
}

SpikedLogRailedGenericPreview::~SpikedLogRailedGenericPreview()
{
}

HackablePreview* SpikedLogRailedGenericPreview::clone()
{
	return SpikedLogRailedGenericPreview::create();
}

void SpikedLogRailedGenericPreview::onEnter()
{
	super::onEnter();

	this->previewSpikedLogRailed->setPosition(Vec2(0.0f, 0.0f));
	this->previewSpikedLogRailed->playAnimationRepeat(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00, 0.08f, 0.0f);
}

void SpikedLogRailedGenericPreview::initializePositions()
{
	super::initializePositions();
}
