#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier2FFHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier2FFHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier2FFHexusBehavior(GameObject* owner);
	virtual ~Tier2FFHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
