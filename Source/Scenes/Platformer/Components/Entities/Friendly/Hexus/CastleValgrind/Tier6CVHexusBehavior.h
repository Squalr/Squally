#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier6CVHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier6CVHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier6CVHexusBehavior(GameObject* owner);
	virtual ~Tier6CVHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
