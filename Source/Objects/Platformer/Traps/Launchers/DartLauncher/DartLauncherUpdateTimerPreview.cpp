#include "DartLauncherUpdateTimerPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantFloat.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ObjectResources.h"


using namespace cocos2d;

DartLauncherUpdateTimerPreview* DartLauncherUpdateTimerPreview::create()
{
	DartLauncherUpdateTimerPreview* instance = new DartLauncherUpdateTimerPreview();

	instance->autorelease();

	return instance;
}

DartLauncherUpdateTimerPreview::DartLauncherUpdateTimerPreview()
{
	this->launchCountDown = 0.0f;
	this->dartLauncher = Sprite::create(ObjectResources::Traps_DartLauncher_CANON);
	this->dart = Sprite::create(ObjectResources::Traps_DartTripodLauncher_DART);
	this->eaxTimerStr = ConstantFloat::create(this->launchCountDown);
	this->eaxTimer = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, this->eaxTimerStr);
	this->isLaunching = false;

	this->eaxTimer->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->dart->setRotation(90.0f);

	this->assemblyTextNode->addChild(this->eaxTimer);
	this->previewNode->addChild(this->dart);
	this->previewNode->addChild(this->dartLauncher);
}

DartLauncherUpdateTimerPreview::~DartLauncherUpdateTimerPreview()
{
}

HackablePreview* DartLauncherUpdateTimerPreview::clone()
{
	return DartLauncherUpdateTimerPreview::create();
}

void DartLauncherUpdateTimerPreview::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void DartLauncherUpdateTimerPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 24.0f;

	this->dart->setPosition(Vec2(24.0f, 64.0f));
	this->dartLauncher->setPosition(Vec2(24.0f, 64.0f));
	this->eaxTimer->setPosition(Vec2(-80.0f, 0.0f));
}

void DartLauncherUpdateTimerPreview::update(float dt)
{
	super::update(dt);

	this->launchCountDown = MathUtils::clamp(this->launchCountDown - dt, 0.0f, 4.0f);

	this->eaxTimerStr->setValue(this->launchCountDown);
	
	if (!this->isLaunching && this->launchCountDown <= 0.0f)
	{
		this->isLaunching = true;

		this->dart->runAction(MoveTo::create(1.0f, Vec2(24.0f, -128.0f)));
		this->dart->runAction(Sequence::create(
			DelayTime::create(0.5f),
			FadeTo::create(0.5f, 0),
			DelayTime::create(0.6f),
			CallFunc::create([=]()
			{
				this->dart->setPosition(Vec2(24.0f, 64.0f));
				this->dart->setOpacity(255);
				this->launchCountDown = RandomHelper::random_real(3.0f, 4.0f);
				this->isLaunching = false;
			}),
			DelayTime::create(0.1f),
			nullptr
		));
	}
}
