#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier5EFHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier5EFHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier5EFHexusBehavior(GameObject* owner);
	virtual ~Tier5EFHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
