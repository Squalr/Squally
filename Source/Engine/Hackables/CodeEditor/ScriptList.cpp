#include "ScriptList.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/CodeEditor/ScriptEntry.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Save/SaveManager.h"

#include "Strings/Generics/Count.h"
#include "Strings/Hacking/CodeEditor/CreateNewScript.h"
#include "Strings/Hacking/CodeEditor/MyNewScript.h"
#include "Strings/Hacking/CodeEditor/OriginalCode.h"
#include "Strings/Hacking/CodeEditor/YourScripts.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

ScriptList* ScriptList::create(std::function<void(ScriptEntry*)> onScriptSelect)
{
	ScriptList* instance = new ScriptList(onScriptSelect);

	instance->autorelease();

	return instance;
}

ScriptList::ScriptList(std::function<void(ScriptEntry*)> onScriptSelect)
{
	this->onScriptSelect = onScriptSelect;
	this->scriptsNode = Node::create();
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Hacking_CodeEditor_YourScripts::create());
	this->scripts = std::vector<ScriptEntry*>();
	this->createNewScriptButton = ClickableNode::create(UIResources::Menus_HackerModeMenu_ScriptEntry, UIResources::Menus_HackerModeMenu_ScriptEntrySelected);
	this->hackableCode = nullptr;

	this->titleLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	// this->createNewScriptButton->addChild(LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_CreateNewScript::create()));
	this->createNewScriptButton->addChild(Sprite::create(UIResources::Menus_HackerModeMenu_Plus));

	this->addChild(this->titleLabel);
	this->addChild(this->scriptsNode);
	this->addChild(this->createNewScriptButton);
}

void ScriptList::initializePositions()
{
	super::initializePositions();

	const float panelSize = 420.0f;
	const float titleOffset = 48.0f;
	const float entrySize = 48.0f;
	const float margin = 16.0f;
	int index = 0;

	this->titleLabel->setPositionX(-panelSize / 2.0f + margin);

	for (auto it = this->scripts.begin(); it != this->scripts.end(); it++)
	{
		(*it)->setPosition(Vec2(0.0f, -((float)index++ * entrySize) - titleOffset));
	}

	this->createNewScriptButton->setPosition(Vec2(0.0f, -((float)index++ * entrySize) - titleOffset - 8.0f));
}

void ScriptList::initializeListeners()
{
	super::initializeListeners();

	this->createNewScriptButton->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*) { this->addNewScript(); });
}

void ScriptList::setActiveScriptText(std::string text)
{
	if (this->activeScript != nullptr)
	{
		this->activeScript->setScriptUnsaved(text);
	}
}

void ScriptList::addNewScript()
{
	const int maxScripts = 10;

	if (this->scripts.size() < maxScripts)
	{
		LocalizedString* newScriptName = Strings::Generics_Count::create();

		newScriptName->setStringReplacementVariables(
		{
			Strings::Hacking_CodeEditor_MyNewScript::create(),
			ConstantString::create(std::to_string(this->scripts.size()))
		});

		std::string script = this->hackableCode == nullptr ? "" : this->hackableCode->getOriginalAssemblyString();
		ScriptEntry* newScriptEntry = ScriptEntry::create(ConstantString::create(newScriptName->getString()), script, [=](ScriptEntry* entry) { this->onScriptSelect(entry); });
		this->scripts.push_back(newScriptEntry);
		this->scriptsNode->addChild(newScriptEntry);

		this->setActiveScript(newScriptEntry);

		// Re-initialize positions
		this->initializePositions();
	}
}

void ScriptList::deleteActiveScript()
{
	if (this->activeScript != nullptr && this->scripts.size() > 1)
	{
		this->scriptsNode->removeChild(this->activeScript);

		this->setActiveScript(scripts.front());
	}
}

void ScriptList::loadScripts(HackableCode* hackableCode)
{
	this->hackableCode = hackableCode;
	this->scriptsNode->removeAllChildren();
	this->scripts.clear();

	ValueMap savedScripts = SaveManager::getProfileDataOrDefault(hackableCode->getHackableCodeIdentifier(), Value(ValueMap())).asValueMap();

	if (savedScripts.empty())
	{
		this->addNewScript();
	}
	else
	{
		// Add user scripts
		for (auto it = savedScripts.begin(); it != savedScripts.end(); it++)
		{
			ScriptEntry* scriptEntry = ScriptEntry::create(ConstantString::create(it->first), it->second.asString(), [=](ScriptEntry* entry) { this->onScriptEntryClick(entry); });

			this->scripts.push_back(scriptEntry);
			this->scriptsNode->addChild(scriptEntry);
		}
	}

	this->setActiveScript(scripts.front());
}

ScriptEntry* ScriptList::getActiveScript()
{
	return this->activeScript;
}

void ScriptList::onScriptEntryClick(ScriptEntry* scriptEntry)
{
	this->setActiveScript(scriptEntry);

	this->onScriptSelect(scriptEntry);
}

void ScriptList::setActiveScript(ScriptEntry* activeScript)
{
	this->activeScript = activeScript;

	for (auto it = this->scripts.begin(); it != this->scripts.end(); it++)
	{
		(*it)->toggleSelected(false);
	}

	this->activeScript->toggleSelected(true);
}
