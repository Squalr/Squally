#pragma once
#include <map>
#include <string>

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class Clippy;
class HackableBase;
class HackableCode;
class HackActivatedAbility;
class HackablePreview;
class HackButton;
template <class T> class LazyNode;
class ProgressBar;
class SmartParticles;

class HackableObject : public GameObject
{
public:
	void onHackableClick();
	virtual HackablePreview* createDefaultPreview();

	static int GetHackFlags();
	static void SetHackFlags(int hackFlags);
	
	void toggleHackable(bool isHackable);
	void toggleAllowFx(bool allowFx);
	void registerCode(HackableCode* hackableCode, bool refreshCooldowns = true);
	void unregisterCode(HackableCode* hackableCode, bool forceRestoreState = false);
	void registerHackAbility(HackActivatedAbility* hackActivatedAbility, bool refreshCooldowns = true);
	void unregisterHackAbility(HackActivatedAbility* hackActivatedAbility);
	void registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc);
	cocos2d::Node* getHackParticlesNode();

	std::vector<HackableBase*> hackableList;
	std::vector<HackableCode*> codeList;
	std::vector<HackActivatedAbility*> hackAbilityList;

protected:
	HackableObject(const cocos2d::ValueMap& properties);
	HackableObject();
	virtual ~HackableObject();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void initializePositions() override;
	void update(float dt) override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	void onDespawn() override;
	void rebindUIElementsTo(cocos2d::Node* newParent);
	void repositionHackButtons();
	virtual void registerHackables();
	virtual cocos2d::Vec2 getRainOffset();
	virtual cocos2d::Vec2 getButtonOffset();
	virtual cocos2d::Vec2 getProgressBarsOffset();

private:
	typedef GameObject super;
	friend class CodeHud;
	
	bool hasRelocatedUI = false;
	bool allowFx = true;
	bool isHackable = true;

	void unregisterAllHackables(bool forceRestoreState = false);
	void updateTimeRemainingBars();
	void refreshParticleFx();
	void createHackParticles();
	void createHackCircle();
	HackButton* buildHackButton();

	cocos2d::Node* hackParticlesNode = nullptr;
	SmartParticles* hackParticles1 = nullptr;
	SmartParticles* hackParticles2 = nullptr;
	SmartParticles* hackParticles3 = nullptr;
	SmartParticles* hackParticles4 = nullptr;
	SmartParticles* hackParticles5 = nullptr;
	cocos2d::Sprite* hackCircle = nullptr;
	cocos2d::Node* uiElementsButton = nullptr;
	cocos2d::Node* uiElementsRain = nullptr;
	cocos2d::Node* uiElementsProgressBars = nullptr;
	LazyNode<HackButton>* hackButton = nullptr;
	std::vector<cocos2d::Sprite*> timeRemainingIcons;
	std::vector<ProgressBar*> timeRemainingBars;
	std::map<std::string, std::function<Clippy*()>> clippyMap;

	std::vector<HackableBase*> trackedHackables;
	cocos2d::Vec2 buttonOffset;

	static int HackFlags;
	static unsigned long long WatchId;
};
