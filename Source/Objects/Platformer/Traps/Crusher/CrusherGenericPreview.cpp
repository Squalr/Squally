#include "CrusherGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

CrusherGenericPreview* CrusherGenericPreview::create()
{
	CrusherGenericPreview* instance = new CrusherGenericPreview();

	instance->autorelease();

	return instance;
}

CrusherGenericPreview::CrusherGenericPreview()
{
	this->previewCrusher = Sprite::create(ObjectResources::Traps_SpikedCrusher_Pole);

	this->previewCrusher->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewCrusher);
}

CrusherGenericPreview::~CrusherGenericPreview()
{
}

HackablePreview* CrusherGenericPreview::clone()
{
	return CrusherGenericPreview::create();
}

void CrusherGenericPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewCrusher->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}

void CrusherGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->previewCrusher->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
}
