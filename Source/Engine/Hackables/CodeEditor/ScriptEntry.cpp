#include "ScriptEntry.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Save/SaveManager.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ScriptEntry* ScriptEntry::create(ConstantString* scriptName, std::string script, std::function<void(ScriptEntry*)> onScriptEntryClick)
{
	ScriptEntry* instance = new ScriptEntry(scriptName, script, onScriptEntryClick);

	instance->autorelease();

	return instance;
}

ScriptEntry::ScriptEntry(ConstantString* scriptName, std::string script, std::function<void(ScriptEntry*)> onScriptEntryClick)
{
	this->onScriptEntryClick = onScriptEntryClick;
	this->scriptName = scriptName;
	this->script = script;
	this->scriptUnsaved = script;

	this->backPlate = ClickableNode::create(UIResources::Menus_HackerModeMenu_ScriptEntry, UIResources::Menus_HackerModeMenu_ScriptEntrySelected);
	this->backPlateSelected = ClickableNode::create(UIResources::Menus_HackerModeMenu_SelectedScriptEntry, UIResources::Menus_HackerModeMenu_SelectedScriptEntrySelected);
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->scriptName);

	this->label->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->backPlateSelected->setVisible(false);

	this->addChild(this->backPlate);
	this->addChild(this->backPlateSelected);
	this->addChild(this->label);
}

void ScriptEntry::initializePositions()
{
	super::initializePositions();

	const float margin = 16.0f;

	this->label->setPositionX(-this->backPlate->getContentSize().width / 2.0f + margin);
}

void ScriptEntry::initializeListeners()
{
	super::initializeListeners();

	this->backPlate->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onScriptEntryClick(this); });
	this->backPlateSelected->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->onScriptEntryClick(this); });
}

void ScriptEntry::toggleSelected(bool isSelected)
{
	this->backPlate->setVisible(!isSelected);
	this->backPlateSelected->setVisible(isSelected);
}

ConstantString* ScriptEntry::getName()
{
	return this->scriptName;
}

std::string ScriptEntry::getScript()
{
	return this->script;
}

void ScriptEntry::setScriptUnsaved(std::string script)
{
	this->scriptUnsaved = script;
}

void ScriptEntry::softSave()
{
	// The script list is responsible for actually saving
	this->script = this->scriptUnsaved;
}

bool ScriptEntry::hasUnsavedChanges()
{
	return (this->scriptUnsaved != this->script);
}

void ScriptEntry::discardUnsavedChanges()
{
	this->scriptUnsaved = this->script;
}
