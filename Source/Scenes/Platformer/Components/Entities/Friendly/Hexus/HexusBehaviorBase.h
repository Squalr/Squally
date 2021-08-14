#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class CardData;
class DialogueOption;
class HexusOpponentData;
class MinMaxPool;
class LocalizedString;
class PlatformerEntity;
class SmartParticles;
class StateOverride;
class TutorialBase;

class HexusBehaviorBase : public GameComponent
{
public:
	int getWins();
	int getLosses();
	int getDraws();
	void addWin();
	void addLoss();
	void addDraw();
	void registerWinCallback(std::function<void()> winCallback);
	void registerLossCallback(std::function<void()> lossCallback);
	void registerDrawCallback(std::function<void()> drawCallback);
	void giveItems();
	void removeFromDialogue();

protected:
	HexusBehaviorBase(GameObject* owner, std::string voiceResource, bool showParticles = false, LocalizedString* dialogueChoiceOverride = nullptr);
	virtual ~HexusBehaviorBase();
	
	void onDisable() override;

	float calculateStrength(float localOrder, float zoneOrder);
	virtual MinMaxPool* generateReward() = 0;
	virtual std::string getWinLossSaveKey() = 0;
	virtual std::string getBackgroundResource() = 0;
	virtual std::vector<CardData*> generateDeck() = 0;
	virtual StateOverride* getStateOverride() = 0;
	virtual cocos2d::Vec2 getAvatarOffset();
	virtual std::vector<TutorialBase*> getTutorials();
	
	void onEnter() override;
	void initializePositions() override;
	void onLoad() override;
	void onWin();
	void onLoss();
	void onDraw();
	virtual LocalizedString* getCustomWinDialogue();
	virtual LocalizedString* getCustomDrawDialogue();
	virtual LocalizedString* getCustomLossDialogue();
	void runPostMatchDialogue(LocalizedString* dialogue);

	PlatformerEntity* entity = nullptr;

private:
	typedef GameComponent super;

	HexusOpponentData* createOpponentData();

	cocos2d::Node* dialogueStringNode = nullptr;
	LocalizedString* dialogueChoiceOverride = nullptr;
	MinMaxPool* rewardPool = nullptr;
	DialogueOption* hexusOption = nullptr;
	cocos2d::Node* iconNode = nullptr;
	cocos2d::Node* iconContainer = nullptr;
	cocos2d::Sprite* cardGlow = nullptr;
	cocos2d::Sprite* cardSprite = nullptr;

	SmartParticles* hackParticles1 = nullptr;
	SmartParticles* hackParticles2 = nullptr;
	SmartParticles* hackParticles3 = nullptr;
	SmartParticles* hackParticles4 = nullptr;
	SmartParticles* hackParticles5 = nullptr;

	std::vector<std::function<void()>> winCallbacks;
	std::vector<std::function<void()>> lossCallbacks;
	std::vector<std::function<void()>> drawCallbacks;

	std::string voiceResource;
	bool showParticles = false;
};
