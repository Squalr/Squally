#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier8EFHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier8EFHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier8EFHexusBehavior(GameObject* owner);
	virtual ~Tier8EFHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
