#pragma once
#include <map>
#include <string>

#include "Engine/Events/InputEvents.h"
#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Renderer;
	class Sprite;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class ClickableNode;
class Clippy;
class HackableAttribute;
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
	void unregisterCode(HackableCode* hackableCode);
	void registerHackAbility(HackActivatedAbility* hackActivatedAbility);
	void unregisterHackAbility(HackActivatedAbility* hackActivatedAbility);
	void registerClippy(Clippy* clippy);
	void enableAllClippy();
	cocos2d::Node* getHackParticlesNode();

	template <class T>
	T* getClippy()
	{
		for (auto it = clippyList.begin(); it != clippyList.end(); it++)
		{
			if (dynamic_cast<T*>(*it) != nullptr)
			{
				return dynamic_cast<T*>(*it);
			}
		}

		return nullptr;
	}

	std::vector<HackableAttribute*> hackableList;
	std::vector<HackableCode*> codeList;
	std::vector<HackActivatedAbility*> hackAbilityList;

protected:
	HackableObject(const cocos2d::ValueMap& properties);
	HackableObject();
	virtual ~HackableObject();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void initializeListeners() override;
	void initializePositions() override;
	void update(float dt) override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	void rebindUIElementsTo(cocos2d::Node* newParent);
	virtual void registerHackables();
	virtual cocos2d::Vec2 getRainOffset();
	virtual cocos2d::Vec2 getButtonOffset();

private:
	typedef GameObject super;
	
	bool hasRelocatedUI;
	bool allowFx;
	bool isHackable;

	void refreshParticleFx();
	void createSensingParticles();
	void createHackCircle();
	void unregisterAllHackables();

	cocos2d::Node* hackParticlesNode;
	SmartParticles* hackParticles1;
	SmartParticles* hackParticles2;
	SmartParticles* hackParticles3;
	SmartParticles* hackParticles4;
	SmartParticles* hackParticles5;
	cocos2d::Sprite* hackCircle;
	cocos2d::Node* uiElements;
	cocos2d::Node* uiElementsRain;
	HackButton* hackButton;
	ProgressBar* timeRemainingBar;
	cocos2d::Node* hackablesNode;

	std::vector<Clippy*> clippyList;
	std::vector<HackableAttribute*> trackedAttributes;
	cocos2d::Vec2 buttonOffset;

	static int HackFlags;
};
