#include "PuzzleDoorGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

PuzzleDoorGenericPreview* PuzzleDoorGenericPreview::create()
{
	PuzzleDoorGenericPreview* instance = new PuzzleDoorGenericPreview();

	instance->autorelease();

	return instance;
}

PuzzleDoorGenericPreview::PuzzleDoorGenericPreview()
{
	this->previewSpikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01);

	this->previewSpikedLog->setScale(0.4f);

	this->previewNode->addChild(this->previewSpikedLog);
}

HackablePreview* PuzzleDoorGenericPreview::clone()
{
	return PuzzleDoorGenericPreview::create();
}

void PuzzleDoorGenericPreview::onEnter()
{
	super::onEnter();

	this->previewSpikedLog->setPosition(Vec2(0.0f, 0.0f));
	this->previewSpikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01, 0.08f, 0.0f);
}

void PuzzleDoorGenericPreview::initializePositions()
{
	super::initializePositions();
}
