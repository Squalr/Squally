#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier1LCHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier1LCHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier1LCHexusBehavior(GameObject* owner);
	virtual ~Tier1LCHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
