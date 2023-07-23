#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier2CVHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier2CVHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier2CVHexusBehavior(GameObject* owner);
	virtual ~Tier2CVHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
