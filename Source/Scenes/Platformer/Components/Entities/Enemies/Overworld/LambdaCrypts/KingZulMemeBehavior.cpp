#include "KingZulMemeBehavior.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string KingZulMemeBehavior::MapKey = "king-zul-meme";

KingZulMemeBehavior* KingZulMemeBehavior::create(GameObject* owner)
{
	KingZulMemeBehavior* instance = new KingZulMemeBehavior(owner);

	instance->autorelease();

	return instance;
}

KingZulMemeBehavior::KingZulMemeBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

KingZulMemeBehavior::~KingZulMemeBehavior()
{
}

void KingZulMemeBehavior::onLoad()
{
	this->entity->listenForMapEventOnce(KingZulMemeBehavior::MapKey, [=](ValueMap args)
	{
		if (this->entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->entity->getAnimations()->clearAnimationPriority();
			this->entity->getAnimations()->playAnimation("Meme");
		}
	});
}
