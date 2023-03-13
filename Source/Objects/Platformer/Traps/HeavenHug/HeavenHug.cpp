#include "HeavenHug.h"

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
#include "Objects/Platformer/Traps/HeavenHug/HeavenHugGenericPreview.h"
#include "Objects/Platformer/Traps/HeavenHug/HeavenHugSetSpeedPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_TRAVEL_HEIGHT 1

const std::string HeavenHug::MapKey = "heaven-hug";
const float HeavenHug::SpeedPer480Px = 2.0f;

HeavenHug* HeavenHug::create(ValueMap& properties)
{
	HeavenHug* instance = new HeavenHug(properties);

	instance->autorelease();

	return instance;
}

HeavenHug::HeavenHug(ValueMap& properties) : super(properties)
{
	this->heavenHugContainer = Node::create();
	this->heavenHug = Sprite::create(ObjectResources::Traps_HeavenHug_HEAVEN_HUG);
	this->spikeCollision = CollisionObject::create(CollisionObject::createBox(CSize(212.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Damage, CollisionObject::Properties(false, false));

	this->travelDistance = this->properties.at(GameObject::MapKeyHeight).asFloat();

	this->heavenHugContainer->addChild(this->heavenHug);
	this->heavenHug->addChild(this->spikeCollision);
	this->addChild(this->heavenHugContainer);
}

HeavenHug::~HeavenHug()
{
}

void HeavenHug::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void HeavenHug::initializePositions()
{
	super::initializePositions();

	this->heavenHugContainer->setPositionY(this->properties.at(GameObject::MapKeyHeight).asFloat() / 2.0f);
	this->spikeCollision->setPosition(Vec2(this->heavenHug->getContentSize().width / 2.0f, 32.0f));
}

void HeavenHug::update(float dt)
{
    float adjustedSpeed = (this->isMovingUp ? -1.0f : 1.0f) * this->getSpeed();
    float startPositionY = (this->isMovingUp ? -1.0f : 0.0f) * this->getTravelHeight();

    this->heavenHug->setPositionY(this->heavenHug->getPositionY() + adjustedSpeed * dt);

    if (this->isMovingUp)
    {
        if (this->heavenHug->getPositionY() < startPositionY)
        {
            this->isMovingUp = !this->isMovingUp;
        }
    }
    else
    {
        if (this->heavenHug->getPositionY() > startPositionY)
        {
            this->isMovingUp = !this->isMovingUp;
        }
    }
}

float HeavenHug::getSpeed()
{
    return this->SpeedPer480Px * 480.0f;
}

Vec2 HeavenHug::getButtonOffset()
{
	return Vec2(0.0f, this->heavenHug->getPositionY() + 196.0f);
}

void HeavenHug::registerHackables()
{
	super::registerHackables();
	
	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_TRAVEL_HEIGHT,
			HackableCode::HackableCodeInfo(
				HeavenHug::MapKey,
				Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_GetTravelHeight::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_BleedingLimb,
				LazyNode<HackablePreview>::create([=](){ return HeavenHugSetSpeedPreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_RegisterEax::create() },
					{ HackableCode::Register::zbx, Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_RegisterEbx::create() },
				},
				int(HackFlags::None),
				20.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_CommentPush::create()) + 
						std::string("fld dword ptr [eax]\n") +
						COMMENT(Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_CommentPop::create()
							->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zbx))) + 
						std::string("fstp dword ptr [ebx]\n\n") +
						COMMENT(Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_CommentHint::create()
							->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zbx))) + 
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_CommentPush::create()) + 
						std::string("fld dword ptr [rax]\n") +
						COMMENT(Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_CommentPop::create()
							->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zbx))) + 
						std::string("fstp dword ptr [rbx]\n\n") +
						COMMENT(Strings::Menus_Hacking_Objects_HeavenHug_GetTravelHeight_CommentHint::create()
							->setStringReplacementVariables(HackableCode::registerToLocalizedString(HackableCode::Register::zbx))) + 
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create())
					)
				},
				true
			)
		},
	};

	auto getHeightFunc = &HeavenHug::getTravelHeight;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)getHeightFunc, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* HeavenHug::createDefaultPreview()
{
	return HeavenHugGenericPreview::create();
}

NO_OPTIMIZE float HeavenHug::getTravelHeight()
{
	static volatile float* travelDistPtr = new float();
	static volatile float retVal;

	*travelDistPtr = this->travelDistance;
	retVal = *travelDistPtr;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_PTR(ZAX, travelDistPtr);
	ASM_MOV_REG_PTR(ZBX, travelDistPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_TRAVEL_HEIGHT);
	ASM(fld dword ptr [ZAX]);
	ASM(fstp dword ptr [ZBX]);
	ASM_NOP12();
	HACKABLE_CODE_END();

	ASM(mov ZAX, [ZAX]);
	ASM_MOV_VAR_REG(retVal, eax);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();

	return retVal;
}
END_NO_OPTIMIZE
