#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
}

class ConfirmationMenu;
class ConstantString;
class ClickableNode;
class HackableCode;
class LocalizedLabel;
class ScriptEntry;

class ScriptList : public SmartNode
{
public:
	static ScriptList* create(ConfirmationMenu* confirmationMenuRef, std::function<void(ScriptEntry*)> onScriptSelect);

	void setActiveScriptText(std::string text);
	ScriptEntry* addNewScript();
	void deleteActiveScript();
	void loadScripts(HackableCode* hackableCode);
	void saveScripts();
	ScriptEntry* getActiveScript();

protected:
	ScriptList(ConfirmationMenu* confirmationMenuRef, std::function<void(ScriptEntry*)> onScriptSelect);
	virtual ~ScriptList();

private:
	typedef SmartNode super;

	void initializePositions() override;
	void initializeListeners() override;
	void deleteScript(ScriptEntry* scriptEntry);
	void copyScript(ScriptEntry* scriptEntry);
	void onScriptEntryClick(ScriptEntry* scriptEntry);
	void onScriptEntryCopyClick(ScriptEntry* scriptEntry);
	void onScriptEntryDeleteClick(ScriptEntry* scriptEntry);
	void setActiveScript(ScriptEntry* activeScript);
	
	LocalizedLabel* titleLabel;
	cocos2d::Node* scriptsNode;
	std::function<void(ScriptEntry*)> onScriptSelect;
	std::vector<ScriptEntry*> scripts;
	ClickableNode* createNewScriptButton;
	LocalizedLabel* createNewScriptLabel;
	cocos2d::Sprite* createNewScriptSprite;
	ScriptEntry* activeScript;
	HackableCode* hackableCode;
	ConfirmationMenu* confirmationMenuRef;

	static const std::string ScriptNameKey;
	static const std::string ScriptKey;
	static const int MaxScripts;
};
