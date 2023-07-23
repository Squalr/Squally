#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier6EFHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier6EFHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier6EFHexusBehavior(GameObject* owner);
	virtual ~Tier6EFHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
