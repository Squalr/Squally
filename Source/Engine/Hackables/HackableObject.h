#pragma once
#include <map>
#include <string>

#include "Engine/Events/InputEvents.h"
#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class Clippy;
class HackableBase;
class HackableCode;
class HackActivatedAbility;
class HackablePreview;
class HackButton;
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
	void registerCode(HackableCode* hackableCode);
	void unregisterCode(HackableCode* hackableCode, bool forceRestoreState = false);
	void registerHackAbility(HackActivatedAbility* hackActivatedAbility);
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
	virtual void registerHackables();
	virtual cocos2d::Vec2 getRainOffset();
	virtual cocos2d::Vec2 getButtonOffset();
	virtual cocos2d::Vec2 getProgressBarsOffset();

private:
	typedef GameObject super;
	friend class CodeHud;
	
	bool hasRelocatedUI;
	bool allowFx;
	bool isHackable;

	void unregisterAllHackables(bool forceRestoreState = false);
	void updateTimeRemainingBars();
	void refreshParticleFx();
	void createSensingParticles();
	void createHackCircle();

	cocos2d::Node* hackParticlesNode;
	SmartParticles* hackParticles1;
	SmartParticles* hackParticles2;
	SmartParticles* hackParticles3;
	SmartParticles* hackParticles4;
	SmartParticles* hackParticles5;
	cocos2d::Sprite* hackCircle;
	cocos2d::Node* uiElementsButton;
	cocos2d::Node* uiElementsRain;
	cocos2d::Node* uiElementsProgressBars;
	HackButton* hackButton;
	std::vector<cocos2d::Sprite*> timeRemainingIcons;
	std::vector<ProgressBar*> timeRemainingBars;
	std::map<std::string, std::function<Clippy*()>> clippyMap;

	std::vector<HackableBase*> trackedAttributes;
	cocos2d::Vec2 buttonOffset;

	static int HackFlags;
	static unsigned long long WatchId;
};
