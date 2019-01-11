#include "Wind.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

#include "Strings/Generics/Empty.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_WIND_SPEED_Y 1

const std::string Wind::MapKeyWind = "wind";

Wind* Wind::create(ValueMap* initProperties)
{
	Wind* instance = new Wind(initProperties);

	instance->autorelease();

	return instance;
}

Wind::Wind(ValueMap* initProperties) : HackableObject(initProperties)
{
	float speedX = 0.0f;
	float speedY = 0.0f;

	if (GameUtils::keyExists(this->properties, "speed-x"))
	{
		speedX = this->properties->at("speed-x").asFloat();
	}

	if (GameUtils::keyExists(this->properties, "speed-y"))
	{
		speedY = this->properties->at("speed-y").asFloat();
	}

	this->windSpeed = Vec2(speedX, speedY);
	this->windParticles = ParticleSystemQuad::create(ParticleResources::Gust);
	this->windParticles->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->addChild(this->windParticles);

	this->registerHackables();
	this->scheduleUpdate();
}

Wind::~Wind()
{
}

void Wind::registerHackables()
{
	this->windDataSpeedY = HackableData::create(
		&this->windSpeed.y,
		Strings::Generics_Empty::create(),
		typeid(this->windSpeed.y),
		UIResources::Menus_Icons_AlchemyPot,
		nullptr
	);
	this->registerData(this->windDataSpeedY);
}

Vec2 Wind::getButtonOffset()
{
	return Vec2(512.0f, 0.0f);
}

void Wind::update(float dt)
{
	float width = this->properties->at(SerializableObject::MapKeyWidth).asFloat();
	float height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	Vec2 speed = Vec2::ZERO;
	Vec2 currentSpeed = this->windSpeed;

	ASM(push EBX);
	ASM_MOV_REG_VAR(ebx, currentSpeed.y);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_WIND_SPEED_Y);
	ASM_MOV_VAR_REG(speed.y, EBX);
	HACKABLE_CODE_END();

	ASM(pop EBX);

	HACKABLES_STOP_SEARCH();

	if (speed.x == 0.0f && speed.y == 0.0f)
	{
		this->windParticles->stopSystem();
	}
	else
	{
		if (!this->windParticles->isActive())
		{
			this->windParticles->start();
		}
	}

	float angle = speed.x == 0.0f ? (speed.y > 0.0f ? -90.0f : 90.0f) : std::atan(speed.y / speed.x);
	this->windParticles->setAngle(angle);
	this->windParticles->setPosVar(Vec2(speed.y == 0.0f ? 0.0f : width, speed.x == 0.0f ? 0.0f : height));
}
