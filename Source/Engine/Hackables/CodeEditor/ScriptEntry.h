#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
}

class LocalizedString;
class ClickableNode;
class HackableCode;
class LocalizedLabel;

class ScriptEntry : public SmartNode
{
public:
	static ScriptEntry* create(LocalizedString* scriptName, std::string script, std::function<void(ScriptEntry*)> onScriptEntryClick);

	LocalizedString* getName();
	std::string getScript();
	void setScriptUnsaved(std::string script);
	void softSave();
	bool hasUnsavedChanges();
	void discardUnsavedChanges();

private:
	typedef SmartNode super;
	ScriptEntry(LocalizedString* scriptName, std::string script, std::function<void(ScriptEntry*)> onScriptEntryClick);
	~ScriptEntry() = default;

	void initializePositions() override;
	void initializeListeners() override;

	ClickableNode* backPlate;
	LocalizedLabel* label;

	LocalizedString* scriptName;
	std::string scriptUnsaved;
	std::string script;
	std::function<void(ScriptEntry*)> onScriptEntryClick;
};
