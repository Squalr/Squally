#include "Crusher.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Traps/Crusher/CrusherGenericPreview.h"
#include "Objects/Platformer/Traps/Crusher/CrusherSetSpeedPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_TRAVEL_HEIGHT 1

const std::string Crusher::MapKey = "crusher";
const float Crusher::SpeedPer480Px = 4.0f;

Crusher* Crusher::create(ValueMap& properties)
{
	Crusher* instance = new Crusher(properties);

	instance->autorelease();

	return instance;
}

Crusher::Crusher(ValueMap& properties) : super(properties)
{
	this->travelDistance = this->properties.at(GameObject::MapKeyHeight).asFloat();
	this->base = Sprite::create(ObjectResources::Traps_SpikedCrusher_Base);
	this->pole = Sprite::create(ObjectResources::Traps_SpikedCrusher_Pole);
	this->crusher = Sprite::create(ObjectResources::Traps_SpikedCrusher_HeadJagged);
	this->spikeCollision = CollisionObject::create(CollisionObject::createBox(CSize(212.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));
	this->poleClip = SmartClippingNode::create(this->pole, CSize(this->pole->getContentSize().width, this->travelDistance - 180.0f));
	
	this->base->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->spikeCollision->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->base->setFlippedY(true);
	this->crusher->setFlippedY(true);
	
	// Create parameters to repeat the texture
	Texture2D::TexParams params = Texture2D::TexParams();
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapT = GL_REPEAT;
	this->pole->setTextureRect(CRect(0.0f, 0.0f, this->pole->getContentSize().width, this->travelDistance));
	
	if (this->pole->getTexture() != nullptr)
	{
		this->pole->getTexture()->setTexParameters(params);
	}

	this->addChild(this->poleClip);
	this->addChild(this->base);
	this->addChild(this->crusher);
	this->crusher->addChild(this->spikeCollision);
}

Crusher::~Crusher()
{
}

void Crusher::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Crusher::initializePositions()
{
	super::initializePositions();

	this->poleClip->setPositionY(48.0f);
	this->base->setPositionY(this->travelDistance / 2.0f);
	this->spikeCollision->setPosition(Vec2(0.0f, 64.0f));
}

void Crusher::update(float dt)
{
	// Stop moving down if there is no player below
	if (!this->isMovingUp && !this->isPlayerDetected())
	{
		return;
	}

    float adjustedSpeed = (this->isMovingUp ? 1.0f : -1.0f) * this->getSpeed();
    float startPositionY = (this->isMovingUp ? 1.0f : -1.0f) * (std::max(this->travelDistance - 512.0f, 0.0f));

    this->crusher->setPositionY(this->crusher->getPositionY() + adjustedSpeed * dt);
    this->pole->setPositionY(this->crusher->getPositionY() + this->travelDistance / 2.0f);

    if (this->isMovingUp)
    {
        if (this->crusher->getPositionY() > startPositionY)
        {
            this->isMovingUp = !this->isMovingUp;
        }
    }
    else
    {
        if (this->crusher->getPositionY() < startPositionY)
        {
            this->isMovingUp = !this->isMovingUp;
        }
    }
}

float Crusher::getSpeed()
{
    return Crusher::SpeedPer480Px * 480.0f;
}

Vec2 Crusher::getButtonOffset()
{
	return Vec2(0.0f, this->crusher->getPositionY() + 196.0f);
}

void Crusher::registerHackables()
{
	super::registerHackables();
	
	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_TRAVEL_HEIGHT,
			HackableCode::HackableCodeInfo(
				Crusher::MapKey,
				Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_DetectPlayer::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_BleedingLimb,
				LazyNode<HackablePreview>::create([=](){ return CrusherSetSpeedPreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_RegisterEbx::create() },
					{ HackableCode::Register::zsi, Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_RegisterEsi::create() },
				},
				int(HackFlags::None),
				20.0f,
				0.0f
			)
		},
	};

	auto isPlayerDetectedFunc = &Crusher::isPlayerDetected;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)isPlayerDetectedFunc, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* Crusher::createDefaultPreview()
{
	return CrusherGenericPreview::create();
}

NO_OPTIMIZE bool Crusher::isPlayerDetected()
{
	ASM(push ZAX)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_TRAVEL_HEIGHT);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(pop ZAX)

	HACKABLES_STOP_SEARCH();

	return false;
}
END_NO_OPTIMIZE
