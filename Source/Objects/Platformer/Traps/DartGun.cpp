#include "DartGun.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Objects/Hackables/PendulumBlade/TargetAngle.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

const std::string DartGun::MapKeyDartGun = "dart-gun";

DartGun* DartGun::create(ValueMap* initProperties)
{
	DartGun* instance = new DartGun(initProperties);

	instance->autorelease();

	return instance;
}

DartGun::DartGun(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->dartGunAnimations = SmartAnimationNode::create(ObjectResources::War_Machines_Dartgun_Animations);

	this->dartGunAnimations->playAnimation();

	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	this->registerHackables();

	this->addChild(this->dartGunAnimations);
}

DartGun::~DartGun()
{
}

void DartGun::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void DartGun::initializePositions()
{
	super::initializePositions();
}

void DartGun::update(float dt)
{
	super::update(dt);

	SmartAnimationNode::AnimationPart cannon = this->dartGunAnimations->getAnimationPart("pivot_bone");

	cannon.rotation = MathUtils::wrappingNormalize(cannon.rotation + dt, 0.0f, 360.0f);

	this->dartGunAnimations->setAnimationPart("pivot_bone", cannon);
}

void DartGun::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{ LOCAL_FUNC_ID_SWING, HackableCode::LateBindData(Strings::Objects_Hackables_PendulumBlade_TargetAngle::create(), UIResources::Menus_Icons_CrossHair)},
	};

	auto swingFunc = &DartGun::update;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 DartGun::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void DartGun::shoot(float angle)
{
	/*
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
	*/

	HACKABLES_STOP_SEARCH();
}
