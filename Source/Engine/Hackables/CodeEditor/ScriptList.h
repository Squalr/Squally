#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
}

class ConstantString;
class ClickableNode;
class HackableCode;
class LocalizedLabel;
class ScriptEntry;

class ScriptList : public SmartNode
{
public:
	static ScriptList* create(std::function<void(ScriptEntry*)> onScriptSelect);

	void setActiveScriptText(std::string text);
	void addNewScript();
	void deleteActiveScript();
	void loadScripts(HackableCode* hackableCode);
	ScriptEntry* getActiveScript();

protected:
	ScriptList(std::function<void(ScriptEntry*)> onScriptSelect);
	~ScriptList() = default;

private:
	typedef SmartNode super;

	void initializePositions() override;
	void initializeListeners() override;
	void onScriptEntryClick(ScriptEntry* scriptEntry);
	void setActiveScript(ScriptEntry* activeScript);
	
	LocalizedLabel* titleLabel;
	cocos2d::Node* scriptsNode;
	std::function<void(ScriptEntry*)> onScriptSelect;
	std::vector<ScriptEntry*> scripts;
	ClickableNode* createNewScriptButton;
	ScriptEntry* activeScript;
	HackableCode* hackableCode;
};
