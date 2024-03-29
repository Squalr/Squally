#include "CartSpawn.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Interactables/Mounts/MineCart/MineCart.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string CartSpawn::MapKey = "spawn-cart";
const std::string CartSpawn::PropertyLinkTag = "link-tag";
const std::string CartSpawn::PropertyDirection = "direction";

CartSpawn* CartSpawn::create(ValueMap& properties)
{
	CartSpawn* instance = new CartSpawn(properties);

	instance->autorelease();

	return instance;
}

CartSpawn::CartSpawn(ValueMap& properties) : super(properties)
{
	this->linkTag = GameUtils::getKeyOrDefault(this->properties, CartSpawn::PropertyLinkTag, Value("")).asString();
	this->direction = GameUtils::getKeyOrDefault(this->properties, CartSpawn::PropertyDirection, Value("")).asString();
}

CartSpawn::~CartSpawn()
{
}

void CartSpawn::onPlayerSpawn(PlatformerEntity* entity)
{
	super::onPlayerSpawn(entity);

	this->enterCart(entity);
}

void CartSpawn::enterCart(PlatformerEntity* entity)
{
	// Hack to avoid some data race where the cart does not properly warp to the player
	this->defer([=]()
	{
		ObjectEvents::WatchForObject<MineCart>(this, [=](MineCart* mineCart)
		{
			mineCart->setPositionX(this->getPositionX());
			mineCart->mount(entity);

			if (this->direction == "left")
			{
				mineCart->setMountDirection(MountBase::MountDirection::Left);
			}
			else
			{
				mineCart->setMountDirection(MountBase::MountDirection::Right);
			}
		}, this->linkTag);
	}, 1);
}
