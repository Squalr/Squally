#include "MechanicalFlail.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlailGenericPreview.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlailSetAnglePreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ParticleResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string MechanicalFlail::MapKey = "mechanical-flail";

const float MechanicalFlail::DefaultAngle = 90.0f;
const float MechanicalFlail::SwingsPerSecondAt480Length = 1.5f;
const float MechanicalFlail::MinAngle = MathUtils::wrappingNormalize(MechanicalFlail::DefaultAngle - 45.0f, 0.0f, 360.0f);
const float MechanicalFlail::MaxAngle = MathUtils::wrappingNormalize(MechanicalFlail::DefaultAngle + 45.0f, 0.0f, 360.0f);

MechanicalFlail* MechanicalFlail::create(ValueMap& properties)
{
	MechanicalFlail* instance = new MechanicalFlail(properties);

	instance->autorelease();

	return instance;
}

MechanicalFlail::MechanicalFlail(ValueMap& properties) : super(properties)
{
	this->joint = Sprite::create(ObjectResources::Traps_MechanicalFlail_Joint);
	this->flailChain = Node::create();
	this->smokeParticles = SmartParticles::create(ParticleResources::Objects_Smoke, SmartParticles::CullInfo(Size(96.0f, 96.0f)));
	this->flailCollision = CollisionObject::create(CollisionObject::createCircle(56.0f), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));

	float height = this->properties.at(GameObject::MapKeyHeight).asFloat();

	this->targetAngle = MechanicalFlail::DefaultAngle;
	this->flailHeight = height;

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->flailChain->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->buildChain();
	
	this->flailChain->addChild(this->flailCollision);
	this->addChild(this->flailChain);
	this->addChild(this->joint);
	this->addChild(this->smokeParticles);
}

MechanicalFlail::~MechanicalFlail()
{
}

void MechanicalFlail::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
	this->startSwing();
}

void MechanicalFlail::initializePositions()
{
	super::initializePositions();

	this->flailCollision->setPositionY(this->flailHeight);
	this->smokeParticles->setPositionY(-this->flailHeight / 2.0f);
	this->joint->setPositionY(-this->flailHeight / 2.0f);
	this->flailChain->setPositionY(-this->flailHeight / 2.0f);
}

void MechanicalFlail::update(float dt)
{
	super::update(dt);
}

Vec2 MechanicalFlail::getButtonOffset()
{
	float angle = float(M_PI) * this->flailChain->getRotation() / 180.0f;

	return Vec2(0.0f, -this->flailHeight / 2.0f) + Vec2(std::sin(angle) * this->flailHeight, std::cos(angle) * this->flailHeight);
}

void MechanicalFlail::registerHackables()
{
	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_SWING,
			HackableCode::HackableCodeInfo(
				MechanicalFlail::MapKey,
				Strings::Menus_Hacking_Objects_MechanicalFlail_SetTargetAngle_SetTargetAngle::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_CrossHair,
				MechanicalFlailSetAnglePreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_MechanicalFlail_SetTargetAngle_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_MechanicalFlail_SetTargetAngle_RegisterEbx::create() }
				},
				int(HackFlags::None),
				20.0f,
				0.0f
			)
		},
	};

	auto swingFunc = &MechanicalFlail::setSwingAngle;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* MechanicalFlail::createDefaultPreview()
{
	return MechanicalFlailGenericPreview::create();
}

void MechanicalFlail::startSwing()
{
	this->setSwingAngle(MechanicalFlail::MinAngle);
	this->doSwing();
}

NO_OPTIMIZE void MechanicalFlail::setSwingAngle(float angle)
{
	this->previousAngle = this->targetAngle;
	static volatile int previousAngleInt;
	static volatile int angleInt = (int)angle;

	previousAngleInt = (int)previousAngle;
	angleInt = (int)angle;

	ASM(push ZAX);
	ASM(push ZBX);
	ASM_MOV_REG_VAR(ZAX, angleInt);
	ASM_MOV_REG_VAR(ZBX, previousAngleInt);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SWING);
	ASM(mov ZBX, ZAX);
	ASM_NOP5();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(angleInt, ZBX);

	ASM(pop ZBX);
	ASM(pop ZAX);

	this->targetAngle = MathUtils::wrappingNormalize((float)angleInt, 0.0f, 360.0f);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE

void MechanicalFlail::doSwing()
{
	const float arc = (MechanicalFlail::MaxAngle - MechanicalFlail::MinAngle);
	const float minDuration = 0.5f;
	const float maxDuration = 5.0f;

	volatile float speedMultiplier = (this->flailHeight / 480.0f) * MechanicalFlail::SwingsPerSecondAt480Length;

	float angleDelta = std::abs(this->previousAngle - this->targetAngle);
	volatile float duration = MathUtils::clamp((speedMultiplier * (angleDelta / arc)) / MechanicalFlail::SwingsPerSecondAt480Length, minDuration, maxDuration);

	// Adjust angle to cocos space (inverted Y)
	volatile float newAngleAdjusted = MathUtils::wrappingNormalize(-this->targetAngle + MechanicalFlail::DefaultAngle, 0.0f, 360.0f);

	// Run normal swing
	this->flailChain->runAction(
		Sequence::create(
			EaseSineInOut::create(RotateTo::create(duration, newAngleAdjusted)),
			CallFunc::create([=]()
			{
				this->setSwingAngle((this->targetAngle > (MechanicalFlail::MaxAngle + MechanicalFlail::MinAngle) / 2.0f) ? MechanicalFlail::MinAngle : MechanicalFlail::MaxAngle);
				
				this->doSwing();
			}),
			nullptr
		)
	);

	// Play smoke effect if stuck in place or out of bounds
	if (this->targetAngle == previousAngle || this->targetAngle < MechanicalFlail::MinAngle || this->targetAngle > MechanicalFlail::MaxAngle)
	{
		if (!this->smokeParticles->isActive())
		{
			this->smokeParticles->start();
		}
	}
	else
	{
		if (this->smokeParticles->isActive())
		{
			this->smokeParticles->stop();
		}
	}
}

void MechanicalFlail::buildChain()
{
	float remainingHeight = this->flailHeight;
	int index = 0;

	Sprite* flail = Sprite::create(ObjectResources::Traps_MechanicalFlail_STEEL_BALL);

	do
	{
		const float chainOverlap = 10.0f;

		Sprite* nextPipeLink = Sprite::create(ObjectResources::Traps_MechanicalFlail_Shaft);

		nextPipeLink->setAnchorPoint(Vec2(0.5f, 0.0f));

		this->flailChain->addChild(nextPipeLink);

		nextPipeLink->setPositionY((float)index++ * (nextPipeLink->getContentSize().height - chainOverlap));

		remainingHeight -= nextPipeLink->getContentSize().height - chainOverlap;

	} while (remainingHeight > 0.0f);

	flail->setPositionY(this->flailHeight);

	this->flailChain->addChild(flail);
}
