#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier7DMHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier7DMHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier7DMHexusBehavior(GameObject* owner);
	virtual ~Tier7DMHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
