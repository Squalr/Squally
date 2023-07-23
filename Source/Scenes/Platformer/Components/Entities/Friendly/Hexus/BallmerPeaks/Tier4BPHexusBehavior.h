#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class Tier4BPHexusBehavior : public HexusBehaviorBase
{
public:
	static Tier4BPHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	Tier4BPHexusBehavior(GameObject* owner);
	virtual ~Tier4BPHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
