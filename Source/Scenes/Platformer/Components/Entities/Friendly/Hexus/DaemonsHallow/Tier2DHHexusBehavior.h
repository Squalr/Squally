#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier2DHHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier2DHHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier2DHHexusBehavior(GameObject* owner);
	virtual ~Tier2DHHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
