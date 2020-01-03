#include "ScriptEntry.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Save/SaveManager.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ScriptEntry* ScriptEntry::create(LocalizedString* scriptName, std::string script, bool isReadOnly, std::function<void(ScriptEntry*)> onScriptEntryClick, std::function<void(ScriptEntry*)> onDeleteClick)
{
	ScriptEntry* instance = new ScriptEntry(scriptName, script, isReadOnly, onScriptEntryClick, onDeleteClick);

	instance->autorelease();

	return instance;
}

ScriptEntry::ScriptEntry(LocalizedString* scriptName, std::string script, bool isReadOnly, std::function<void(ScriptEntry*)> onScriptEntryClick, std::function<void(ScriptEntry*)> onDeleteClick)
{
	this->scriptName = scriptName;
	this->script = script;
	this->isReadOnly = isReadOnly;
	this->onScriptEntryClick = onScriptEntryClick;
	this->onDeleteClick = onDeleteClick;
	this->deleteButton = nullptr;

	this->backPlate = ClickableNode::create(UIResources::Menus_HackerModeMenu_ScriptEntry, UIResources::Menus_HackerModeMenu_ScriptEntrySelected);
	this->selectedSprite = Sprite::create(UIResources::Menus_HackerModeMenu_SelectedScriptArrow);
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->scriptName);

	this->selectedSprite->setColor(Color3B::YELLOW);
	this->selectedSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->label->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->backPlate);
	this->addChild(this->selectedSprite);
	this->addChild(this->label);

	if (!this->isReadOnly)
	{
		this->deleteButton = ClickableNode::create(UIResources::Menus_HackerModeMenu_TrashCan, UIResources::Menus_HackerModeMenu_TrashCanSelected);
		this->addChild(this->deleteButton);
	}
}

void ScriptEntry::initializePositions()
{
	super::initializePositions();

	const float margin = 16.0f;

	this->label->setPositionX(-this->backPlate->getContentSize().width / 2.0f + margin);
	this->selectedSprite->setPositionX(-this->backPlate->getContentSize().width / 2.0f + margin);

	if (this->deleteButton != nullptr)
	{
		this->deleteButton->setPositionX(this->backPlate->getContentSize().width / 2.0f - this->deleteButton->getContentSize().width - 8.0f);
	}
}

void ScriptEntry::initializeListeners()
{
	super::initializeListeners();

	this->backPlate->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onScriptEntryClick(this); });
	
	if (this->deleteButton != nullptr)
	{
		this->deleteButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->onDeleteClick(this); });
	}
}

void ScriptEntry::toggleSelected(bool isSelected)
{
	const float Margin = 16.0f;
	const float SelectedOffset = 32.0f;

	this->selectedSprite->setVisible(isSelected);

	this->label->setTextColor(isSelected ? Color4B::YELLOW : Color4B::WHITE);
	this->label->setPositionX(-this->backPlate->getContentSize().width / 2.0f + Margin + (isSelected ? SelectedOffset : 0.0f));
}

LocalizedString* ScriptEntry::getName()
{
	return this->scriptName;
}

std::string ScriptEntry::getScript()
{
	return this->script;
}

void ScriptEntry::setScript(std::string script)
{
	this->script = script;
}
