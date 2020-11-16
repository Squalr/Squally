#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class MinMaxPool;

class URPuzzleBBehavior : public HexusPuzzleBehaviorBase
{
public:
	static URPuzzleBBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	URPuzzleBBehavior(GameObject* owner);
	virtual ~URPuzzleBBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
