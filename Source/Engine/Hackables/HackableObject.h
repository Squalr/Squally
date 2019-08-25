#pragma once
#include <map>
#include <string>

#include "Engine/Events/InputEvents.h"
#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class ParticleSystem;
	class Renderer;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class ClickableNode;
class HackableAttribute;
class HackableCode;
class HackableData;
class HackActivatedAbility;
class HackablePreview;
class HackButton;
class ProgressBar;

class HackableObject : public GameObject
{
public:
	void onHackableClick();
	virtual HackablePreview* createDefaultPreview();
	
	void registerData(HackableData* hackableData);
	void unregisterData(HackableData* hackableData);
	void registerCode(HackableCode* hackableCode);
	void unregisterCode(HackableCode* hackableCode);
	void registerHackAbility(HackActivatedAbility* hackActivatedAbility);
	void unregisterHackAbility(HackActivatedAbility* hackActivatedAbility);

	std::vector<HackableAttribute*> hackableList;
	std::vector<HackableData*> dataList;
	std::vector<HackableCode*> codeList;
	std::vector<HackActivatedAbility*> hackAbilityList;

protected:
	HackableObject(const cocos2d::ValueMap& properties);
	HackableObject();
	~HackableObject();

	bool showClippy;

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void initializeListeners() override;
	void initializePositions() override;
	void update(float dt) override;
	void onHackerModeEnable(int eq) override;
	void onHackerModeDisable() override;
	virtual void onSensingEnable(int eq);
	virtual void onSensingDisable();
	virtual void registerHackables();
	virtual cocos2d::Vec2 getButtonOffset();

private:
	typedef GameObject super;

	bool hasRelocatedUI;

	cocos2d::ParticleSystem* sensingParticles;
	cocos2d::Node* uiElements;
	HackButton* hackButton;
	ProgressBar* timeRemainingBar;
	cocos2d::Node* hackablesNode;

	std::vector<HackableAttribute*> trackedAttributes;
	cocos2d::Vec2 buttonOffset;

	static const std::string MapKeyShowClippy;
};
