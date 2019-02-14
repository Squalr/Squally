#pragma once
#include <map>
#include <string>

#include "Engine/Maps/SerializableObject.h"

class HackableAttribute;
class HackableCode;
class HackableData;
class HackablePreview;
class HackButton;
class ClickableNode;

namespace cocos2d
{
	class Renderer;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class HackableObject : public SerializableObject
{
public:
	void onHackableClick(ClickableNode* backButton);
	HackablePreview* getDefaultPreview();
	void setDefaultPreview(HackablePreview* defaultPreview);

	std::vector<HackableAttribute*> hackableList;
	std::vector<HackableData*> dataList;
	std::vector<HackableCode*> codeList;

protected:
	HackableObject(const cocos2d::ValueMap& initProperties);
	virtual ~HackableObject();

	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void initializePositions() override;
	virtual void onHackerModeEnable();
	virtual void onHackerModeDisable();
	virtual cocos2d::Vec2 getButtonOffset();
	void registerData(HackableData* hackableData);
	void registerCode(HackableCode* hackableCode);

private:
	typedef SerializableObject super;

	HackButton* hackButton;
	cocos2d::Vec2 buttonOffset;
	HackablePreview* defaultPreview;
};
