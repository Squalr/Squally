#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier4DHHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier4DHHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier4DHHexusBehavior(GameObject* owner);
	virtual ~Tier4DHHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
