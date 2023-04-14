#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier3EFHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier3EFHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier3EFHexusBehavior(GameObject* owner);
	virtual ~Tier3EFHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
