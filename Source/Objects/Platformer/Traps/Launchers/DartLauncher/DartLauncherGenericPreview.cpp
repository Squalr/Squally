#include "DartLauncherGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

DartLauncherGenericPreview* DartLauncherGenericPreview::create()
{
	DartLauncherGenericPreview* instance = new DartLauncherGenericPreview();

	instance->autorelease();

	return instance;
}

DartLauncherGenericPreview::DartLauncherGenericPreview()
{
	this->dartLauncher = Sprite::create(ObjectResources::Traps_DartLauncher_CANON);
	this->dart = Sprite::create(ObjectResources::Traps_DartTripodLauncher_DART);

	this->dart->setRotation(90.0f);

	this->previewNode->addChild(this->dart);
	this->previewNode->addChild(this->dartLauncher);
}

DartLauncherGenericPreview::~DartLauncherGenericPreview()
{
}

HackablePreview* DartLauncherGenericPreview::clone()
{
	return DartLauncherGenericPreview::create();
}

void DartLauncherGenericPreview::onEnter()
{
	super::onEnter();

	this->dart->runAction(
		RepeatForever::create(Sequence::create(
			CallFunc::create([=]()
			{
				this->dart->runAction(MoveTo::create(1.0f, Vec2(0.0f, -128.0f)));
			}),
			DelayTime::create(0.5f),
			FadeTo::create(0.5f, 0),
			DelayTime::create(0.6f),
			CallFunc::create([=]()
			{
				this->dart->setPosition(Vec2(0.0f, 64.0f));
				this->dart->setOpacity(255);
			}),
			DelayTime::create(0.1f),
			nullptr
		))
	);
}

void DartLauncherGenericPreview::initializePositions()
{
	super::initializePositions();

	this->dartLauncher->setPosition(Vec2(0.0f, 64.0f));
}
