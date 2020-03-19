#include "SquallyReceiveItemBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Inventory/Currency.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/CurrencyPool.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Localization/ConstantString.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SquallyReceiveItemBehavior::MapKey = "squally-receive-item";

SquallyReceiveItemBehavior* SquallyReceiveItemBehavior::create(GameObject* owner)
{
	SquallyReceiveItemBehavior* instance = new SquallyReceiveItemBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyReceiveItemBehavior::SquallyReceiveItemBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyReceiveItemBehavior::~SquallyReceiveItemBehavior()
{
}

void SquallyReceiveItemBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveItem, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveItemArgs* args = static_cast<PlatformerEvents::GiveItemArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->item != nullptr)
		{
			NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
				args->messageOverride == nullptr ? Strings::Platformer_Notifications_ItemFound::create() : args->messageOverride,
				args->item->getString(),
				args->item->getIconResource(),
				SoundResources::Notifications_NotificationGood3
			));

			this->squally->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				entityInventoryBehavior->getInventory()->forceInsert(args->item, true);
			});
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveItemsFromPool, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveItemsFromPoolArgs* args = static_cast<PlatformerEvents::GiveItemsFromPoolArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->pool != nullptr)
		{
			this->squally->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				std::vector<Item*> items = args->pool->getItems(entityInventoryBehavior->getAllInventories());

				for (auto item : items)
				{
					if (item == nullptr)
					{
						continue;
					}

					NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
						args->messageOverride == nullptr ? Strings::Platformer_Notifications_ItemFound::create() : args->messageOverride,
						item->getString(),
						item->getIconResource(),
						SoundResources::Notifications_NotificationGood3
					));

					entityInventoryBehavior->getInventory()->forceInsert(item, true);
				}
			});
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveCurrency, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveCurrencyArgs* args = static_cast<PlatformerEvents::GiveCurrencyArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->currency != nullptr && args->currency->getCount() > 0)
		{
			NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
				args->messageOverride == nullptr ? Strings::Platformer_Notifications_ItemFound::create() : args->messageOverride,
				Strings::Common_TimesConstant::create()->setStringReplacementVariables(ConstantString::create(std::to_string(args->currency->getCount()))),
				args->currency->getIconResource(),
				SoundResources::Notifications_NotificationGood3
			));

			this->squally->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				entityInventoryBehavior->getCurrencyInventory()->addCurrency(args->currency->getSerializationKey(), args->currency->getCount());
			});
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveCurrenciesFromPool, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveCurrenciesFromPoolArgs* args = static_cast<PlatformerEvents::GiveCurrenciesFromPoolArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->pool != nullptr)
		{
			this->squally->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				std::vector<Currency*> currencies = args->pool->getRandomCurrencyFromPool();

				for (auto currency : currencies)
				{
					if (currency == nullptr || currency->getCount() <= 0)
					{
						continue;
					}

					NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
						args->messageOverride == nullptr ? Strings::Platformer_Notifications_ItemFound::create() : args->messageOverride,
						Strings::Common_TimesConstant::create()->setStringReplacementVariables(ConstantString::create(std::to_string(currency->getCount()))),
						currency->getIconResource(),
						SoundResources::Notifications_NotificationGood3
					));

					entityInventoryBehavior->getCurrencyInventory()->addCurrency(currency->getSerializationKey(), currency->getCount());
				}
			});
		}
	}));
}

void SquallyReceiveItemBehavior::onDisable()
{
	super::onDisable();
}
