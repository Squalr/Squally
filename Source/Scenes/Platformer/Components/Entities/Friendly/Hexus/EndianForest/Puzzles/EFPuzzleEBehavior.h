#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusPuzzleBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class EFPuzzleEBehavior : public HexusPuzzleBehaviorBase
{
public:
	static EFPuzzleEBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EFPuzzleEBehavior(GameObject* owner);
	virtual ~EFPuzzleEBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusPuzzleBehaviorBase super;
};
