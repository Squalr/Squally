#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class SarudeTutorialBehavior : public HexusBehaviorBase
{
public:
	static SarudeTutorialBehavior* create(GameObject* owner);

protected:
	SarudeTutorialBehavior(GameObject* owner);
	~SarudeTutorialBehavior();

	std::vector<CardData*> generateDeck() override;
	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;

private:
	typedef HexusBehaviorBase super;

	static const std::string WinLossTrackIdentifier;
};
