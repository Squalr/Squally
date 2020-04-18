#include "WoodenSpikesUpdateTimerPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

WoodenSpikesUpdateTimerPreview* WoodenSpikesUpdateTimerPreview::create()
{
	WoodenSpikesUpdateTimerPreview* instance = new WoodenSpikesUpdateTimerPreview();

	instance->autorelease();

	return instance;
}

WoodenSpikesUpdateTimerPreview::WoodenSpikesUpdateTimerPreview()
{
	this->launchCountDown = 0.0f;
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_WoodenSpikes_Spikes_0000);
	this->ebxTimerStr = ConstantString::create(std::to_string(this->launchCountDown));
	this->ebxTimer = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, this->ebxTimerStr);
	this->isLaunching = false;

	this->ebxTimer->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->previewSpikes->setScale(0.4f);

	this->assemblyTextNode->addChild(this->ebxTimer);
	this->previewNode->addChild(this->previewSpikes);
}

WoodenSpikesUpdateTimerPreview::~WoodenSpikesUpdateTimerPreview()
{
}

HackablePreview* WoodenSpikesUpdateTimerPreview::clone()
{
	return WoodenSpikesUpdateTimerPreview::create();
}

void WoodenSpikesUpdateTimerPreview::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void WoodenSpikesUpdateTimerPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 24.0f;
	
	this->ebxTimer->setPosition(Vec2(0.0f, -80.0f));
}

void WoodenSpikesUpdateTimerPreview::update(float dt)
{
	super::update(dt);

	this->launchCountDown = MathUtils::clamp(this->launchCountDown - dt, 0.0f, 4.0f);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->launchCountDown;
	std::string s = stream.str();

	this->ebxTimerStr->setString(stream.str());
	
	if (!this->isLaunching && this->launchCountDown <= 0)
	{
		this->isLaunching = true;

		this->previewSpikes->playAnimationAndReverse(ObjectResources::Traps_WoodenSpikes_Spikes_0000, 0.025f, 1.5f, 0.025f);

		this->runAction(Sequence::create(
			DelayTime::create(2.5f),
			CallFunc::create([=]()
			{
				this->launchCountDown = RandomHelper::random_real(3.0f, 4.0f);
				this->isLaunching = false;
			}),
			nullptr
		));
	}
}
