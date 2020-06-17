#include "Pacifist.h"

#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string Pacifist::PacifistIdentifier = "pacifist";

Pacifist* Pacifist::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Pacifist* instance = new Pacifist(caster, target);

	instance->autorelease();

	return instance;
}

Pacifist::Pacifist(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Physical, BuffData(-1.0f, Pacifist::PacifistIdentifier))
{
	if (this->caster != nullptr)
	{
		this->caster->setState(StateKeys::IsPacifist, Value(true));
	}
}

Pacifist::~Pacifist()
{
}
