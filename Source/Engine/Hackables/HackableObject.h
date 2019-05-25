#pragma once
#include <map>
#include <string>

#include "Engine/Maps/SerializableObject.h"

namespace cocos2d
{
	class Renderer;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class ClickableNode;
class HackableAttribute;
class HackableCode;
class HackableData;
class HackablePreview;
class HackButton;
class ProgressBar;

class HackableObject : public SerializableObject
{
public:
	void onHackableClick();
	virtual HackablePreview* createDefaultPreview();
	
	void registerData(HackableData* hackableData);
	void unregisterData(HackableData* hackableData);
	void registerCode(HackableCode* hackableCode);
	void unregisterCode(HackableCode* hackableCode);

	std::vector<HackableAttribute*> hackableList;
	std::vector<HackableData*> dataList;
	std::vector<HackableCode*> codeList;

protected:
	HackableObject(const cocos2d::ValueMap& initProperties);
	virtual ~HackableObject();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void initializeListeners() override;
	void initializePositions() override;
	void update(float dt) override;
	virtual void onHackerModeEnable();
	virtual void onHackerModeDisable();
	virtual void registerHackables();
	virtual cocos2d::Vec2 getButtonOffset();

private:
	typedef SerializableObject super;

	cocos2d::Node* uiElements;
	HackButton* hackButton;
	ProgressBar* timeRemainingBar;
	std::vector<HackableAttribute*> trackedAttributes;

	cocos2d::Vec2 buttonOffset;
};
