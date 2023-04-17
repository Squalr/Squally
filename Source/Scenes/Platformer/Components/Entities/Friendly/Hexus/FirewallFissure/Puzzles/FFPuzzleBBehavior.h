#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class MinMaxPool;

class FFPuzzleBBehavior : public HexusPuzzleBehaviorBase
{
public:
	static FFPuzzleBBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FFPuzzleBBehavior(GameObject* owner);
	virtual ~FFPuzzleBBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
