#include "Waterball.h"

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
#include "Objects/Platformer/Combat/Projectiles/Waterball/WaterballGenericPreview.h"
#include "Objects/Platformer/Combat/Projectiles/Waterball/WaterballSpeedPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_FIREBALL_SPEED 11

const std::string Waterball::HackIdentifierWaterballSpeed = "waterball-speed";

Waterball* Waterball::create(PlatformerEntity* owner, PlatformerEntity* target)
{
	Waterball* instance = new Waterball(owner, target);

	instance->autorelease();

	return instance;
}

Waterball::Waterball(PlatformerEntity* owner, PlatformerEntity* target)
	: super(owner, target, true, Node::create(), CSize(32.0f, 32.0f))
{
	this->waterballAnim = SmartAnimationSequenceNode::create();

	this->explosionAnim = SmartAnimationSequenceNode::create();
	this->breathSound = WorldSound::create(SoundResources::Platformer_Spells_Fireball2);
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);

	this->postFXNode->addChild(this->breathSound);
	this->postFXNode->addChild(this->impactSound);
	this->postFXNode->addChild(this->explosionAnim);
	this->object->addChild(this->waterballAnim);
}

Waterball::~Waterball()
{
}

void Waterball::update(float dt)
{
	super::update(dt);

	if (!this->canUpdate)
	{
		return;
	}

	this->setWaterballSpeed();
}

void Waterball::runSpawnFX()
{
	this->breathSound->play();
	this->waterballAnim->playAnimationRepeat(FXResources::WaterBall_WaterBall_0000, 0.05f);
}

void Waterball::runImpactFX()
{
	this->explosionAnim->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);
	this->waterballAnim->stopAnimation();
	this->setLaunchVelocity(Vec3::ZERO);

	this->impactSound->play();
}

Vec2 Waterball::getButtonOffset()
{
	return Vec2::ZERO;
}

void Waterball::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FIREBALL_SPEED,
			HackableCode::HackableCodeInfo(
				Waterball::HackIdentifierWaterballSpeed,
				Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_ApplySpeed::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_FireSphere,
				LazyNode<HackablePreview>::create([=](){ return WaterballSpeedPreview::create(); }),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_RegisterXmm1::create() }
				},
				int(HackFlags::None),
				3.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_StopWaterball::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_CommentXmmLoading::create()->
							setStringReplacementVariables(Strings::Common_Brackets::create()->
							setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_CommentAlterSpeed::create()) + 
						"mov dword ptr [eax], 0.0f\n"
						"movss xmm1, dword ptr [eax]\n\n"
						"mulps xmm0, xmm1"
						, // x64
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_CommentXmmLoading::create()->
							setStringReplacementVariables(Strings::Common_Brackets::create()->
							setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()))) + 
						COMMENT(Strings::Menus_Hacking_Abilities_Abilities_Waterball_ApplySpeed_CommentAlterSpeed::create()) + 
						"mov dword ptr [rax], 0.0f\n"
						"movss xmm1, dword ptr [rax]\n\n"
						"mulps xmm0, xmm1"
					)
				}
			)
		},
	};

	std::vector<HackableCode*> hackables = CREATE_HACKABLES(Waterball::setWaterballSpeed, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* Waterball::createDefaultPreview()
{
	return WaterballGenericPreview::create();
}

NO_OPTIMIZE void Waterball::setWaterballSpeed()
{
	static volatile float* freeMemoryForUser = new float[16];
	static volatile float speedMultiplier;
	static volatile float speedMultiplierTemp;
	static volatile float* speedMultiplierPtr;
	static volatile float* speedMultiplierTempPtr;

	speedMultiplier = 1.0f;
	speedMultiplierTemp = 1.0f;
	speedMultiplierPtr = &speedMultiplier;
	speedMultiplierTempPtr = &speedMultiplierTemp;

	// Initialize xmm0 and xmm1
	ASM(push ZAX);
	ASM_MOV_REG_PTR(ZAX, speedMultiplierPtr);
	ASM(movss xmm0, dword ptr [ZAX]);
	ASM_MOV_REG_PTR(ZAX, speedMultiplierTempPtr);
	ASM(movss xmm1, dword ptr [ZAX]);
	ASM_MOV_REG_PTR(ZAX, freeMemoryForUser);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FIREBALL_SPEED);
	ASM(mulps xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();

	ASM_MOV_REG_PTR(ZAX, speedMultiplierPtr);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM(pop ZAX);

	this->setSpeedMultiplier(Vec3(speedMultiplier, speedMultiplier, speedMultiplier));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
