#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier1DHHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier1DHHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier1DHHexusBehavior(GameObject* owner);
	virtual ~Tier1DHHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
