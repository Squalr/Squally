#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class TutorialDBehavior : public HexusBehaviorBase
{
public:
	static TutorialDBehavior* create(GameObject* owner);

protected:
	TutorialDBehavior(GameObject* owner);
	~TutorialDBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;

private:
	typedef HexusBehaviorBase super;

	static const std::string WinLossTrackIdentifier;
};
