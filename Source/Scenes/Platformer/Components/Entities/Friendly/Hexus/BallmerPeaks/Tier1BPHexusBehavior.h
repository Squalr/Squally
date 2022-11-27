#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier1BPHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier1BPHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier1BPHexusBehavior(GameObject* owner);
	virtual ~Tier1BPHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
