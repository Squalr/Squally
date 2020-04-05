#include "Bombed.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"


#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_STRENGTH 1

const std::string Bombed::BombedIdentifier = "strength";

Bombed* Bombed::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Bombed* instance = new Bombed(caster, target);

	instance->autorelease();

	return instance;
}

Bombed::Bombed(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, BuffData(Bombed::Duration, Bombed::BombedIdentifier))
{
}

Bombed::~Bombed()
{
}
