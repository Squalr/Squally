#include "MechanicalFlailGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MechanicalFlailGenericPreview* MechanicalFlailGenericPreview::create()
{
	MechanicalFlailGenericPreview* instance = new MechanicalFlailGenericPreview();

	instance->autorelease();

	return instance;
}

MechanicalFlailGenericPreview::MechanicalFlailGenericPreview()
{
	this->previewFlail = Sprite::create(ObjectResources::Traps_MechanicalFlail_PreviewFlail);
	this->previewJoint = Sprite::create(ObjectResources::Traps_MechanicalFlail_PreviewJoint);

	this->previewFlail->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->previewNode->addChild(this->previewFlail);
	this->previewNode->addChild(this->previewJoint);
}

MechanicalFlailGenericPreview::~MechanicalFlailGenericPreview()
{
}

HackablePreview* MechanicalFlailGenericPreview::clone()
{
	return MechanicalFlailGenericPreview::create();
}

void MechanicalFlailGenericPreview::onEnter()
{
	super::onEnter();

	this->previewFlail->setRotation(45.0f);

	this->previewFlail->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(RotateTo::create(1.5f, 315.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 45.0f)),
			nullptr
		))
	);
}

void MechanicalFlailGenericPreview::initializePositions()
{
	super::initializePositions();
}
