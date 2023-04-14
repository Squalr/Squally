#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier8URHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier8URHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier8URHexusBehavior(GameObject* owner);
	virtual ~Tier8URHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
