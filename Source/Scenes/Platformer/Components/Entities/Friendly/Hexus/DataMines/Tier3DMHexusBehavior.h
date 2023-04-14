#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier3DMHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier3DMHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier3DMHexusBehavior(GameObject* owner);
	virtual ~Tier3DMHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
