#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class PuzzleEBehavior : public HexusPuzzleBehaviorBase
{
public:
	static PuzzleEBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	PuzzleEBehavior(GameObject* owner);
	~PuzzleEBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
