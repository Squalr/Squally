#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class MinMaxPool;

class FFPuzzleDBehavior : public HexusPuzzleBehaviorBase
{
public:
	static FFPuzzleDBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FFPuzzleDBehavior(GameObject* owner);
	virtual ~FFPuzzleDBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
