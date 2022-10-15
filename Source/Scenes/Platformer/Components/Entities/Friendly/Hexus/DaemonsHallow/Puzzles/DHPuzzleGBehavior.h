#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class MinMaxPool;

class DHPuzzleGBehavior : public HexusPuzzleBehaviorBase
{
public:
	static DHPuzzleGBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DHPuzzleGBehavior(GameObject* owner);
	virtual ~DHPuzzleGBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
