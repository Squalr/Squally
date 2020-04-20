#include "Fireball.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Projectiles/Combat/Fireball/FireballClippy.h"
#include "Objects/Platformer/Projectiles/Combat/Fireball/FireballGenericPreview.h"
#include "Objects/Platformer/Projectiles/Combat/Fireball/FireballSpeedPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_FIREBALL_SPEED 11

Fireball* Fireball::create(PlatformerEntity* owner, PlatformerEntity* target)
{
	Fireball* instance = new Fireball(owner, target);

	instance->autorelease();

	return instance;
}

Fireball::Fireball(PlatformerEntity* owner, PlatformerEntity* target)
	: super(owner, target, true, Node::create(), Size(32.0f, 32.0f))
{
	this->fireballAnim = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->explosionAnim = SmartAnimationSequenceNode::create();
	this->breathSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Fireball2);
	this->impactSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_FireHit1);
	this->reverseClippy = FireballClippy::create();

	this->fireballAnim->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.05f);

	this->registerClippy(this->reverseClippy);
	this->postFXNode->addChild(this->breathSound);
	this->postFXNode->addChild(this->impactSound);
	this->postFXNode->addChild(this->explosionAnim);
	this->object->addChild(this->fireballAnim);
}

Fireball::~Fireball()
{
}

void Fireball::update(float dt)
{
	super::update(dt);

	if (!this->canUpdate)
	{
		return;
	}

	this->setFireballSpeed();
}

void Fireball::enableClippy()
{
	this->reverseClippy->setIsEnabled(true);
}

void Fireball::runSpawnFX()
{
	this->breathSound->play();
}

void Fireball::runImpactFX()
{
	this->explosionAnim->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);

	this->impactSound->play();
}

Vec2 Fireball::getButtonOffset()
{
	return Vec2::ZERO;
}

void Fireball::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_FIREBALL_SPEED,
			HackableCode::HackableCodeInfo(
				"Fireball",
				Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_ApplySpeed::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_FireBalls,
				FireballSpeedPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_RegisterXmm1::create() }
				},
				int(HackFlags::None),
				3.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_StopFireball::create(),
						// x86
						COMMENT(Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_CommentXmmLoading::create()->
							setStringReplacementVariables(Strings::Common_Brackets::create()->
							setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()))) + 
						COMMENT(Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_CommentAlterSpeed::create()) + 
						"mov dword ptr [eax], 0.0f\n"
						"movss xmm1, dword ptr [eax]\n\n"
						"mulps xmm0, xmm1",
						// x64
						COMMENT(Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_CommentXmmLoading::create()->
							setStringReplacementVariables(Strings::Common_Brackets::create()->
							setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()))) + 
						COMMENT(Strings::Menus_Hacking_Objects_Combat_Projectiles_Fireball_ApplySpeed_CommentAlterSpeed::create()) + 
						"mov dword ptr [rax], 0.0f\n"
						"movss xmm1, dword ptr [rax]\n\n"
						"mulps xmm0, xmm1"
					)
				}
			)
		},
	};

	auto fireballFunc = &Fireball::setFireballSpeed;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)fireballFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* Fireball::createDefaultPreview()
{
	return FireballGenericPreview::create();
}

NO_OPTIMIZE void Fireball::setFireballSpeed()
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
	ASM_MOV_REG_VAR(ZAX, speedMultiplierPtr);
	ASM(movss xmm0, dword ptr [ZAX]);
	ASM_MOV_REG_VAR(ZAX, speedMultiplierTempPtr);
	ASM(movss xmm1, dword ptr [ZAX]);
	ASM(pop ZAX);

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, freeMemoryForUser);
	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_FIREBALL_SPEED);
	ASM(mulps xmm0, xmm1);
	ASM_NOP16();
	HACKABLE_CODE_END();
	ASM(pop ZAX);

	ASM(push ZAX);
	ASM_MOV_REG_VAR(ZAX, speedMultiplierPtr);
	ASM(movss dword ptr [ZAX], xmm0);
	ASM(pop ZAX);

	this->setSpeedMultiplier(Vec3(speedMultiplier, speedMultiplier, speedMultiplier));

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
