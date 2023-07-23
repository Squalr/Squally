#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class MinMaxPool;

class LCPuzzleDBehavior : public HexusPuzzleBehaviorBase
{
public:
	static LCPuzzleDBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LCPuzzleDBehavior(GameObject* owner);
	virtual ~LCPuzzleDBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
