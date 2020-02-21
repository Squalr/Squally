#pragma once
#include <map>
#include <string>

#include "Engine/Events/InputEvents.h"
#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Renderer;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class ClickableNode;
class Clippy;
class HackableAttribute;
class HackableCode;
class HackableData;
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
	
	void toggleHackable(bool isHackable);
	void registerData(HackableData* hackableData);
	void unregisterData(HackableData* hackableData);
	void registerCode(HackableCode* hackableCode);
	void unregisterCode(HackableCode* hackableCode);
	void registerHackAbility(HackActivatedAbility* hackActivatedAbility);
	void unregisterHackAbility(HackActivatedAbility* hackActivatedAbility);
	void registerClippy(Clippy* clippy);
	void enableAllClippy();

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
	std::vector<HackableData*> dataList;
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
	void onHackerModeEnable(int hackFlags) override;
	void onHackerModeDisable() override;
	void rebindUIElementsTo(cocos2d::Node* newParent);
	virtual void registerHackables();
	virtual cocos2d::Vec2 getButtonOffset();

private:
	typedef GameObject super;

	bool hasRelocatedUI;
	bool isHackable;

	void startParticleFx();
	void createSensingParticles();
	void unregisterAllHackables();

	cocos2d::Node* sensingParticlesNode;
	SmartParticles* hackParticles1;
	SmartParticles* hackParticles2;
	SmartParticles* hackParticles3;
	SmartParticles* hackParticles4;
	SmartParticles* hackParticles5;
	cocos2d::Node* uiElements;
	HackButton* hackButton;
	ProgressBar* timeRemainingBar;
	cocos2d::Node* hackablesNode;

	std::vector<Clippy*> clippyList;
	std::vector<HackableAttribute*> trackedAttributes;
	cocos2d::Vec2 buttonOffset;

	int cachedHackFlags;
};
