#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier5DMHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier5DMHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier5DMHexusBehavior(GameObject* owner);
	virtual ~Tier5DMHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
