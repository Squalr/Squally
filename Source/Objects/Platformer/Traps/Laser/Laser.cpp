#include "Laser.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Traps/Laser/LaserCountDownPreview.h"
#include "Objects/Platformer/Traps/Laser/LaserGenericPreview.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Objects/Laser/UpdateCountDown/RegisterSt0.h"
#include "Strings/Hacking/Objects/Laser/UpdateCountDown/UpdateCountDown.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME 1

const std::string Laser::MapKeyLaser = "laser";

Laser* Laser::create(ValueMap* initProperties)
{
	Laser* instance = new Laser(initProperties);

	instance->autorelease();

	return instance;
}

Laser::Laser(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->currentLaserCountDown = RandomHelper::random_real(0.0f, 3.0f);
	this->maxLaserCountDown = 4.0f;
	this->isRunningAnimation = false;

	this->laserHeadTop = Sprite::create(ObjectResources::Traps_Laser_LaserHead);
	this->laserHeadBottom = Sprite::create(ObjectResources::Traps_Laser_LaserHead);
	this->laserWeak = Sprite::create(ObjectResources::Traps_Laser_LaserWeak);
	this->laserStrong = Sprite::create(ObjectResources::Traps_Laser_LaserMid);

	this->height = this->properties->at(SerializableObject::MapKeyHeight).asFloat();

	this->laserHeadBottom->setFlippedY(true);
	this->laserCollision = CollisionObject::create(PhysicsBody::createBox(Size(268.0f, 72.0f)), (CollisionType)PlatformerCollisionType::Damage, false, false);

	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;

	this->laserWeak->getTexture()->setTexParameters(params);
	this->laserWeak->setTextureRect(Rect(0.0f, 0.0f, this->laserWeak->getContentSize().width, this->height));

	this->laserStrong->getTexture()->setTexParameters(params);
	this->laserStrong->setTextureRect(Rect(0.0f, 0.0f, this->laserStrong->getContentSize().width, this->height));

	this->setDefaultPreview(LaserGenericPreview::create());
	this->registerHackables();

	this->addChild(this->laserWeak);
	this->addChild(this->laserStrong);
	this->addChild(this->laserHeadTop);
	this->addChild(this->laserHeadBottom);
}

Laser::~Laser()
{
}

void Laser::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Laser::update(float dt)
{
	super::update(dt);

	this->updateLaser(dt);
}

void Laser::initializePositions()
{
	super::initializePositions();

	this->laserHeadTop->setPositionY(this->height / 2.0f);
	this->laserHeadBottom->setPositionY(-this->height / 2.0f);
	this->laserCollision->setPosition(Vec2::ZERO);
}

void Laser::registerHackables()
{
	// this->hackableDataTargetAngle = HackableData::create("Target Angle", &this->targetAngle, typeid(this->targetAngle), UIResources::Menus_Icons_AxeSlash);
	// this->registerData(this->hackableDataTargetAngle);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME,
			HackableCode::LateBindData(
				Laser::MapKeyLaser,
				Strings::Hacking_Objects_Laser_UpdateCountDown_UpdateCountDown::create(),
				UIResources::Menus_Icons_Clock,
				LaserCountDownPreview::create(),
				{
					{ HackableCode::Register::ebx, Strings::Hacking_Objects_Laser_UpdateCountDown_RegisterSt0::create() },
				}
			)
		},
	};

	auto updateLaserFunc = &Laser::updateLaser;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)updateLaserFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

Vec2 Laser::getButtonOffset()
{
	return Vec2(0.0f, 128.0f);
}

void Laser::updateLaser(float dt)
{
	if (this->isRunningAnimation)
	{
		return;
	}

	volatile float* countDownPtr = &this->currentLaserCountDown;
	volatile float* deltaTimePtr = &dt;

	ASM(push EAX);
	ASM(push EBX);
	ASM_MOV_REG_VAR(EAX, countDownPtr);
	ASM_MOV_REG_VAR(EBX, deltaTimePtr);

	ASM(fld dword ptr [EAX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_INCREMENT_ANIMATION_FRAME);
	ASM(fsub dword ptr [EBX]);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(fstp dword ptr [EAX])

	ASM(pop EAX);
	ASM(pop EBX);

	HACKABLES_STOP_SEARCH();

	if (this->currentLaserCountDown <= 0.0f)
	{
		const float stayActiveDuration = 1.5f;

		this->isRunningAnimation = true;
		this->currentLaserCountDown = this->maxLaserCountDown;

		// Move collision box
		this->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->laserWeak->setVisible(true);
			}),
			DelayTime::create(0.25f),
			CallFunc::create([=]()
			{
				this->laserWeak->setVisible(false);
			}),
			DelayTime::create(0.75f),
			CallFunc::create([=]()
			{
				this->laserWeak->setVisible(true);
			}),
			DelayTime::create(0.25f),
			CallFunc::create([=]()
			{
				this->laserWeak->setVisible(false);
			}),
			DelayTime::create(0.25f),
			CallFunc::create([=]()
			{
				this->laserWeak->setVisible(true);
			}),
			DelayTime::create(0.25f),
			CallFunc::create([=]()
			{
				this->laserWeak->setVisible(false);
			}),
			DelayTime::create(0.25f),
			CallFunc::create([=]()
			{
				this->laserStrong->setVisible(true);
				// TODO: collision
			}),
			DelayTime::create(stayActiveDuration),
			CallFunc::create([=]()
			{
				this->laserStrong->setVisible(false);
				this->isRunningAnimation = false;
			}),
			nullptr
		));
	}
}
