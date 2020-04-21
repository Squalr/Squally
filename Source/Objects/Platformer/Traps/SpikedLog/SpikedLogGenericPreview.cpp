#include "SpikedLogGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

SpikedLogGenericPreview* SpikedLogGenericPreview::create()
{
	SpikedLogGenericPreview* instance = new SpikedLogGenericPreview();

	instance->autorelease();

	return instance;
}

SpikedLogGenericPreview::SpikedLogGenericPreview()
{
	this->previewSpikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikedLog_SpikedLog_00);

	this->previewSpikedLog->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikedLog);
}

SpikedLogGenericPreview::~SpikedLogGenericPreview()
{
}

HackablePreview* SpikedLogGenericPreview::clone()
{
	return SpikedLogGenericPreview::create();
}

void SpikedLogGenericPreview::onEnter()
{
	super::onEnter();

	this->previewSpikedLog->setPosition(Vec2(0.0f, 0.0f));
	this->previewSpikedLog->playAnimationRepeat(ObjectResources::Traps_SpikedLog_SpikedLog_00, 0.08f, 0.0f);
}

void SpikedLogGenericPreview::initializePositions()
{
	super::initializePositions();
}
