#include "GhostBolt.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/GhostBolt/GhostBoltGenericPreview.h"
#include "Objects/Platformer/Combat/Projectiles/GhostBolt/GhostBoltSpeedPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_GHOST_BOLT 11

const std::string GhostBolt::HackIdentifierGhostBoltSpeed = "ghost-bolt-speed";

GhostBolt* GhostBolt::create(PlatformerEntity* owner, PlatformerEntity* target)
{
	GhostBolt* instance = new GhostBolt(owner, target);

	instance->autorelease();

	return instance;
}

GhostBolt::GhostBolt(PlatformerEntity* owner, PlatformerEntity* target)
	: super(owner, target, true, Node::create(), CSize(32.0f, 32.0f))
{
	this->fireballAnim = SmartAnimationSequenceNode::create();

	this->explosionAnim = SmartAnimationSequenceNode::create();
	this->breathSound = WorldSound::create(SoundResources::Platformer_Spells_Fireball2);
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);

	this->postFXNode->addChild(this->breathSound);
	this->postFXNode->addChild(this->impactSound);
	this->postFXNode->addChild(this->explosionAnim);
	this->object->addChild(this->fireballAnim);
}

GhostBolt::~GhostBolt()
{
}

void GhostBolt::update(float dt)
{
	super::update(dt);

	if (!this->canUpdate)
	{
		return;
	}

	this->setGhostBoltSpeed();
}

void GhostBolt::runSpawnFX()
{
	this->breathSound->play();
	this->fireballAnim->playAnimationRepeat(FXResources::GhostBolt_GhostBolt_0000, 0.05f);
}

void GhostBolt::runImpactFX()
{
	this->explosionAnim->playAnimation(FXResources::ShadowImpact_ShadowImpact_0000, 0.05f, true);
	this->fireballAnim->stopAnimation();
	this->setLaunchVelocity(Vec3::ZERO);

	this->impactSound->play();
}

Vec2 GhostBolt::getButtonOffset()
{
	return Vec2::ZERO;
}

void GhostBolt::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_GHOST_BOLT,
			HackableCode::HackableCodeInfo(
				GhostBolt::HackIdentifierGhostBoltSpeed,
				Strings::Menus_Hacking_Abilities_Abilities_GhostBolt_ApplySpeed_ApplySpeed::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_GhostBolts,
				LazyNode<HackablePreview>::create([=](){ return GhostBoltSpeedPreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Abilities_GhostBolt_ApplySpeed_RegisterEax::create(), true },
				},
				int(HackFlags::None),
				3.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Abilities_GhostBolt_ApplySpeed_ApplySpeed::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFld1::create()) +
						std::string("fld1\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFchs::create()) +
						std::string("fchs\n") +
						std::string("fstp dword ptr [eax]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_GhostBolt_ApplySpeed_CommentHint::create())
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFld1::create()) +
						std::string("fld1\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_FPU_CommentFchs::create()) +
						std::string("fchs\n") +
						std::string("fstp dword ptr [rax]\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalance::create()) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPush::create()) +
						COMMENT(Strings::Menus_Hacking_Abilities_Generic_Stack_CommentStackBalanceFPUPop::create()) +
						std::string("\n\n") +
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_GhostBolt_ApplySpeed_CommentHint::create())
					)
				},
				true
			)
		},
	};

	std::vector<HackableCode*> hackables = CREATE_HACKABLES(GhostBolt::setGhostBoltSpeed, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* GhostBolt::createDefaultPreview()
{
	return GhostBoltGenericPreview::create();
}

NO_OPTIMIZE void GhostBolt::setGhostBoltSpeed()
{
	static volatile float speedMultiplier;
	static volatile float* speedMultiplierPtr;

	speedMultiplier = 0.0f;
	speedMultiplierPtr = &speedMultiplier;

	ASM_PUSH_EFLAGS();
	ASM(push ZAX);

	ASM_MOV_REG_PTR(ZAX, speedMultiplierPtr);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_GHOST_BOLT);
	ASM(fld1);
	ASM(fchs);
	ASM(fstp dword ptr [ZAX]);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM(pop ZAX);
	ASM_POP_EFLAGS();

	speedMultiplier = speedMultiplier * -1.0f;
	
	this->setSpeedMultiplier(Vec3(speedMultiplier, speedMultiplier, speedMultiplier));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
