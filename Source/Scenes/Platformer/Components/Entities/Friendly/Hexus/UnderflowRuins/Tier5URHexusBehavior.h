#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier5URHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier5URHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier5URHexusBehavior(GameObject* owner);
	virtual ~Tier5URHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
