#include "ScriptList.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/CodeEditor/ScriptEntry.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Save/SaveManager.h"

#include "Strings/Generics/Count.h"
#include "Strings/Hacking/CodeEditor/CreateNewScript.h"
#include "Strings/Hacking/CodeEditor/MyNewScript.h"
#include "Strings/Hacking/CodeEditor/YourScripts.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ScriptList::ScriptNameKey = "SCRIPT_NAME";
const std::string ScriptList::ScriptKey = "SCRIPT";

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
	this->createNewScriptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hacking_CodeEditor_CreateNewScript::create());
	this->createNewScriptSprite = Sprite::create(UIResources::Menus_HackerModeMenu_Plus);
	this->hackableCode = nullptr;
	this->activeScript = nullptr;

	this->createNewScriptLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->createNewScriptSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->createNewScriptButton->addChild(this->createNewScriptLabel);
	this->createNewScriptButton->addChild(this->createNewScriptSprite);

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
	this->createNewScriptLabel->setPositionX(-this->createNewScriptButton->getContentSize().width / 2.0f + 32.0f + margin);
	this->createNewScriptSprite->setPositionX(-this->createNewScriptButton->getContentSize().width / 2.0f + margin);

	for (auto it = this->scripts.begin(); it != this->scripts.end(); it++)
	{
		(*it)->setPosition(Vec2(0.0f, -((float)index++ * entrySize) - titleOffset));
	}

	this->createNewScriptButton->setPosition(Vec2(0.0f, -((float)index++ * entrySize) - titleOffset - 8.0f));
}

void ScriptList::initializeListeners()
{
	super::initializeListeners();

	this->createNewScriptButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*) { this->addNewScript(); });
}

void ScriptList::setActiveScriptText(std::string text)
{
	if (this->activeScript != nullptr)
	{
		this->activeScript->setScript(text);
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
		ScriptEntry* newScriptEntry = ScriptEntry::create(ConstantString::create(newScriptName->getString()), script, CC_CALLBACK_1(ScriptList::onScriptEntryClick, this), CC_CALLBACK_1(ScriptList::onScriptEntryDeleteClick, this));
		this->scripts.push_back(newScriptEntry);
		this->scriptsNode->addChild(newScriptEntry);

		this->setActiveScript(newScriptEntry);

		// Re-initialize positions
		this->initializePositions();
	}
}

void ScriptList::deleteActiveScript()
{
	this->deleteScript(this->activeScript);
}

void ScriptList::deleteScript(ScriptEntry* scriptEntry)
{
	if (scriptEntry == nullptr || std::find(this->scripts.begin(), this->scripts.end(), scriptEntry) == this->scripts.end())
	{
		return;
	}

	this->scripts.erase(std::remove(this->scripts.begin(), this->scripts.end(), scriptEntry), this->scripts.end());
	this->scriptsNode->removeChild(scriptEntry);

	// Re-initialize positions
	this->initializePositions();

	if (scriptEntry == this->activeScript)
	{
		if (!this->scripts.empty())
		{
			this->setActiveScript(scripts.front());
		}
		else
		{
			this->addNewScript();
		}
	}
}

void ScriptList::loadScripts(HackableCode* hackableCode)
{
	this->hackableCode = hackableCode;
	this->scriptsNode->removeAllChildren();
	this->scripts.clear();

	ValueVector savedScripts = SaveManager::getProfileDataOrDefault(hackableCode->getHackableCodeIdentifier(), Value(ValueVector())).asValueVector();

	if (savedScripts.empty())
	{
		this->addNewScript();
	}
	else
	{
		// Add user scripts
		for (auto it = savedScripts.begin(); it != savedScripts.end(); it++)
		{
			ValueMap attributes = it->asValueMap();
			const std::string scriptName = attributes[ScriptList::ScriptNameKey].asString();
			const std::string script = attributes[ScriptList::ScriptKey].asString();

			ScriptEntry* scriptEntry = ScriptEntry::create(ConstantString::create(scriptName), script, CC_CALLBACK_1(ScriptList::onScriptEntryClick, this), CC_CALLBACK_1(ScriptList::onScriptEntryDeleteClick, this));

			this->scripts.push_back(scriptEntry);
			this->scriptsNode->addChild(scriptEntry);
		}
	}

	this->initializePositions();

	this->setActiveScript(scripts.front());
}

void ScriptList::saveScripts()
{
	ValueVector scriptsToSave = ValueVector();

	for (auto it = this->scripts.begin(); it != this->scripts.end(); it++)
	{
		ValueMap attributes = ValueMap();

		attributes[ScriptList::ScriptNameKey] = Value((*it)->getName()->getString());
		attributes[ScriptList::ScriptKey] = Value((*it)->getScript());

		scriptsToSave.push_back(Value(attributes));
	}

	SaveManager::saveProfileData(this->hackableCode->getHackableCodeIdentifier(), Value(scriptsToSave));
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

void ScriptList::onScriptEntryDeleteClick(ScriptEntry* scriptEntry)
{
	this->deleteScript(scriptEntry);
}

void ScriptList::setActiveScript(ScriptEntry* activeScript)
{
	this->activeScript = activeScript;

	for (auto it = this->scripts.begin(); it != this->scripts.end(); it++)
	{
		(*it)->toggleSelected(false);
	}

	this->activeScript->toggleSelected(true);
	this->onScriptSelect(this->activeScript);
}
