#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class MildredHexusBehavior : public HexusBehaviorBase
{
public:
	static MildredHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MildredHexusBehavior(GameObject* owner);
	virtual ~MildredHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
