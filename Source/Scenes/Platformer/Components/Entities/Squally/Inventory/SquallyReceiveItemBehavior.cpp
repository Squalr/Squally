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
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"

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
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveItems, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveItemsArgs* args = static_cast<PlatformerEvents::GiveItemsArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->obtainItems(args->items, args->messageOverride, args->keepOpen);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveItemsFromPool, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveItemsFromPoolArgs* args = static_cast<PlatformerEvents::GiveItemsFromPoolArgs*>(eventCustom->getData());

		if (args != nullptr && args->pool != nullptr)
		{
			this->squally->getComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				this->obtainItems(args->pool->getItems(entityInventoryBehavior->getAllInventories()), args->messageOverride, args->keepOpen);
			});
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveCurrency, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveCurrencyArgs* args = static_cast<PlatformerEvents::GiveCurrencyArgs*>(eventCustom->getData());

		if (args != nullptr && args->currency != nullptr && args->currency->getCount() > 0)
		{
			NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
				args->messageOverride,
				Strings::Common_Concat::create()->setStringReplacementVariables({
					args->currency->getString(),
					Strings::Common_TimesConstant::create()->setStringReplacementVariables(ConstantString::create(std::to_string(args->currency->getCount())))
				}),
				args->currency->getIconResource(),
				SoundResources::Notifications_NotificationGood3,
				args->keepOpen
			));

			this->squally->getComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				entityInventoryBehavior->getCurrencyInventory()->addCurrency(args->currency->getIdentifier(), args->currency->getCount());
			});
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveCurrenciesFromPool, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveCurrenciesFromPoolArgs* args = static_cast<PlatformerEvents::GiveCurrenciesFromPoolArgs*>(eventCustom->getData());
		
		if (args != nullptr && args->pool != nullptr)
		{
			this->squally->getComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				std::vector<Currency*> currencies = args->pool->getRandomCurrencyFromPool();

				for (auto currency : currencies)
				{
					if (currency == nullptr || currency->getCount() <= 0)
					{
						continue;
					}

					NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
						args->messageOverride,
						Strings::Common_Concat::create()->setStringReplacementVariables({
							currency->getString(),
							Strings::Common_TimesConstant::create()->setStringReplacementVariables(ConstantString::create(std::to_string(currency->getCount())))
						}),
						currency->getIconResource(),
						SoundResources::Notifications_NotificationGood3,
						args->keepOpen
					));

					entityInventoryBehavior->getCurrencyInventory()->addCurrency(currency->getIdentifier(), currency->getCount());
				}
			});
		}
	}));
}

void SquallyReceiveItemBehavior::onDisable()
{
	super::onDisable();
}

void SquallyReceiveItemBehavior::obtainItems(const std::vector<Item*>& items, LocalizedString* messageOverride, bool keepOpen)
{
	if (this->squally == nullptr)
	{
		return;
	}

	this->squally->getComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		std::map<std::string, std::vector<Item*>> itemsById = std::map<std::string, std::vector<Item*>>();

		for (Item* item : items)
		{
			if (item == nullptr)
			{
				continue;
			}

			itemsById[item->getIdentifier()].push_back(item);
			entityInventoryBehavior->getInventory()->forceInsert(item, false);
		}

		entityInventoryBehavior->getInventory()->save();
		
		for (const auto& [id, itemsOfId] : itemsById)
		{
			if (itemsOfId.size() < 1)
			{
				continue;
			}

			NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
				messageOverride,
				itemsOfId.size() <= 1 ? itemsOfId[0]->getString() : Strings::Common_ConcatSpaced::create()->setStringReplacementVariables(
				{
					itemsOfId[0]->getString(),
					Strings::Common_Parenthesis::create()->setStringReplacementVariables(
						Strings::Common_TimesConstant::create()->setStringReplacementVariables(
							ConstantString::create(std::to_string(itemsOfId.size()))
						)
					)
				}),
				itemsOfId[0]->getIconResource(),
				SoundResources::Notifications_NotificationGood3,
				keepOpen
			));
		}
	});
}
