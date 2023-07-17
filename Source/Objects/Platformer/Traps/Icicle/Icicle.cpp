#include "Icicle.h"

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

#include "Objects/Platformer/Traps/Icicle/IcicleGenericPreview.h"
#include "Objects/Platformer/Traps/Icicle/IcicleGetDensityPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_APPLY_GRAVITY 1

const std::string Icicle::MapKey = "icicle";

Icicle* Icicle::create(ValueMap& properties)
{
	Icicle* instance = new Icicle(properties);
	
	instance->autorelease();

	return instance;
}

Icicle::Icicle(ValueMap& properties) : super(properties)
{
	CSize size = CSize(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat());
	this->sprite = Sprite::create(ObjectResources::Traps_Icicle_Icicle);
	this->collision = CollisionObject::create(CollisionObject::createBox(size), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, true));

	CSize imageSize = this->sprite->getContentSize();
	if (imageSize.height > 0.0f) 
	{
		this->sprite->setScale(size.height / imageSize.height);
	}

	this->collision->addChild(this->sprite);
	this->addChild(this->collision);
}

Icicle::~Icicle()
{
}

void Icicle::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Icicle::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEventOnce(this->getListenEvent(), [=](ValueMap)
	{
		const float RotationAngle = 2.5f;
		const float RotationSpeed = 0.05f;
		const float HalfRotationSpeed = RotationSpeed / 2.0f;
		const float RumbleTime = 0.5f;
		const int Rumbles = int(std::round((RumbleTime - RotationSpeed) / RotationSpeed)) / 2;

		// TODO: Add icicle shaking sound.
		// this->rumbleSound->play(); 

		this->runAction(Sequence::create(
			EaseSineInOut::create(RotateTo::create(HalfRotationSpeed, RotationAngle)),
			Repeat::create(Sequence::create(
				EaseSineInOut::create(RotateTo::create(RotationSpeed, -RotationAngle)),
				EaseSineInOut::create(RotateTo::create(RotationSpeed, RotationAngle)),
				nullptr
			), Rumbles),
			EaseSineInOut::create(RotateTo::create(HalfRotationSpeed, 0.0f)),
			CallFunc::create([=]()
			{
				this->isFalling = true;
			}),
			nullptr
		));
	});
}

void Icicle::initializePositions()
{
	super::initializePositions();
}

void Icicle::update(float dt)
{
	super::update(dt);

	this->applyGravity(dt);
}

Vec2 Icicle::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Icicle::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_APPLY_GRAVITY,
			HackableCode::HackableCodeInfo(
				Icicle::MapKey,
				Strings::Menus_Hacking_Objects_FloatingObjects_GetDensity_GetDensity::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_Anvil,
				LazyNode<HackablePreview>::create([=](){ return IcicleGetDensityPreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_FloatingObjects_GetDensity_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Objects_FloatingObjects_GetDensity_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Objects_FloatingObjects_GetDensity_RegisterXmm1::create() },
				},
				int(HackFlags::None),
				8.0f,
				0.0f
			)
		},
	};

	std::vector<HackableCode*> hackables = CREATE_HACKABLES(Icicle::applyGravity, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* Icicle::createDefaultPreview()
{
	return IcicleGenericPreview::create();
}

NO_OPTIMIZE void Icicle::applyGravity(float dt)
{
	static const float Acceleration = 1.3f;
	static const float Speed = 768.0f;

	if (!this->isFalling)
	{
		return;
	}

	this->setPositionY(this->getPositionY() + -pow(Speed, Acceleration) * dt);

	/*
	volatile static float* freeMemoryForUser = new float[16];
	volatile float densityRet = 0.5f;
	volatile float* densityRetPtr = &densityRet;
	volatile float densityCopy = this->loadedDensity;
	volatile float* densityCopyPtr = &densityCopy;

	// Prepare variables (initialize xmm0 with return value, xmm1 with loaded density)
	ASM(push ZAX);
	ASM_MOV_REG_PTR(ZAX, densityRetPtr);
	ASM(movss xmm0, dword ptr [ZAX]);
	ASM_MOV_REG_PTR(ZAX, densityCopyPtr);
	ASM(movss xmm1, dword ptr [ZAX]);
	ASM_MOV_REG_PTR(ZAX, freeMemoryForUser);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_APPLY_GRAVITY);
	ASM(movss xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();

	// Copy from xmm0 to the output variable
	ASM_MOV_REG_PTR(ZAX, densityRetPtr);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM(pop ZAX);
	*/
	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
