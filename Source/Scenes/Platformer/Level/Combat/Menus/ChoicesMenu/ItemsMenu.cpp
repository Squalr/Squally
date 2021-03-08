#include "ItemsMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float ItemsMenu::Radius = 384.0f;

ItemsMenu* ItemsMenu::create()
{
	ItemsMenu* instance = new ItemsMenu();

	instance->autorelease();

	return instance;
}

ItemsMenu::ItemsMenu() : super(ItemsMenu::Radius, float(M_PI) / 9.0f)
{
	this->hasItemsInList = false;
}

ItemsMenu::~ItemsMenu()
{
}

bool ItemsMenu::hasItems()
{
	return this->hasItemsInList;
}

void ItemsMenu::buildItemList(TimelineEntry* entry)
{
	this->clearItems();
	this->hasItemsInList = false;

	if (entry == nullptr)
	{
		return;
	}

	PlatformerEntity* entity = entry->getEntity();

	if (entity == nullptr)
	{
		return;
	}

	entity->getAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		int index = 0;

		std::map<std::string, std::tuple<int, PlatformerAttack*>> consumablesMap = std::map<std::string, std::tuple<int, PlatformerAttack*>>();
		
		for (auto consumable : attackBehavior->getAvailableConsumables())
		{
			const std::string identifier = consumable->getIdentifier();

			if (!consumablesMap.contains(identifier))
			{
				consumablesMap[identifier] = std::make_tuple<int, PlatformerAttack*>(1, consumable->getAssociatedAttack(entity));
			}
			else
			{
				std::get<0>(consumablesMap[identifier])++;
			}
		}

		for (auto next : consumablesMap)
		{
			this->hasItemsInList = true;

			int count = std::get<0>(next.second);
			PlatformerAttack* attack = std::get<1>(next.second);
			
			LocalizedString* countString = Strings::Common_Brackets::create()
				->setStringReplacementVariables(Strings::Common_TimesConstant::create()
				->setStringReplacementVariables(ConstantString::create(std::to_string(count))));
			LocalizedString* menuString = Strings::Common_ConcatSpaced::create()->setStringReplacementVariables({ attack->getString(), countString });
			LocalizedString* description = attack->getDescription();

			this->addEntry(menuString, { description }, attack->getIconResource(), UIResources::Combat_ItemsCircle, [=]()
			{
				this->scrollTo(index);

				entry->stageCast(attack->clone());

				switch (attack->getAttackType())
				{
					case PlatformerAttack::AttackType::Healing:
					case PlatformerAttack::AttackType::Buff:
					{
						auto meta = CombatEvents::MenuStateArgs::SelectionMeta(CombatEvents::MenuStateArgs::SelectionMeta::Choice::Item, attack->getIconResource());
						CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget, entry, meta));
						break;
					}
					case PlatformerAttack::AttackType::Resurrection:
					{
						auto meta = CombatEvents::MenuStateArgs::SelectionMeta(CombatEvents::MenuStateArgs::SelectionMeta::Choice::Item, attack->getIconResource());
						CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseResurrectionTarget, entry, meta));
						break;
					}
					case PlatformerAttack::AttackType::Damage:
					case PlatformerAttack::AttackType::Debuff:
					{
						auto meta = CombatEvents::MenuStateArgs::SelectionMeta(CombatEvents::MenuStateArgs::SelectionMeta::Choice::Item, attack->getIconResource());
						CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget, entry, meta));
						break;
					}
					default:
					{
						auto meta = CombatEvents::MenuStateArgs::SelectionMeta(CombatEvents::MenuStateArgs::SelectionMeta::Choice::Item, attack->getIconResource());
						CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget, entry, meta));
						break;
					}
				}
			});

			index++;
		}
	});
}
