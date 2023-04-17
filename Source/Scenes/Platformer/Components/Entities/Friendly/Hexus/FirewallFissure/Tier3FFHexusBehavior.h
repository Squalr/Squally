#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier3FFHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier3FFHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier3FFHexusBehavior(GameObject* owner);
	virtual ~Tier3FFHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
