#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class URPuzzleEBehavior : public HexusPuzzleBehaviorBase
{
public:
	static URPuzzleEBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	URPuzzleEBehavior(GameObject* owner);
	virtual ~URPuzzleEBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
