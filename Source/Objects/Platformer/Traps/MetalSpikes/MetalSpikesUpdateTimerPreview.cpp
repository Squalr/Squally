#include "MetalSpikesUpdateTimerPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

MetalSpikesUpdateTimerPreview* MetalSpikesUpdateTimerPreview::create()
{
	MetalSpikesUpdateTimerPreview* instance = new MetalSpikesUpdateTimerPreview();

	instance->autorelease();

	return instance;
}

MetalSpikesUpdateTimerPreview::MetalSpikesUpdateTimerPreview()
{
	this->launchCountDown = 0.0f;
	this->previewSpikes = SmartAnimationSequenceNode::create(ObjectResources::Traps_MetalSpikes_Spikes_0000);
	this->xmm2TimerStr = ConstantString::create(std::to_string(this->launchCountDown));
	this->xmm2Timer = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm2, false, this->xmm2TimerStr);
	this->isLaunching = false;

	this->xmm2Timer->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->previewSpikes->setScale(0.4f);

	this->assemblyTextNode->addChild(this->xmm2Timer);
	this->previewNode->addChild(this->previewSpikes);
}

MetalSpikesUpdateTimerPreview::~MetalSpikesUpdateTimerPreview()
{
}

HackablePreview* MetalSpikesUpdateTimerPreview::clone()
{
	return MetalSpikesUpdateTimerPreview::create();
}

void MetalSpikesUpdateTimerPreview::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void MetalSpikesUpdateTimerPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 24.0f;
	
	this->xmm2Timer->setPosition(Vec2(0.0f, -80.0f));
}

void MetalSpikesUpdateTimerPreview::update(float dt)
{
	super::update(dt);

	this->launchCountDown = MathUtils::clamp(this->launchCountDown - dt, 0.0f, 4.0f);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->launchCountDown;
	std::string s = stream.str();

	this->xmm2TimerStr->setString(stream.str());
	
	if (!this->isLaunching && this->launchCountDown <= 0)
	{
		this->isLaunching = true;

		this->previewSpikes->playAnimationAndReverse(ObjectResources::Traps_MetalSpikes_Spikes_0000, 0.025f, 1.5f, 0.025f);

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
