#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class TobenHexusBehavior : public HexusBehaviorBase
{
public:
	static TobenHexusBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	TobenHexusBehavior(GameObject* owner);
	virtual ~TobenHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
