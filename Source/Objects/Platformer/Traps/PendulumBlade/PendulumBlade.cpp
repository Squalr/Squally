#include "PendulumBlade.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/PendulumBlade/PendulumBladeGenericPreview.h"
#include "Objects/Platformer/Traps/PendulumBlade/PendulumBladeSetAnglePreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string PendulumBlade::MapKey = "pendulum-blade";
const std::string PendulumBlade::HackIdentifierTargetAngle = "pendulum-blade-target-angle";

const float PendulumBlade::DefaultAngle = 270.0f;
const float PendulumBlade::SwingsPerSecondAt480Length = 1.5f;
const float PendulumBlade::MinAngle = MathUtils::wrappingNormalize(PendulumBlade::DefaultAngle - 45.0f, 0.0f, 360.0f);
const float PendulumBlade::MaxAngle = MathUtils::wrappingNormalize(PendulumBlade::DefaultAngle + 45.0f, 0.0f, 360.0f);

PendulumBlade* PendulumBlade::create(ValueMap& properties)
{
	PendulumBlade* instance = new PendulumBlade(properties);

	instance->autorelease();

	return instance;
}

PendulumBlade::PendulumBlade(ValueMap& properties) : super(properties)
{
	this->neck = Sprite::create(ObjectResources::Traps_PendulumBlade_Neck);
	this->bladeChain = Node::create();
	this->bladeCollision = CollisionObject::create(this->createBladeCollision(), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));

	float height = this->properties.at(GameObject::MapKeyHeight).asFloat();

	this->targetAngle = PendulumBlade::DefaultAngle;
	this->chainHeight = height;

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->bladeChain->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->buildChain();
	
	this->bladeChain->addChild(this->bladeCollision);
	this->addChild(this->neck);
	this->addChild(this->bladeChain);
}

PendulumBlade::~PendulumBlade()
{
}

void PendulumBlade::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
	this->startSwing();
}

void PendulumBlade::initializePositions()
{
	super::initializePositions();

	const float neckOfffset = 8.0f;

	this->bladeCollision->setPositionY(-this->chainHeight);
	this->neck->setPositionY(this->chainHeight / 2.0f + neckOfffset);
	this->bladeChain->setPositionY(this->chainHeight / 2.0f);
}

void PendulumBlade::update(float dt)
{
	super::update(dt);
	
	this->repositionHackButtons();
}

Vec2 PendulumBlade::getButtonOffset()
{
	float angle = float(M_PI) * this->bladeChain->getRotation() / 180.0f;

	return Vec2(0.0f, this->chainHeight / 2.0f) - Vec2(std::sin(angle) * this->chainHeight, std::cos(angle) * this->chainHeight);
}

void PendulumBlade::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_SWING,
			HackableCode::HackableCodeInfo(
				PendulumBlade::HackIdentifierTargetAngle,
				Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_SetTargetAngle::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_CrossHair,
				LazyNode<HackablePreview>::create([=](){ return PendulumBladeSetAnglePreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_PendulumBlade_SetTargetAngle_RegisterEbx::create() }
				},
				int(HackFlags::None),
				20.0f,
				0.0f
			)
		},
	};

	auto swingFunc = &PendulumBlade::setSwingAngle;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* PendulumBlade::createDefaultPreview()
{
	return PendulumBladeGenericPreview::create();
}

void PendulumBlade::startSwing()
{
	this->setSwingAngle(PendulumBlade::MinAngle);
	this->doSwing();	
}

NO_OPTIMIZE void PendulumBlade::setSwingAngle(float angle)
{
	this->previousAngle = this->targetAngle;
	static volatile int previousAngleInt;
	static volatile int angleInt;

	previousAngleInt = (int)previousAngle;
	angleInt = (int)angle;

	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(eax, angleInt);
	ASM_MOV_REG_VAR(ebx, previousAngleInt);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SWING);
	ASM(mov ZBX, ZAX);
	ASM_NOP5();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(angleInt, ebx);

	ASM(pop ZBX);
	ASM(pop ZAX);

	this->targetAngle = MathUtils::wrappingNormalize((float)angleInt, 0.0f, 360.0f);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE

void PendulumBlade::doSwing()
{
	const float arc = (PendulumBlade::MaxAngle - PendulumBlade::MinAngle);
	const float minDuration = 0.5f;
	const float maxDuration = 5.0f;

	volatile float speedMultiplier = (this->chainHeight / 480.0f) * PendulumBlade::SwingsPerSecondAt480Length;

	volatile float angleDelta = std::abs(this->previousAngle - this->targetAngle);
	volatile float duration = MathUtils::clamp((speedMultiplier * (angleDelta / arc)) / PendulumBlade::SwingsPerSecondAt480Length, minDuration, maxDuration);

	// Adjust angle to cocos space (inverted Y)
	volatile float newAngleAdjusted = MathUtils::wrappingNormalize(-this->targetAngle + PendulumBlade::DefaultAngle, 0.0f, 360.0f);

	// Run normal swing
	this->bladeChain->runAction(
		Sequence::create(
			EaseSineInOut::create(RotateTo::create(duration, newAngleAdjusted)),
			CallFunc::create([=]()
			{
				this->setSwingAngle((this->targetAngle > (PendulumBlade::MaxAngle + PendulumBlade::MinAngle) / 2.0f) ? PendulumBlade::MinAngle : PendulumBlade::MaxAngle);
				
				this->doSwing();
			}),
			nullptr
		)
	);
}

void PendulumBlade::buildChain()
{
	float remainingHeight = this->chainHeight;
	int index = 0;

	Sprite* blade = Sprite::create(ObjectResources::Traps_PendulumBlade_Blade);

	do
	{
		const float chainOverlap = 10.0f;

		Sprite* nextChainLink = Sprite::create(ObjectResources::Traps_PendulumBlade_Chain);

		nextChainLink->setAnchorPoint(Vec2(0.5f, 1.0f));

		this->bladeChain->addChild(nextChainLink);

		nextChainLink->setPositionY((float)index++ * -(nextChainLink->getContentSize().height - chainOverlap));

		remainingHeight -= nextChainLink->getContentSize().height - chainOverlap;

	} while (remainingHeight > 0.0f);

	blade->setPositionY(-this->chainHeight);

	this->bladeChain->addChild(blade);
}

std::vector<Vec2> PendulumBlade::createBladeCollision()
{
	std::vector<Vec2> points = std::vector<Vec2>();

	points.push_back(Vec2(0.0f, 8.0f));
	points.push_back(Vec2(-212.0f, 64.0f));
	points.push_back(Vec2(-160.0f, -32.0f));
	points.push_back(Vec2(-96.0f, -64.0f));
	points.push_back(Vec2(0.0f, -80.0f));

	points.push_back(Vec2(0.0f, 8.0f));
	points.push_back(Vec2(212.0f, 64.0f));
	points.push_back(Vec2(160.0f, -32.0f));
	points.push_back(Vec2(96.0f, -64.0f));
	points.push_back(Vec2(0.0f, -80.0f));

	return points;
}
