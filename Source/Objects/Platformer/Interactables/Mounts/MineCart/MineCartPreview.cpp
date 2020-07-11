#include "MineCartPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MineCartPreview* MineCartPreview::create()
{
	MineCartPreview* instance = new MineCartPreview();

	instance->autorelease();

	return instance;
}

MineCartPreview::MineCartPreview()
{
	this->previewCart = Sprite::create(ObjectResources::Interactive_MineCarts_Body1);

	this->previewCart->setScale(0.35f);

	this->previewNode->addChild(this->previewCart);
}

HackablePreview* MineCartPreview::clone()
{
	return MineCartPreview::create();
}

void MineCartPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	/*
	this->previewCart->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
	*/
}

void MineCartPreview::initializePositions()
{
	super::initializePositions();

	this->previewCart->setPosition(Vec2(0.0f, 0.0f));
}
