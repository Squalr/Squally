#include "Wind.h"

Wind* Wind::create(ValueMap* initProperties, Size startSize, Vec2 startSpeed)
{
	Wind* instance = new Wind(initProperties, startSize, startSpeed);

	instance->autorelease();

	return instance;
}

Wind::Wind(ValueMap* initProperties, Size startSize, Vec2 startSpeed) : CollisionObject(initProperties)
{
	this->size = startSize;
	this->windSpeed = startSpeed;
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

	this->setButtonOffset(Vec2(0.0f, 0.0f));
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
