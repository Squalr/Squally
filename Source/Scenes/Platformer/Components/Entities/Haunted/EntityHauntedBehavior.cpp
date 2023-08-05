#include "EntityHauntedBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/InteractObject.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/MedusaMirror.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/CureKingLine.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/UnhauntCastle.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EntityHauntedBehavior::MapKey = "haunted";
const std::string EntityHauntedBehavior::PropertyOtherWorld = "other-world";
const std::string EntityHauntedBehavior::PropertyHauntedKey = "haunted-key";

EntityHauntedBehavior* EntityHauntedBehavior::create(GameObject* owner)
{
	EntityHauntedBehavior* instance = new EntityHauntedBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityHauntedBehavior::EntityHauntedBehavior(GameObject* owner) : super(owner)
{
	this->ownerAsEnemy = dynamic_cast<PlatformerEnemy*>(owner);
	this->ownerAsFriendly = dynamic_cast<PlatformerFriendly*>(owner);

	if (this->ownerAsEnemy == nullptr && this->ownerAsFriendly == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->isOtherWorld = GameUtils::getKeyOrDefault(this->owner->properties, EntityHauntedBehavior::PropertyOtherWorld, Value(false)).asBool();
		this->hauntedKey = GameUtils::getKeyOrDefault(this->owner->properties, EntityHauntedBehavior::PropertyHauntedKey, Value("")).asString();
	}
}

EntityHauntedBehavior::~EntityHauntedBehavior()
{
}

void EntityHauntedBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	if (this->ownerAsFriendly != nullptr)
	{
		if (this->isOtherWorld)
		{
			this->ownerAsFriendly->getAnimations()->setOpacity(127);
		}

		if (!this->hauntedKey.empty())
		{
			this->ownerAsFriendly->setState(StateKeys::PatrolHijacked, Value(true));
			
			// Defer 1 frame to give the dead enemy a chance to persist the save key
			this->defer([=]()
			{
				// Hack to remove interaction
				this->ownerAsFriendly->watchForComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
				{
					healthBehavior->kill();
				});

				this->ownerAsFriendly->watchForComponent<HexusBehaviorBase>([=](HexusBehaviorBase* hexusBehavior)
				{
					hexusBehavior->setVisible(false);
				});

				bool isUnhaunted = SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyPrefixUnhaunted + this->hauntedKey, Value(false)).asBool();

				if (!isUnhaunted)
				{
					this->ownerAsFriendly->getAnimations()->playAnimation("Cower", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f, 0.5f, true));
					
					if (!this->isOtherWorld)
					{
						this->ownerAsFriendly->listenForMapEventOnce(this->ownerAsFriendly->getEntityKey(), [=](ValueMap)
						{
							this->ownerAsFriendly->getComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
							{
								interactionBehavior->getSpeechBubble()->runDialogue(
									this->getNextHauntedSpeechBubbleText(),
									Voices::GetNextVoiceShort(Voices::VoiceType::Human)
								);
							});
						});
					}
				}
				else if (isUnhaunted && !this->isOtherWorld)
				{
					this->ownerAsFriendly->listenForMapEventOnce(this->ownerAsFriendly->getEntityKey(), [=](ValueMap)
					{
						this->ownerAsFriendly->getComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
						{
							LocalizedString* dialog = this->getNextUnhauntedSpeechBubbleText();

							if (dialog != nullptr)
							{
								interactionBehavior->getSpeechBubble()->runDialogue(
									dialog,
									Voices::GetNextVoiceShort(Voices::VoiceType::Human)
								);
							}
						});
					});
				}
			});
		}
	}
	else if (this->ownerAsEnemy != nullptr)
	{
		if (this->isOtherWorld)
		{
			this->ownerAsEnemy->getAnimations()->setOpacity(127);
		}

		if (!this->hauntedKey.empty())
		{
			bool isAlive = this->ownerAsEnemy->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool();
			bool isUnhaunted = SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyPrefixUnhaunted + this->hauntedKey, Value(false)).asBool();

			// Increase unhaunted count (only once) if this enemy is dead
			if (!isUnhaunted && !isAlive)
			{
				this->unhaunt();
			}
			else
			{
				this->ownerAsEnemy->listenForStateWriteOnce(StateKeys::IsAlive, [=](Value)
				{
					this->unhaunt();
				});
			}

			// This enemy is linked to a enemy on another map that is unhaunted. Kill it!
			if (isUnhaunted && isAlive)
			{
				this->ownerAsEnemy->watchForComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
				{
					healthBehavior->kill();
				});
			}
		}
	}
}

void EntityHauntedBehavior::onDisable()
{
	super::onDisable();
}

bool EntityHauntedBehavior::isUnhaunted() const
{
	return SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyPrefixUnhaunted + this->hauntedKey, Value(false)).asBool();
}

void EntityHauntedBehavior::unhaunt()
{
	bool isUnhaunted = SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeyPrefixUnhaunted + this->hauntedKey, Value(false)).asBool();

	if (!isUnhaunted)
	{
		SaveManager::SoftSaveProfileData(UnhauntCastle::SaveKeyPrefixUnhaunted + this->hauntedKey, Value(true));
	}
}

void EntityHauntedBehavior::onSoulHarvested()
{
	int newSoulHarvestedCount = SaveManager::GetProfileDataOrDefault(UnhauntCastle::SaveKeySoulHarvestedCount, Value(0)).asInt() + 1;
	SaveManager::SoftSaveProfileData(UnhauntCastle::SaveKeySoulHarvestedCount, Value(newSoulHarvestedCount));

	if (newSoulHarvestedCount >= UnhauntCastle::MaxUnhauntCount)
	{
		Objectives::SetCurrentObjective(ObjectiveKeys::CVReturnToMabel);
	}

	this->showRemainingSoulsDialogue(UnhauntCastle::MaxUnhauntCount - newSoulHarvestedCount);
}

LocalizedString* EntityHauntedBehavior::getNextHauntedSpeechBubbleText()
{
	static int NextIndex = -1;

	switch(++NextIndex % 6)
	{
		default:
		case 0:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_A_Help::create();
		}
		case 1:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_B_GoAway::create();
		}
		case 2:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_C_Ack::create();
		}
		case 3:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_D_LeaveAlone::create();
		}
		case 4:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_E_NoPls::create();
		}
		case 5:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_F_Begone::create();
		}
	}
}

LocalizedString* EntityHauntedBehavior::getNextUnhauntedSpeechBubbleText()
{
	static int NextIndex = -1;
	static std::string HasThanked = "SAVE_KEY_THANKED";

	if (this->ownerAsFriendly != nullptr && this->ownerAsFriendly->loadObjectStateOrDefault(HasThanked, Value(false)).asBool())
	{
		return nullptr;
	}

	this->ownerAsFriendly->saveObjectState(HasThanked, Value(true));

	switch(++NextIndex % 6)
	{
		default:
		case 0:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_H_Hero::create();
		}
		case 1:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_I_ThankYou::create();
		}
		case 2:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_J_Savior::create();
		}
		case 3:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_K_Thx::create();
		}
		case 4:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_L_Grateful::create();
		}
		case 5:
		{
			return Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_M_Appreciated::create();
		}
	}
}

void EntityHauntedBehavior::showRemainingSoulsDialogue(int remaining)
{
	if (remaining <= 0)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_Q_AllSouls::create()
				->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Mabel::create()),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
			true
		));
	}
	else
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Misc_P_RemainingSouls::create()
				->setStringReplacementVariables(ConstantString::create(std::to_string(remaining))),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
			true
		));
	}
}
