#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier5LCHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier5LCHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier5LCHexusBehavior(GameObject* owner);
	virtual ~Tier5LCHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
