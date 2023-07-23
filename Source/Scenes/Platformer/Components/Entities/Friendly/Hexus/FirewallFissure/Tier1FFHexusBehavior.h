#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier1FFHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier1FFHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier1FFHexusBehavior(GameObject* owner);
	virtual ~Tier1FFHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
