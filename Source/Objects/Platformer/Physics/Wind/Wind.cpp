#include "Wind.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/2d/CCParticleSystemQuad.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Physics/Wind/WindClippy.h"
#include "Objects/Platformer/Physics/Wind/WindGenericPreview.h"
#include "Objects/Platformer/Physics/Wind/WindSetSpeedPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_WIND_SPEED 1

const std::string Wind::MapKeyWind = "wind";
const float Wind::BaseWindSpeed = 10240.0f;

Wind* Wind::create(ValueMap& properties)
{
	Wind* instance = new Wind(properties);

	instance->autorelease();

	return instance;
}

Wind::Wind(ValueMap& properties) : super(properties)
{
	float speedX = 0.0f;
	float speedY = 0.0f;

	if (GameUtils::keyExists(this->properties, "speed-x"))
	{
		speedX = this->properties.at("speed-x").asFloat();
	}

	if (GameUtils::keyExists(this->properties, "speed-y"))
	{
		speedY = this->properties.at("speed-y").asFloat();
	}

	this->windSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	this->windSpeedDefault = Vec2(speedX, speedY);
	this->windSpeed = this->windSpeedDefault;
	this->windParticles = ParticleSystemQuad::create(ParticleResources::Gust);
	this->windForce = CollisionObject::create(PhysicsBody::createBox(this->windSize), (CollisionType)PlatformerCollisionType::Force, false, false);

	this->windParticles->setAnchorPoint(Vec2::ZERO);
	this->windParticles->setPositionType(ParticleSystem::PositionType::GROUPED);

	this->addChild(this->windForce);
	this->addChild(this->windParticles);
}

Wind::~Wind()
{
}

void Wind::onEnter()
{
	super::onEnter();

	this->windParticles->setTotalParticles(int(this->windSize.width * this->windSize.height / 4096.0f));
	this->windParticles->setPosVar(Vec2(this->windSize.width / 2.0f, this->windSize.height / 2.0f));

	this->scheduleUpdate();
}

void Wind::initializePositions()
{
	super::initializePositions();
}

void Wind::initializeListeners()
{
	super::initializeListeners();

	this->windForce->setContactUpdateCallback(CC_CALLBACK_2(Wind::applyWindForce, this));

	this->windForce->whenCollidesWith({ (int)PlatformerCollisionType::PlayerMovement, (int)PlatformerCollisionType::Movement, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		// Speed is applied in the update applyWindForce

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Wind::update(float dt)
{
	super::update(dt);

	this->updateWind(dt);
}

void Wind::applyWindForce(const std::vector<CollisionObject*>& targets, float dt)
{
	Vec2 thisPosition = GameUtils::getWorldCoords(this);

	for (auto it = targets.begin(); it != targets.end(); it++)
	{
		Vec2 targetPosition = GameUtils::getWorldCoords(*it);
		Vec2 distance = Vec2(std::abs(thisPosition.x - targetPosition.x), std::abs(thisPosition.y - targetPosition.y));
		Vec2 delta = Vec2(this->windSize / 2.0f) - distance;

		// Note: Y multiplier minimum is higher to prevent bobbing in place between wind objects
		Vec2 multiplier = Vec2(MathUtils::clamp(delta.x / (this->windSize.width / 2.0f), 0.0f, 1.0f), MathUtils::clamp(delta.y / (this->windSize.height / 2.0f) * 2.0f, 0.25f, 1.0f));
		Vec2 speed = Vec2(this->windSpeed.x * multiplier.x, this->windSpeed.y * multiplier.y) * Wind::BaseWindSpeed;

		(*it)->setVelocity((*it)->getVelocity() + speed * dt);
	}
}

Vec2 Wind::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Wind::registerHackables()
{
	super::registerHackables();

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_WIND_SPEED,
			HackableCode::LateBindData(
				Wind::MapKeyWind,
				Strings::Menus_Hacking_Objects_Wind_SetWindSpeed_SetWindSpeed::create(),
				UIResources::Menus_Icons_Spell,
				WindSetSpeedPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Wind_SetWindSpeed_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_Wind_SetWindSpeed_RegisterEbx::create() },
				},
				int(HackFlags::Wind),
				12.0f,
				this->showClippy ? WindClippy::create() : nullptr
			)
		},
	};

	auto updateWindFunc = &Wind::updateWind;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateWindFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* Wind::createDefaultPreview()
{
	return WindGenericPreview::create();
}

NO_OPTIMIZE void Wind::updateWind(float dt)
{
	this->windSpeed = Vec2::ZERO;

	static volatile float* xSpeedPtr;
	static volatile float* ySpeedPtr;
	static volatile float* xDefaultSpeedPtr;
	static volatile float* yDefaultSpeedPtr;

	xSpeedPtr = &this->windSpeed.x;
	ySpeedPtr = &this->windSpeed.y;
	xDefaultSpeedPtr = &this->windSpeedDefault.x;
	yDefaultSpeedPtr = &this->windSpeedDefault.y;

	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(ZAX, xDefaultSpeedPtr);
	ASM_MOV_REG_VAR(ZBX, yDefaultSpeedPtr);

	ASM(movss xmm0, [ZAX])
	ASM(movss xmm1, [ZBX])

	ASM_MOV_REG_VAR(ZAX, xSpeedPtr);
	ASM_MOV_REG_VAR(ZBX, ySpeedPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_WIND_SPEED);
	ASM(movss [ZAX], xmm0)
	ASM(movss [ZBX], xmm1)
	ASM_NOP16()
	ASM_NOP16()
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZAX);

	HACKABLES_STOP_SEARCH();

	if (this->windSpeed.x == 0.0f && this->windSpeed.y == 0.0f)
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

	static volatile float angle;

	angle = std::atan2(this->windSpeed.y, this->windSpeed.x) * 180.0f / float(M_PI);

	this->windParticles->setAngle(angle);
}
