#include "ScriptList.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Save/SaveManager.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/CodeEditor/OriginalCode.h"
#include "Strings/Hacking/CodeEditor/YourScripts.h"

using namespace cocos2d;

ScriptList* ScriptList::create(std::function<void(std::string)> onScriptSelect)
{
	ScriptList* instance = new ScriptList(onScriptSelect);

	instance->autorelease();

	return instance;
}

ScriptList::ScriptList(std::function<void(std::string)> onScriptSelect)
{
	this->onScriptSelect = onScriptSelect;
	this->scriptsNode = Node::create();
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_CodeEditor_YourScripts::create());

	this->addChild(this->titleLabel);
	this->addChild(this->scriptsNode);
}

void ScriptList::initializePositions()
{
	super::initializePositions();
}

void ScriptList::loadScripts(HackableCode* hackableCode)
{
	this->scriptsNode->removeAllChildren();

	ValueMap scripts = SaveManager::getProfileDataOrDefault(hackableCode->getHackableCodeIdentifier(), Value(ValueMap())).asValueMap();

	const float titleOffset = 48.0f;
	const float entrySize = 48.0f;
	const float margin = 16.0f;
	int index = 0;

	// Add the default script
	{
		std::string script = hackableCode->getOriginalAssemblyString();
		ClickableNode* entry = ClickableNode::create(UIResources::Menus_HackerModeMenu_ScriptEntry, UIResources::Menus_HackerModeMenu_ScriptEntrySelected);
		LocalizedLabel* text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_OriginalCode::create());

		text->setPositionX(-entry->getContentSize().width / 2.0f + margin);
		text->setAnchorPoint(Vec2(0.0f, 0.5f));

		entry->setPosition(Vec2(0.0f, (entrySize * (float)index) - titleOffset));
		entry->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
		{
			this->onScriptSelect(script);
		});

		entry->addChild(text);
		this->scriptsNode->addChild(entry);

		index++;
	}

	// Add user scripts
	for (auto it = scripts.begin(); it != scripts.end(); it++)
	{
		std::string scriptName = it->first;
		std::string script = it->second.asString();
		ClickableNode* entry = ClickableNode::create(UIResources::Menus_HackerModeMenu_ScriptEntry, UIResources::Menus_HackerModeMenu_ScriptEntrySelected);
		LocalizedLabel* text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(scriptName));

		text->setPositionX(-entry->getContentSize().width / 2.0f + margin);
		text->setAnchorPoint(Vec2(0.0f, 0.5f));

		entry->setPosition(Vec2(0.0f, (entrySize * (float)index) - titleOffset));
		entry->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
		{
			this->onScriptSelect(script);
		});

		entry->addChild(text);
		this->scriptsNode->addChild(entry);

		index++;
	}
}
