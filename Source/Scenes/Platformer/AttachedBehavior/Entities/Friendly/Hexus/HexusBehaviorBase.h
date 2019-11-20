#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CardData;
class HexusOpponentData;
class MinMaxPool;
class LocalizedString;
class PlatformerEntity;
class StateOverride;
class TutorialBase;

class HexusBehaviorBase : public AttachedBehavior
{
public:
	void registerWinCallback(std::function<void()> winCallback);
	void registerLossCallback(std::function<void()> lossCallback);
	void registerDrawCallback(std::function<void()> drawCallback);

protected:
	HexusBehaviorBase(GameObject* owner, std::string voiceResource, LocalizedString* dialogueChoiceOverride = nullptr);
	~HexusBehaviorBase();

	virtual MinMaxPool* generateReward() = 0;
	virtual std::string getWinLossSaveKey() = 0;
	virtual std::string getBackgroundResource() = 0;
	virtual std::vector<CardData*> generateDeck() = 0;
	virtual StateOverride* getStateOverride() = 0;
	virtual cocos2d::Vec2 getAvatarOffset();
	virtual std::vector<TutorialBase*> getTutorials();
	
	void onLoad() override;
	void onWin();
	void onLoss();
	void onDraw();
	void runPostMatchDialogue(LocalizedString* dialogue);

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;

	HexusOpponentData* createOpponentData();

	cocos2d::Node* dialogueStringNode;
	LocalizedString* dialogueChoiceOverride;
	MinMaxPool* rewardPool;

	std::vector<std::function<void()>> winCallbacks;
	std::vector<std::function<void()>> lossCallbacks;
	std::vector<std::function<void()>> drawCallbacks;

	std::string voiceResource;
};
