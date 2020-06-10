#include "HealthLinkAutoCast.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/HealthLink/HealthLink.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string HealthLinkAutoCast::HealthLinkAutoCastIdentifier = "undying-auto-cast";

HealthLinkAutoCast* HealthLinkAutoCast::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	HealthLinkAutoCast* instance = new HealthLinkAutoCast(caster, target);

	instance->autorelease();

	return instance;
}

HealthLinkAutoCast::HealthLinkAutoCast(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", BuffData(-1.0f, HealthLinkAutoCast::HealthLinkAutoCastIdentifier))
{
	this->hasAutoCasted = false;
}

HealthLinkAutoCast::~HealthLinkAutoCast()
{
}

void HealthLinkAutoCast::onBeforeDamageTaken(volatile int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
	super::onBeforeDamageTaken(damageOrHealing, handleCallback, caster, target);

	if (this->hasAutoCasted)
	{
		return;
	}

	int originalHealth = target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);
	int newHealth = originalHealth - *damageOrHealing;

	if (newHealth <= 0)
	{
		target->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			this->hasAutoCasted = true;

			entityBuffBehavior->applyBuff(HealthLink::create(target, target));
			entityBuffBehavior->getBuff<HealthLink>([&](HealthLink* undying)
			{
				undying->onBeforeDamageTaken(damageOrHealing, handleCallback, caster, target);
			});
		});
	}
}
