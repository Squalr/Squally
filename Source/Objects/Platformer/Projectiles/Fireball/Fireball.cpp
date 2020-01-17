#include "Fireball.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Projectiles/ThrownObject/ThrownObject.h"
#include "Objects/Platformer/Projectiles/Fireball/FireballGenericPreview.h"
#include "Objects/Platformer/Projectiles/Fireball/FireballSpeedPreview.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FxResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_FIREBALL_SPEED 11

Fireball* Fireball::create(PlatformerEntity* owner, PlatformerAttack* attack)
{
	Fireball* instance = new Fireball(owner, attack);

	instance->autorelease();

	return instance;
}

Fireball::Fireball(PlatformerEntity* owner, PlatformerAttack* attack) : super(owner, SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000), Size(32.0f, 32.0f))
{
	SmartAnimationSequenceNode* fireballAnim = dynamic_cast<SmartAnimationSequenceNode*>(this->object);

	this->toggleHackable(false);

	fireballAnim->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.05f);

	this->getCollision()->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
		this->getCollision()->setPhysicsEnabled(false);
		this->setVisible(false);

		// Explosion animation
		SmartAnimationSequenceNode* explosionAnim = SmartAnimationSequenceNode::create(FXResources::Explosion_Explosion_0000);
		WorldSound* impactSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_FireHit1);
		
		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, explosionAnim, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
		explosionAnim->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);
		explosionAnim->setPosition3D(GameUtils::getWorldCoords3D(this));
		explosionAnim->addChild(impactSound);

		impactSound->play();

		PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

		if (entity != nullptr)
		{
			CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(owner, entity, attack->getRandomDamage()));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
}

Fireball::~Fireball()
{
}

void Fireball::update(float dt)
{
	super::update(dt);

	this->setFireballSpeed();
}

Vec2 Fireball::getButtonOffset()
{
	return this->getPosition();
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
				Strings::Menus_Hacking_Objects_Fireball_ApplySpeed_ApplySpeed::create(),
				UIResources::Menus_Icons_CrossHair,
				FireballSpeedPreview::create(),
				{
					{ HackableCode::Register::zax, Strings::Menus_Hacking_Objects_Fireball_ApplySpeed_RegisterEax::create() },
					{ HackableCode::Register::xmm0, Strings::Menus_Hacking_Objects_Fireball_ApplySpeed_RegisterXmm0::create() },
					{ HackableCode::Register::xmm1, Strings::Menus_Hacking_Objects_Fireball_ApplySpeed_RegisterXmm1::create() }
				},
				int(HackFlags::None),
				5.0f,
				nullptr,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_Objects_Fireball_ApplySpeed_StopFireball::create(),
						// x86
						"mov dword ptr [eax], 0.0\n"
						"movss xmm1, dword ptr [eax]\n\n"
						"mulps xmm0, xmm1",
						// x64
						"mov dword ptr [rax], 0.0\n"
						"movss xmm1, dword ptr [rax]\n\n"
						"mulps xmm0, xmm1"
					)
				}
			)
		},
	};

	auto fireballFunc = &Fireball::setFireballSpeed;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)fireballFunc, codeInfoMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->registerCode(*it);
	}
}

HackablePreview* Fireball::createDefaultPreview()
{
	return FireballGenericPreview::create();
}

NO_OPTIMIZE void Fireball::setFireballSpeed()
{
	volatile static float* freeMemoryForUser = new float[16];
	volatile float speedMultiplier = 1.0f;
	volatile float speedMultiplierTemp = 1.0f;
	volatile float* speedMultiplierPtr = &speedMultiplier;
	volatile float* speedMultiplierTempPtr = &speedMultiplierTemp;

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
}
END_NO_OPTIMIZE
