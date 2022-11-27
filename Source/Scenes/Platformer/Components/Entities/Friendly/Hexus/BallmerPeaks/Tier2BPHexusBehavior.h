#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier2BPHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier2BPHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier2BPHexusBehavior(GameObject* owner);
	virtual ~Tier2BPHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
