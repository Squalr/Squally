#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier3CVHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier3CVHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier3CVHexusBehavior(GameObject* owner);
	virtual ~Tier3CVHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
