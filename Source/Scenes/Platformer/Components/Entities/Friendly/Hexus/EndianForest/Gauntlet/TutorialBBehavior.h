#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class PlatformerEntity;

class TutorialBBehavior : public HexusBehaviorBase
{
public:
	static TutorialBBehavior* create(GameObject* owner);

protected:
	TutorialBBehavior(GameObject* owner);
	virtual ~TutorialBBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

	static const std::string WinLossTrackIdentifier;
};
