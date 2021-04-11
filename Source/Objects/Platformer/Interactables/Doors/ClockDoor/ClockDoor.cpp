#include "ClockDoor.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Particles/SmartParticles.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ClockDoor::MapKey = "clock-door";
const std::string ClockDoor::PropertyClockStyle = "clock-style";
const std::string ClockDoor::ClockStyleHaunted = "haunted";
const Color4B ClockDoor::BaseColor = Color4B::BLACK;
const Size ClockDoor::ClipSize = Size(204.0f, 352.0f);

ClockDoor* ClockDoor::create(ValueMap& properties)
{
	ClockDoor* instance = new ClockDoor(properties);

	instance->autorelease();

	return instance;
}

ClockDoor::ClockDoor(ValueMap& properties) : super(properties, ClockDoor::ClipSize)
{
	this->isHaunted = GameUtils::getKeyOrDefault(this->properties, ClockDoor::PropertyClockStyle, Value("")).asString() == ClockDoor::ClockStyleHaunted;
	this->clippingContentNode = Node::create();
	this->clippingNode = SmartClippingNode::create(this->clippingContentNode, ClockDoor::ClipSize);
	this->portalEffectNode = Node::create();
	this->background = DrawNode::create();
	this->portalParticles = SmartParticles::create(ParticleResources::Portals_PortalFrost, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->edgeParticles = SmartParticles::create(ParticleResources::Portals_PortalEdge, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->handNode = Node::create();

	if (this->isHaunted)
	{
		this->clock = Sprite::create(ObjectResources::Doors_ClockDoor_ClockHaunted);
		this->pendulum = Sprite::create(ObjectResources::Doors_ClockDoor_SunPendulum);
		this->handCenter = Sprite::create(ObjectResources::Doors_ClockDoor_ClockHauntedHandCenter);
		this->handMinutes = Sprite::create(ObjectResources::Doors_ClockDoor_ClockHauntedHandMinute);
		this->handHours = Sprite::create(ObjectResources::Doors_ClockDoor_ClockHauntedHandHour);
	}
	else
	{
		this->clock = Sprite::create(ObjectResources::Doors_ClockDoor_Clock);
		this->pendulum = Sprite::create(ObjectResources::Doors_ClockDoor_MoonPendulum);
		this->handCenter = Sprite::create(ObjectResources::Doors_ClockDoor_ClockHandCenter);
		this->handMinutes = Sprite::create(ObjectResources::Doors_ClockDoor_ClockHandMinute);
		this->handHours = Sprite::create(ObjectResources::Doors_ClockDoor_ClockHandHour);
	}

	this->weights.push_back(createWeight(ObjectResources::Doors_ClockDoor_Weight1));
	this->weights.push_back(createWeight(ObjectResources::Doors_ClockDoor_Weight2));
	this->weights.push_back(createWeight(ObjectResources::Doors_ClockDoor_Weight3));

	this->background->drawSolidRect(Vec2::ZERO, ClockDoor::ClipSize, Color4F::BLACK);
	
	this->edgeParticles->start();
	this->portalParticles->start();
	this->pendulum->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->handMinutes->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->handHours->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->addTag(ClockDoor::MapKey);
	
	this->portalEffectNode->addChild(this->edgeParticles);
	this->portalEffectNode->addChild(this->portalParticles);
	this->clippingContentNode->addChild(this->background);
	// this->clippingContentNode->addChild(this->portalEffectNode);
	this->clippingContentNode->addChild(this->pendulum);

	for (const auto& next : this->weights)
	{
		this->clippingContentNode->addChild(std::get<0>(next));
	}

	this->handNode->addChild(this->handMinutes);
	this->handNode->addChild(this->handHours);
	this->handNode->addChild(this->handCenter);
	this->contentNode->addChild(this->clippingNode);
	this->contentNode->addChild(this->clock);
	this->contentNode->addChild(this->handNode);
}

ClockDoor::~ClockDoor()
{
}

void ClockDoor::onEnter()
{
	super::onEnter();

	const float PendulumSpeed = 0.85f;
	const float PendulumSwing = 12.5f;

	if (!this->isHaunted)
	{
		this->pendulum->runAction(RepeatForever::create(Sequence::create(
			EaseSineOut::create(RotateTo::create(PendulumSpeed, PendulumSwing)),
			CallFunc::create([=]()
			{
			}),
			EaseSineIn::create(RotateTo::create(PendulumSpeed, 0.0f)),
			EaseSineOut::create(RotateTo::create(PendulumSpeed, -PendulumSwing)),
			CallFunc::create([=]()
			{
			}),
			EaseSineIn::create(RotateTo::create(PendulumSpeed, 0.0f)),
			nullptr
		)));

		const float OneFakeMinute = 2.0f;
		const float OneFakeHour = OneFakeMinute * 60.0f / 8.0f;

		this->handMinutes->runAction(RepeatForever::create(Sequence::create(
			RotateBy::create(OneFakeMinute, 360.0f),
			nullptr
		)));

		this->handHours->runAction(RepeatForever::create(Sequence::create(
			RotateBy::create(OneFakeHour, 360.0f),
			nullptr
		)));

		static const std::vector<float> WeightInitDelays = { 1.14f, 2.12f, 0.37f };
		static const std::vector<float> WeightSpeeds = { 1.91f, 2.12f, 2.37f };
		static const std::vector<float> WeightDelays = { 1.91f, 2.12f, 2.37f };
		static const std::vector<float> Deltas = { 32.0f, -16.0f, 16.0f };

		for (int index = 0; index < int(this->weights.size()); index++)
		{
			Node* weight = std::get<0>(this->weights[index]);
			Node* spinner = std::get<1>(this->weights[index]);

			weight->runAction(Sequence::create(
				DelayTime::create(WeightInitDelays[index]),
				CallFunc::create([=]()
				{
					weight->runAction(RepeatForever::create(Sequence::create(
						EaseSineInOut::create(MoveBy::create(WeightSpeeds[index], Vec2(0.0f, Deltas[index]))),
						DelayTime::create(WeightDelays[index]),
						EaseSineInOut::create(MoveBy::create(WeightSpeeds[index], Vec2(0.0f, -Deltas[index]))),
						DelayTime::create(WeightDelays[index]),
						nullptr
					)));
				}), nullptr));
			spinner->runAction(Sequence::create(
				DelayTime::create(WeightInitDelays[index]),
				CallFunc::create([=]()
				{
					spinner->runAction(RepeatForever::create(Sequence::create(
						RotateBy::create(WeightSpeeds[index], 360.0f),
						DelayTime::create(WeightDelays[index]),
						nullptr
					)));
				}), nullptr));
		}
	}
}

void ClockDoor::initializePositions()
{
	super::initializePositions();

	this->clippingNode->setPosition(Vec2(0.0f, this->isHaunted ? -112.0f : -48.0f));
	this->background->setPosition(-Vec2(ClockDoor::ClipSize / 2.0f));
	this->handNode->setPosition(Vec2(0.0f, (this->isHaunted ? 0.0f : 16.0f) + 136.0f));
	this->pendulum->setPosition(Vec2(0.0f, (this->isHaunted ? -16.0f : 0.0f) + 144.0f));

	for (int index = 0; index < int(this->weights.size()); index++)
	{
		Node* weight = std::get<0>(this->weights[index]);
		Node* spinner = std::get<1>(this->weights[index]);

		weight->setPosition(Vec2(
			float(index - 1) * 32.0f,
			float(std::abs(index - 1)) * -16.0f + 32.0f + (this->isHaunted ? -8.0f : 0.0f)
		));
		spinner->setPosition(Vec2(0.0f, 56.0f));
	}
}

void ClockDoor::initializeListeners()
{
	super::initializeListeners();
}

std::tuple<cocos2d::Node*, cocos2d::Node*> ClockDoor::createWeight(std::string weightResource)
{
	cocos2d::Node* baseNode = Node::create();
	cocos2d::Sprite* weight = Sprite::create(ObjectResources::Doors_ClockDoor_Weight1);
	cocos2d::Sprite* rope = Sprite::create(ObjectResources::Doors_ClockDoor_WeightRope);
	cocos2d::Sprite* spinner = Sprite::create(ObjectResources::Doors_ClockDoor_WeightSpinner);

	baseNode->addChild(rope);
	baseNode->addChild(weight);
	baseNode->addChild(spinner);

	rope->setAnchorPoint(Vec2(0.5f, 0.0f));

	return std::make_tuple(baseNode, spinner);
}
