#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
}

class ConfirmationMenu;
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
	
	LocalizedLabel* titleLabel = nullptr;
	cocos2d::Node* scriptsNode = nullptr;
	std::function<void(ScriptEntry*)> onScriptSelect = nullptr;
	std::vector<ScriptEntry*> scripts;
	ClickableNode* createNewScriptButton = nullptr;
	LocalizedLabel* createNewScriptLabel = nullptr;
	cocos2d::Sprite* createNewScriptSprite = nullptr;
	ScriptEntry* activeScript = nullptr;
	HackableCode* hackableCode = nullptr;
	ConfirmationMenu* confirmationMenuRef = nullptr;

	int readOnlyCount = 0;

	static const std::string ScriptNameKey;
	static const std::string ScriptKey;
	static const std::string SaveKeyLastSelectedScriptIndexPrefix;
	static const int MaxScripts;
};
