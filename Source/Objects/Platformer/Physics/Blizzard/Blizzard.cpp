#include "Blizzard.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Physics/Blizzard/BlizzardGenericPreview.h"
#include "Objects/Platformer/Physics/Blizzard/BlizzardSetSpeedPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ParticleResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_WIND_SPEED 1

const std::string Blizzard::MapKey = "blizzard";
const std::string Blizzard::PropertyUniform = "uniform";
const std::string Blizzard::PropertySpeedX = "speed-x";
const std::string Blizzard::PropertySpeedY = "speed-y";
const float Blizzard::BaseBlizzardSpeed = 10240.0f;

Blizzard* Blizzard::create(ValueMap& properties)
{
	Blizzard* instance = new Blizzard(properties);

	instance->autorelease();

	return instance;
}

Blizzard::Blizzard(ValueMap& properties) : super(properties)
{
	this->isUniform = GameUtils::getKeyOrDefault(this->properties, Blizzard::PropertyUniform, Value(false)).asBool();
	float speedX = GameUtils::getKeyOrDefault(this->properties, Blizzard::PropertySpeedX, Value(0.0f)).asFloat();
	float speedY = GameUtils::getKeyOrDefault(this->properties, Blizzard::PropertySpeedY, Value(0.0f)).asFloat();

	this->blizzardSize = CSize(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	this->blizzardSpeedDefault = Vec2(speedX, speedY);
	this->blizzardSpeed = this->blizzardSpeedDefault;
	this->blizzardParticles = SmartParticles::create(ParticleResources::Gust, SmartParticles::CullInfo(this->blizzardSize));
	this->blizzardForce = CollisionObject::create(CollisionObject::createBox(this->blizzardSize), (CollisionType)PlatformerCollisionType::Force, CollisionObject::Properties(false, false));

	this->blizzardParticles->setAnchorPoint(Vec2::ZERO);
	this->blizzardParticles->setGrouped();
	
	this->addChild(this->blizzardForce);
	this->addChild(this->blizzardParticles);
}

Blizzard::~Blizzard()
{
}

void Blizzard::onEnter()
{
	super::onEnter();

	this->blizzardParticles->start();
	this->blizzardParticles->setTotalParticles(int(this->blizzardSize.width * this->blizzardSize.height / 4096.0f));
	this->blizzardParticles->setPosVar(Vec2(this->blizzardSize.width / 2.0f, this->blizzardSize.height / 2.0f));

	this->scheduleUpdate();
}

void Blizzard::initializePositions()
{
	super::initializePositions();
}

void Blizzard::initializeListeners()
{
	super::initializeListeners();

	this->blizzardForce->whileCollidesWith({ (int)PlatformerCollisionType::EntityMovement, (int)PlatformerCollisionType::Physics }, [=](CollisionData collisionData)
	{
		this->applyBlizzardForce(collisionData.other, collisionData.dt);

		return CollisionResult::DoNothing;
	});
}

void Blizzard::update(float dt)
{
	super::update(dt);

	this->updateBlizzard(dt);
}

void Blizzard::applyBlizzardForce(CollisionObject* target, float dt)
{
	Vec2 thisPosition = GameUtils::getWorldCoords(this);

	Vec2 targetPosition = GameUtils::getWorldCoords(target);
	Vec2 distance = Vec2(std::abs(thisPosition.x - targetPosition.x), std::abs(thisPosition.y - targetPosition.y));
	Vec2 delta = Vec2(this->blizzardSize / 2.0f) - distance;

	// Note: default non-uniform values are to prevent bobbing in place between two blizzard objects
	const float MinMultiplierX = this->isUniform ? 1.0f : 0.15f;
	const float MinMultiplierY = this->isUniform ? 1.0f : 0.25f;

	Vec2 multiplier = Vec2(MathUtils::clamp(delta.x / (this->blizzardSize.width / 2.0f), MinMultiplierX, 1.0f), MathUtils::clamp(delta.y / (this->blizzardSize.height / 2.0f) * 2.0f, MinMultiplierY, 1.0f));
	Vec2 speed = Vec2(this->blizzardSpeed.x * multiplier.x, this->blizzardSpeed.y * multiplier.y) * Blizzard::BaseBlizzardSpeed;

	target->setVelocity(target->getVelocity() + speed * dt);
}

Vec2 Blizzard::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Blizzard::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_WIND_SPEED,
			HackableCode::HackableCodeInfo(
				Blizzard::MapKey,
				Strings::Menus_Hacking_Objects_Blizzard_SetBlizzardSpeed_SetBlizzardSpeed::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Blizzard,
				LazyNode<HackablePreview>::create([](){ return (HackablePreview*)BlizzardSetSpeedPreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Blizzard_SetBlizzardSpeed_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_Blizzard_SetBlizzardSpeed_RegisterEbx::create() },
				},
				int(HackFlags::Frost),
				12.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Objects_Blizzard_SetBlizzardSpeed_SetBlizzardSpeedDown::create(),
						// x86
						ConcatString::create({
							Strings::Menus_Hacking_Objects_Blizzard_SetBlizzardSpeed_CommentBlizzardDown::create(),
							Strings::Menus_Hacking_Objects_Blizzard_SetBlizzardSpeed_CommentModify::create(),
							ConstantString::create("mov dword ptr [eax], 0.0f\n"),
							ConstantString::create("mov dword ptr [ebx], -1.0f\n")
						})
						, // x64
						ConcatString::create({
							Strings::Menus_Hacking_Objects_Blizzard_SetBlizzardSpeed_CommentBlizzardDown::create(),
							Strings::Menus_Hacking_Objects_Blizzard_SetBlizzardSpeed_CommentModify::create(),
							ConstantString::create("mov dword ptr [rax], 0.0f\n"),
							ConstantString::create("mov dword ptr [rbx], -1.0f\n")
						})
					),
				}
			)
		},
	};

	auto updateBlizzardFunc = &Blizzard::updateBlizzard;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateBlizzardFunc, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* Blizzard::createDefaultPreview()
{
	return BlizzardGenericPreview::create();
}

