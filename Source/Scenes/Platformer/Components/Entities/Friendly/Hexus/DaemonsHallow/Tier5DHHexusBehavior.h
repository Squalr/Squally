#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier5DHHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier5DHHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier5DHHexusBehavior(GameObject* owner);
	virtual ~Tier5DHHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
