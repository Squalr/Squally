#include "MineCart.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Objects/Platformer/Interactables/Mounts/MineCart/MineCartPreview.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_CAN_MOVE 1

const std::string MineCart::MapKey = "mine-cart";

MineCart* MineCart::create(cocos2d::ValueMap& properties)
{
	MineCart* instance = new MineCart(properties);

	instance->autorelease();

	return instance;
}

MineCart::MineCart(cocos2d::ValueMap& properties) : super(properties, CSize(240.0f, 184.0f), false)
{
	this->parseColor();
	this->parseDirection();
	this->mountSpeed = GameUtils::getKeyOrDefault(this->properties, MineCart::PropertySpeed, Value(512.0f)).asFloat();
	this->body = Sprite::create(this->cartColor == CartColor::Brown ? ObjectResources::Interactive_MineCarts_Body1 : ObjectResources::Interactive_MineCarts_Body2);
	this->wheelFront = Sprite::create(ObjectResources::Interactive_MineCarts_WheelFront);
	this->wheelBack = Sprite::create(ObjectResources::Interactive_MineCarts_WheelBack);
	this->bottomCollision = CollisionObject::create(
		CollisionObject::createBox(CSize(240.0f, 48.0f)),
		int(PlatformerCollisionType::PassThrough),
		CollisionObject::Properties(false, false)
	);

	this->frontNode->addChild(this->bottomCollision);
	this->frontNode->addChild(this->body);
	this->frontNode->addChild(this->wheelFront);
	this->frontNode->addChild(this->wheelBack);
}

MineCart::~MineCart()
{
}

void MineCart::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void MineCart::initializePositions()
{
	super::initializePositions();

	this->bottomCollision->setPositionY(-108.0f);
	this->wheelBack->setPosition(Vec2(-32.0f, -64.0f));
	this->wheelFront->setPosition(Vec2(32.0f, -69.0f));
}

void MineCart::initializeListeners()
{
	super::initializeListeners();
	
	this->interactCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::CartStop }, [=](CollisionData collisionData)
	{
		this->reverse();
		this->dismountAll();
		
		return CollisionResult::CollideWithPhysics;
	});
}

void MineCart::update(float dt)
{
	super::update(dt);

	this->updateCanMove();
	this->moveMount(dt);
	this->faceEntityTowardsDirection();
}

Vec2 MineCart::getButtonOffset()
{
	return Vec2(0.0f, -64.0f);
}

void MineCart::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_CAN_MOVE,
			HackableCode::HackableCodeInfo(
				MineCart::MapKey,
				Strings::Menus_Hacking_Objects_MineCart_IsMoving_IsMoving::create(),
				HackableBase::HackBarColor::Gray,
				UIResources::Menus_Icons_GearBroken,
				LazyNode<HackablePreview>::create([=](){ return MineCartPreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_MineCart_IsMoving_RegisterEax::create() },
				},
				int(HackFlags::None),
				2.5f,
				0.0f
			)
		},
	};

	std::vector<HackableCode*> hackables = CREATE_HACKABLES(MineCart::updateCanMove, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* MineCart::createDefaultPreview()
{
	return MineCartPreview::create();
}

void MineCart::mount(PlatformerEntity* interactingEntity)
{
	super::mount(interactingEntity);

	this->faceEntityTowardsDirection();

	this->isMoving = true;
}

void MineCart::dismount(PlatformerEntity* entity)
{
	super::dismount(entity);
	
	this->isMoving = false;
}

NO_OPTIMIZE void MineCart::updateCanMove()
{
	static volatile int canMoveLocal = 0;

	// GCC will seg fault if this is updated at the end of the function. So hacking this is on a 1-frame delay.
	this->canMoveOverride = bool(canMoveLocal);

	canMoveLocal = 1;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(eax, canMoveLocal);
	ASM(mov ZBX, 0);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CAN_MOVE);
	ASM(cmp eax, 1);
	ASM_NOP16();
	HACKABLE_CODE_END();
	
	ASM(cmovne ZAX, ZBX);

	ASM_MOV_VAR_REG(canMoveLocal, eax);

	ASM(pop ZBX);
	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE

Vec2 MineCart::getReparentPosition()
{
	return Vec2(0.0f, 32.0f);
}

void MineCart::parseColor()
{
	std::string color = GameUtils::getKeyOrDefault(this->properties, GameObject::PropertyColor, Value("")).asString();

	if (color == "blue")
	{
		this->cartColor = CartColor::Blue;
	}
	else // if (color == "brown")
	{
		this->cartColor = CartColor::Brown;
	}
}
