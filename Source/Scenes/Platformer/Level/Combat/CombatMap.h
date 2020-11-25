#pragma once

#include "Scenes/MapBase.h"

class CardsMenu;
class CancelMenu;
class ChoicesMenu;
class CollectablesMenu;
class CombatAIHelper;
class CombatHud;
class ConfirmationHud;
class DefeatMenu;
class FocusTakeOver;
class FirstStrikeMenu;
class HackerModeWarningHud;
template <class T>
class LazyNode;
class NotificationHud;
class PartyMenu;
class PlatformerEntityDeserializer;
class PlatformerPauseMenu;
class RewardsMenu;
class Scrappy;
class TargetSelectionMenu;
class Timeline;

class CombatMap : public MapBase
{
public:
	struct StatsOverrides
	{
		int health;
		int mana;
		bool useOverrides;

		StatsOverrides() : health(0), mana(0), useOverrides(false) { }
		StatsOverrides(int health, int mana) : health(health), mana(mana), useOverrides(true) { }
	};

	struct CombatData
	{
		std::string entityType;
		std::string identifier;
		std::string battleBehavior;
		std::string dropPool;
		StatsOverrides statsOverrides;

		CombatData(std::string entityType, std::string identifier, std::string battleBehavior, StatsOverrides statsOverrides = StatsOverrides(), std::string dropPool = "")
			: entityType(entityType), identifier(identifier), battleBehavior(battleBehavior), statsOverrides(statsOverrides), dropPool(dropPool) { }
	};

	static CombatMap* create(std::string levelFile, bool playerFirstStrike, std::vector<CombatData> playerData, std::vector<CombatData> enemyData);

protected:
	CombatMap(std::string levelFile, bool playerFirstStrike, std::vector<CombatData> playerData, std::vector<CombatData> enemyData);
	virtual ~CombatMap();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onHackerModeEnable() override;
	void openPauseMenu(cocos2d::Node* refocusTarget) override;

private:
	typedef MapBase super;

	void spawnEntities();
	CollectablesMenu* buildCollectablesMenu();
	CardsMenu* buildCardsMenu();
	PartyMenu* buildPartyMenu();
	PlatformerPauseMenu* buildPlatformerPauseMenu();

	LazyNode<CollectablesMenu>* collectablesMenu;
	LazyNode<CardsMenu>* cardsMenu;
	LazyNode<PartyMenu>* partyMenu;
	LazyNode<PlatformerPauseMenu>* platformerPauseMenu;

	TargetSelectionMenu* targetSelectionMenu;
	ChoicesMenu* choicesMenu;
	CancelMenu* cancelMenu;
	CombatHud* combatHud;
	FirstStrikeMenu* firstStrikeMenu;
	DefeatMenu* defeatMenu;
	RewardsMenu* rewardsMenu;
	Timeline* timeline;
	CombatAIHelper* enemyAIHelper;
	HackerModeWarningHud* hackerModeWarningHud;
	NotificationHud* notificationHud;
	ConfirmationHud* confirmationHud;

	Hud* combatEndBackdrop;

	Scrappy* scrappy;

	FocusTakeOver* entityFocusTakeOver;
	FocusTakeOver* focusTakeOver;

	bool playerFirstStrike;
	std::vector<CombatData> playerData;
	std::vector<CombatData> enemyData;

	PlatformerEntityDeserializer* platformerEntityDeserializer;

	static const std::string PropertyPlayerFirstStrike;
	static const std::string PropertyEnemyFirstStrike;
};
