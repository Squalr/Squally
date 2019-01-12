#include "MechanicalFlail.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlailGenericPreview.h"
#include "Objects/Platformer/Traps/MechanicalFlail/MechanicalFlailSetAnglePreview.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ParticleResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/MechanicalFlail/SetTargetAngle/SetTargetAngle.h"
#include "Strings/Hacking/Objects/MechanicalFlail/SetTargetAngle/RegisterEax.h"
#include "Strings/Hacking/Objects/MechanicalFlail/SetTargetAngle/RegisterEbx.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string MechanicalFlail::MapKeyMechanicalFlail = "mechanical-flail";

const float MechanicalFlail::DefaultAngle = 90.0f;
const float MechanicalFlail::SwingsPerSecondAt480Length = 1.5f;
const float MechanicalFlail::MinAngle = MathUtils::wrappingNormalize(MechanicalFlail::DefaultAngle - 45.0f, 0.0f, 360.0f);
const float MechanicalFlail::MaxAngle = MathUtils::wrappingNormalize(MechanicalFlail::DefaultAngle + 45.0f, 0.0f, 360.0f);

MechanicalFlail* MechanicalFlail::create(ValueMap* initProperties)
{
	MechanicalFlail* instance = new MechanicalFlail(initProperties);

	instance->autorelease();

	return instance;
}

MechanicalFlail::MechanicalFlail(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->joint = Sprite::create(ObjectResources::Traps_MechanicalFlail_Joint);
	this->flailChain = Node::create();
	this->smokeParticles = ParticleSystemQuad::create(ParticleResources::Objects_Smoke);
	this->flailCollision = CollisionObject::create(PhysicsBody::createCircle(56.0f), (CollisionType)PlatformerCollisionType::Damage, false, false);
	this->setDefaultPreview(MechanicalFlailGenericPreview::create());

	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	this->smokeParticles->setVisible(false);

	this->targetAngle = MechanicalFlail::DefaultAngle;
	this->flailHeight = height;

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->flailChain->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->registerHackables();
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

void MechanicalFlail::registerHackables()
{
	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_SWING,
			HackableCode::LateBindData(
				Strings::Hacking_Objects_MechanicalFlail_SetTargetAngle_SetTargetAngle::create(),
				UIResources::Menus_Icons_CrossHair,
				MechanicalFlailSetAnglePreview::create(),
				{
					{ HackableCode::Register::eax, Strings::Hacking_Objects_MechanicalFlail_SetTargetAngle_RegisterEax::create() },
					{ HackableCode::Register::ebx, Strings::Hacking_Objects_MechanicalFlail_SetTargetAngle_RegisterEbx::create() }
				}
			)
		},
	};

	auto swingFunc = &MechanicalFlail::swingToAngle;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 MechanicalFlail::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void MechanicalFlail::startSwing()
{
	swingToAngle(MechanicalFlail::MinAngle);
}

void MechanicalFlail::swingToAngle(float angle)
{
	const float arc = (MechanicalFlail::MaxAngle - MechanicalFlail::MinAngle);
	const float minDuration = 0.5f;
	const float maxDuration = 5.0f;

	volatile float previousAngle = this->targetAngle;
	volatile int previousAngleInt = (int)previousAngle;
	volatile int angleInt = (int)angle;

	ASM(push EAX);
	ASM(push EBX);
	ASM_MOV_REG_VAR(EAX, angleInt);
	ASM_MOV_REG_VAR(EBX, previousAngleInt);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SWING);
	ASM(mov EBX, EAX);
	ASM_NOP5();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(angleInt, EBX);

	ASM(pop EBX);
	ASM(pop EAX);

	this->targetAngle = MathUtils::wrappingNormalize((float)angleInt, 0.0f, 360.0f);

	volatile float speedMultiplier = (this->flailHeight / 480.0f) * MechanicalFlail::SwingsPerSecondAt480Length;

	float angleDelta = std::abs(previousAngle - this->targetAngle);
	volatile float duration = MathUtils::clamp((speedMultiplier * (angleDelta / arc)) / MechanicalFlail::SwingsPerSecondAt480Length, minDuration, maxDuration);

	// Adjust angle to cocos space (inverted Y)
	volatile float newAngleAdjusted = MathUtils::wrappingNormalize(-this->targetAngle + MechanicalFlail::DefaultAngle, 0.0f, 360.0f);

	// Run normal swing
	this->flailChain->runAction(
		Sequence::create(
			EaseSineInOut::create(RotateTo::create(duration, newAngleAdjusted)),
			CallFunc::create([=]()
			{
				if (this->targetAngle > (MechanicalFlail::MaxAngle + MechanicalFlail::MinAngle) / 2.0f)
				{
					this->swingToAngle(MechanicalFlail::MinAngle);
				}
				else
				{
					this->swingToAngle(MechanicalFlail::MaxAngle);
				}
			}),
			nullptr
		)
	);

	// Play smoke effect if stuck in place or out of bounds
	if (this->targetAngle == previousAngle || this->targetAngle < MechanicalFlail::MinAngle || this->targetAngle > MechanicalFlail::MaxAngle)
	{
		if (!this->smokeParticles->isActive())
		{
			this->smokeParticles->setVisible(true);
			this->smokeParticles->start();
		}
	}
	else
	{
		if (this->smokeParticles->isActive())
		{
			this->smokeParticles->setVisible(false);
			this->smokeParticles->stopSystem();
		}
	}

	HACKABLES_STOP_SEARCH();
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
