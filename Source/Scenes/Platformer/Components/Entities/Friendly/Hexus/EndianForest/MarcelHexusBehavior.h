#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class MarcelHexusBehavior : public HexusBehaviorBase
{
public:
	static MarcelHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MarcelHexusBehavior(GameObject* owner);
	virtual ~MarcelHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
