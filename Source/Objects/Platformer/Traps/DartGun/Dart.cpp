#include "Dart.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/PendulumBlade/TargetAngle.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

Dart* Dart::create(ValueMap* initProperties)
{
	Dart* instance = new Dart(initProperties);

	instance->autorelease();

	return instance;
}

Dart::Dart(ValueMap* initProperties) : HackableObject(initProperties)
{
	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	this->registerHackables();
}

Dart::~Dart()
{
}

void Dart::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Dart::initializePositions()
{
	super::initializePositions();
}

void Dart::update(float dt)
{
	super::update(dt);
}

void Dart::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_SWING,
			HackableCode::LateBindData(
				Strings::Hacking_Objects_PendulumBlade_TargetAngle::create(),
				UIResources::Menus_Icons_CrossHair,
				nullptr,
				{
					{ HackableCode::Register::eax, nullptr },
					{ HackableCode::Register::ebx, nullptr }
				}
			)
		},
	};

	auto swingFunc = &Dart::dartHeatSeek;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)swingFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 Dart::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Dart::dartHeatSeek()
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

PhysicsBody* Dart::buildCollision()
{
	// Polygons can't be concave, so we get around this by building the left and right sides of the blade separately

	std::vector<Vec2> leftPoints = std::vector<Vec2>();

	leftPoints.push_back(Vec2(0.0f, 8.0f));
	leftPoints.push_back(Vec2(-212.0f, 64.0f));
	leftPoints.push_back(Vec2(-160.0f, -32.0f));
	leftPoints.push_back(Vec2(-96.0f, -64.0f));
	leftPoints.push_back(Vec2(0.0f, -80.0f));

	std::vector<Vec2> rightPoints = std::vector<Vec2>();

	rightPoints.push_back(Vec2(0.0f, 8.0f));
	rightPoints.push_back(Vec2(212.0f, 64.0f));
	rightPoints.push_back(Vec2(160.0f, -32.0f));
	rightPoints.push_back(Vec2(96.0f, -64.0f));
	rightPoints.push_back(Vec2(0.0f, -80.0f));

	PhysicsBody* physicsBody = PhysicsBody::createPolygon(leftPoints.data(), leftPoints.size());

	physicsBody->addShape(PhysicsShapePolygon::create(rightPoints.data(), rightPoints.size()));

	return physicsBody;
}
