#pragma once

#include "Engine/SmartNode.h"
#include "Engine/Localization/LocalizedString.h"

namespace cocos2d
{
	class Node;
	class Sprite;
}

class ConstantString;
class ClickableNode;
class HackableCode;
class LocalizedLabel;

class ScriptEntry : public SmartNode
{
public:
	static ScriptEntry* create(ConstantString* scriptName, std::string script, std::function<void(ScriptEntry*)> onScriptEntryClick);

	void toggleSelected(bool isSelected);
	ConstantString* getName();
	std::string getScript();
	void setScriptUnsaved(std::string script);
	void softSave();
	bool hasUnsavedChanges();
	void discardUnsavedChanges();

private:
	typedef SmartNode super;
	ScriptEntry(ConstantString* scriptName, std::string script, std::function<void(ScriptEntry*)> onScriptEntryClick);
	~ScriptEntry() = default;

	void initializePositions() override;
	void initializeListeners() override;

	ClickableNode* backPlate;
	cocos2d::Sprite* selectedSprite;
	LocalizedLabel* label;

	ConstantString* scriptName;
	std::string scriptUnsaved;
	std::string script;
	std::function<void(ScriptEntry*)> onScriptEntryClick;
};
