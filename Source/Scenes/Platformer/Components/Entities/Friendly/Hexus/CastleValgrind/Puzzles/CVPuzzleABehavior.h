#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class MinMaxPool;

class CVPuzzleABehavior : public HexusPuzzleBehaviorBase
{
public:
	static CVPuzzleABehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	CVPuzzleABehavior(GameObject* owner);
	virtual ~CVPuzzleABehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
