#include "Stalactite.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/Stalactite/StalactiteGenericPreview.h"
#include "Objects/Platformer/Traps/Stalactite/StalactiteSetSpeedPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_TRAVEL_HEIGHT 1

const std::string Stalactite::MapKey = "stalactite";
const float Stalactite::SpeedPer480Px = 2.0f;

Stalactite* Stalactite::create(ValueMap& properties)
{
	Stalactite* instance = new Stalactite(properties);

	instance->autorelease();

	return instance;
}

Stalactite::Stalactite(ValueMap& properties) : super(properties)
{
	this->heavenHugContainer = Node::create();
	this->heavenHug = Sprite::create(ObjectResources::Traps_Stalactite_Stalactite);
	this->spikeCollision = CollisionObject::create(this->createSpikeCollision(), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));

	this->travelDistance = this->properties.at(GameObject::MapKeyHeight).asFloat();

	this->heavenHugContainer->addChild(this->heavenHug);
	this->heavenHug->addChild(this->spikeCollision);
	this->addChild(this->heavenHugContainer);
}

Stalactite::~Stalactite()
{
}

void Stalactite::onEnter()
{
	super::onEnter();

	this->updateStalactite();
}

void Stalactite::initializePositions()
{
	super::initializePositions();

	this->heavenHugContainer->setPositionY(this->properties.at(GameObject::MapKeyHeight).asFloat() / 2.0f);
	this->spikeCollision->setPosition(Vec2(this->heavenHug->getContentSize().width / 2.0f, 32.0f));
}

Vec2 Stalactite::getButtonOffset()
{
	return Vec2(0.0f, this->heavenHug->getPositionY() + 196.0f);
}

void Stalactite::registerHackables()
{
	super::registerHackables();
	
	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_TRAVEL_HEIGHT,
			HackableCode::HackableCodeInfo(
				Stalactite::MapKey,
				Strings::Menus_StoryMode::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_BleedingLimb,
				StalactiteSetSpeedPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Menus_StoryMode::create() },
					{ HackableCode::Register::zbp, Strings::Menus_StoryMode::create() }
				},
				int(HackFlags::None),
				20.0f,
				0.0f
			)
		},
	};

	auto getHeightFunc = &Stalactite::getTravelHeight;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)getHeightFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* Stalactite::createDefaultPreview()
{
	return StalactiteGenericPreview::create();
}

void Stalactite::updateStalactite()
{
	float duration = MathUtils::clamp(this->travelDistance / (480.0f * Stalactite::SpeedPer480Px), 0.25f, 10.0f);

	if (this->heavenHug->getPositionY() >= 0.0f)
	{
		float delta = this->getTravelHeight();

		this->heavenHug->runAction(Sequence::create(
			EaseSineInOut::create(MoveTo::create(duration, Vec2(0.0f, -delta))),
			CallFunc::create([=]() { this->updateStalactite(); }),
			nullptr
		));
	}
	else
	{
		this->heavenHug->runAction(Sequence::create(
			EaseSineInOut::create(MoveTo::create(duration, Vec2::ZERO)),
			CallFunc::create([=]() { this->updateStalactite(); }),
			nullptr
		));
	}
}

NO_OPTIMIZE float Stalactite::getTravelHeight()
{
	static volatile float* travelDistPtr = new float();
	static volatile float retVal;

	*travelDistPtr = this->travelDistance;
	retVal = *travelDistPtr;

	ASM(push ZAX)

	ASM_MOV_REG_PTR(ZAX, travelDistPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_TRAVEL_HEIGHT);
	ASM(fld dword ptr [ZAX])
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(fstp dword ptr [ZAX])
	ASM(mov ZAX, [ZAX])
	ASM_MOV_VAR_REG(retVal, eax);

	ASM(pop ZAX)

	HACKABLES_STOP_SEARCH();

	return retVal;
}
END_NO_OPTIMIZE

std::vector<Vec2> Stalactite::createSpikeCollision()
{
	return std::vector<Vec2>();
}
