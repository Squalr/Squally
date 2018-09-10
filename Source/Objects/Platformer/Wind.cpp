#include "Wind.h"

Wind* Wind::create(ValueMap* initProperties)
{
	Wind* instance = new Wind(initProperties);

	instance->autorelease();

	return instance;
}

Wind::Wind(ValueMap* initProperties) : HackableObject(initProperties)
{
	float width = this->properties->at(SerializableObject::KeyWidth).asFloat();
	float height = this->properties->at(SerializableObject::KeyHeight).asFloat();
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

	this->size = Size(width, height);
	this->windSpeed = Vec2(speedX, speedY);
	this->windParticles = ParticleSystemQuad::create(Resources::Particles_Gust);
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
	this->windDataSpeedY = HackableData::create("Y Position", &this->windSpeed.y, &typeid(this->windSpeed.y), Resources::Menus_HackerModeMenu_Icons_AlchemyPot);
	this->registerData(this->windDataSpeedY);
}

Vec2 Wind::getButtonOffset()
{
	return Vec2::ZERO;
}

void Wind::update(float dt)
{
	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;

	Vec2 speed = Vec2::ZERO;
	Vec2 currentSpeed = this->windSpeed;

	__asm
	{
		push ebx;
		mov ebx, currentSpeed.y
	}

	HACKABLE_CODE_BEGIN(assemblyAddressStart, windSpeedYStart)
	__asm
	{
		mov speed.y, ebx
	}
	HACKABLE_CODE_END(assemblyAddressEnd, windSpeedYEnd)

	__asm
	{
		pop ebx;
	}

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

	float angle = speed.x == 0.0f ? (speed.y > 0.0f ? -90.0f : 90.0f) : atan(speed.y / speed.x);
	this->windParticles->setAngle(angle);

	this->windParticles->setPosVar(Vec2(speed.y == 0.0f ? 0.0f : this->size.width, speed.x == 0.0f ? 0.0f : this->size.height));

	this->windDataSpeedY->registerCode(assemblyAddressStart, assemblyAddressEnd, "Wind Y Speed", Resources::Menus_HackerModeMenu_Icons_Tornado);
}
