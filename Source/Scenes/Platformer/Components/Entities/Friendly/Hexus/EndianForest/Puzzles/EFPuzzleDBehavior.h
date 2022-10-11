#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class EFPuzzleDBehavior : public HexusPuzzleBehaviorBase
{
public:
	static EFPuzzleDBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EFPuzzleDBehavior(GameObject* owner);
	virtual ~EFPuzzleDBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
