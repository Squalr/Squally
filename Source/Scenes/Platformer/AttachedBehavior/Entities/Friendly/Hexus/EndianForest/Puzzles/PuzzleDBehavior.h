#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class PuzzleDBehavior : public HexusBehaviorBase
{
public:
	static PuzzleDBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	PuzzleDBehavior(GameObject* owner);
	~PuzzleDBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;
};
