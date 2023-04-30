#include "Crusher.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Traps/Crusher/CrusherGenericPreview.h"
#include "Objects/Platformer/Traps/Crusher/CrusherSetSpeedPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_DETECTOR 1

const std::string Crusher::MapKey = "crusher";
const float Crusher::SpeedPer480Px = 2.0f;

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
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	this->scheduleUpdate();
}

void Crusher::initializePositions()
{
	super::initializePositions();

	this->poleClip->setPositionY(48.0f);
	this->base->setPositionY(this->travelDistance / 2.0f);
	this->spikeCollision->setPosition(Vec2(this->crusher->getContentSize().width / 2.0f, 64.0f));
}

void Crusher::update(float dt)
{
	// Stop moving down if there is no player below
	if (!this->isMovingUp && !this->isPlayerDetected())
	{
		this->isMovingUp = true;
	}

	float adjustedTravelDistance = std::abs(std::max(this->travelDistance - 512.0f, 0.0f));
    float adjustedSpeed = (this->isMovingUp ? 1.0f : -1.0f) * this->getSpeed();
    float startPositionY = (this->isMovingUp ? 1.0f : -1.0f) * adjustedTravelDistance;

    this->crusher->setPositionY(MathUtils::clamp(this->crusher->getPositionY() + adjustedSpeed * dt, -adjustedTravelDistance, adjustedTravelDistance));
    this->pole->setPositionY(this->crusher->getPositionY() + this->travelDistance / 2.0f);

    if (this->isMovingUp)
    {
        if (this->crusher->getPositionY() >= startPositionY)
        {
            this->isMovingUp = !this->isMovingUp;
        }
    }
    else
    {
        if (this->crusher->getPositionY() <= startPositionY)
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
			LOCAL_FUNC_ID_DETECTOR,
			HackableCode::HackableCodeInfo(
				Crusher::MapKey,
				Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_DetectPlayer::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_BleedingLimb,
				LazyNode<HackablePreview>::create([=](){ return CrusherSetSpeedPreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_RegisterEbx::create() },
					{ HackableCode::Register::zcx, Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_RegisterEcx::create() },
				},
				int(HackFlags::None),
				20.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							ConstantString::create("and ecx, eax\n"),
							ConstantString::create("and ecx, ebx\n\n"),
							Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_Hint::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create())
						})
						, // x64
						ConcatString::create({
							ConstantString::create("and rcx, rax\n"),
							ConstantString::create("and rcx, rbx\n\n"),
							Strings::Menus_Hacking_Objects_Crusher_DetectPlayer_Hint::create()
								->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create())
						})
					)
				},
				true
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
	static volatile int squallyPositionXLocal;
	static volatile int leftBoundLocal;
	static volatile int rightBoundLocal;
	static volatile int compareResultLeft;
	static volatile int compareResultRight;
	static volatile int compareResult;

	squallyPositionXLocal = 0;
	leftBoundLocal = -200;
	rightBoundLocal = 200;
	compareResult = 0;

	if (this->squally != nullptr)
	{
		static const Vec3 thisPosition = GameUtils::getWorldCoords3D(this);
		Vec3 squallyPosition = GameUtils::getWorldCoords3D(this->squally);

		squallyPositionXLocal = int(squallyPosition.x);
		leftBoundLocal = leftBoundLocal + int(thisPosition.x);
		rightBoundLocal = rightBoundLocal + int(thisPosition.x);

		// Different Z plane, don't detect player
		if (std::abs(thisPosition.z - squallyPosition.z) > 24.0f)
		{
			return false;
		}
	}

	compareResultLeft = squallyPositionXLocal > leftBoundLocal;
	compareResultRight = squallyPositionXLocal < rightBoundLocal;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX)
	ASM(push ZBX)
	ASM(push ZCX)

	ASM_MOV_REG_VAR(eax, compareResultLeft);
	ASM_MOV_REG_VAR(ebx, compareResultRight);
	ASM(mov ecx, 1)

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_DETECTOR);
	ASM(and ecx, eax)
	ASM(and ecx, ebx)
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(compareResult, ecx);

	ASM(pop ZCX)
	ASM(pop ZBX)
	ASM(pop ZAX)
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	return compareResult != 0;
}
END_NO_OPTIMIZE
