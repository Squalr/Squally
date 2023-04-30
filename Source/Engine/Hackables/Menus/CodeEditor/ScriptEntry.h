#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class LocalizedLabel;
class LocalizedString;

class ScriptEntry : public SmartNode
{
public:
	static ScriptEntry* create(LocalizedString* scriptName, std::string script, bool isReadOnly, std::function<void(ScriptEntry*)> onScriptEntryClick, std::function<void(ScriptEntry*)> onCopyClick, std::function<void(ScriptEntry*)> onDeleteClick);

	void bindToLocalizedScript(LocalizedString* localizedScript);

	void toggleSelected(bool isSelected);
	void deleteScript();
	void copyScript();
	LocalizedString* getName();
	std::string getScript();
	void setScript(std::string script);
	void setName(std::string name);

	bool isReadOnly = false;

protected:
	ScriptEntry(LocalizedString* scriptName, std::string script, bool isReadOnly, std::function<void(ScriptEntry*)> onScriptEntryClick, std::function<void(ScriptEntry*)> onCopyClick, std::function<void(ScriptEntry*)> onDeleteClick);
	virtual ~ScriptEntry();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::CSize originalBackPlateSize;

	ClickableNode* backPlate = nullptr;
	cocos2d::Sprite* selectedSprite = nullptr;
	LocalizedLabel* label = nullptr;
	ClickableNode* copyButton = nullptr;
	ClickableNode* deleteButton = nullptr;
	cocos2d::LayerColor* deletePanel = nullptr;
	LocalizedLabel* deleteLabel = nullptr;
	cocos2d::LayerColor* copyPanel = nullptr;
	LocalizedLabel* copyLabel = nullptr;

	LocalizedString* boundScript = nullptr;
	LocalizedString* scriptName = nullptr;
	std::string script;
	std::function<void(ScriptEntry*)> onScriptEntryClick = nullptr;
	std::function<void(ScriptEntry*)> onCopyClick = nullptr;
	std::function<void(ScriptEntry*)> onDeleteClick = nullptr;
};
