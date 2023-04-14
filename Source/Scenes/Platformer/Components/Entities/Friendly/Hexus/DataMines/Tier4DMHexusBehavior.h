#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier4DMHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier4DMHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier4DMHexusBehavior(GameObject* owner);
	virtual ~Tier4DMHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