NO_OPTIMIZE void Blizzard::updateBlizzard(float dt)
{
	this->blizzardSpeed = Vec2::ZERO;

	static volatile float* xSpeedPtr;
	static volatile float* ySpeedPtr;
	static volatile float* xDefaultSpeedPtr;
	static volatile float* yDefaultSpeedPtr;

	xSpeedPtr = &this->blizzardSpeed.x;
	ySpeedPtr = &this->blizzardSpeed.y;
	xDefaultSpeedPtr = &this->blizzardSpeedDefault.x;
	yDefaultSpeedPtr = &this->blizzardSpeedDefault.y;

	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_PTR(ZAX, xDefaultSpeedPtr);
	ASM_MOV_REG_PTR(ZBX, yDefaultSpeedPtr);

	ASM(movss xmm0, [ZAX]);
	ASM(movss xmm1, [ZBX]);

	ASM_MOV_REG_PTR(ZAX, xSpeedPtr);
	ASM_MOV_REG_PTR(ZBX, ySpeedPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_WIND_SPEED);
	ASM(movss [ZAX], xmm0);
	ASM(movss [ZBX], xmm1);
	ASM_NOP16();
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZBX);
	ASM(pop ZAX);

	HACKABLES_STOP_SEARCH();

	if (this->blizzardSpeed.x == 0.0f && this->blizzardSpeed.y == 0.0f)
	{
		this->blizzardParticles->stop(2.0f);
	}
	else
	{
		if (!this->blizzardParticles->isActive())
		{
			this->blizzardParticles->start();
		}
	}

	static volatile float angle = 0.0f;

	angle = std::atan2(this->blizzardSpeed.y, this->blizzardSpeed.x) * 180.0f / float(M_PI);

	this->blizzardParticles->setAngle(angle);
}
END_NO_OPTIMIZE
