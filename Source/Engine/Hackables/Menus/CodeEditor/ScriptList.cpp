#include "ScriptList.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/Menus/CodeEditor/ScriptEntry.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Menus/Confirmation/ConfirmationMenu.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ScriptList::ScriptNameKey = "SCRIPT_NAME";
const std::string ScriptList::ScriptKey = "SCRIPT";
const std::string ScriptList::SaveKeyLastSelectedScriptIndexPrefix = "SAVE_KEY_SCRIPT_INDEX_";
const int ScriptList::MaxScripts = 9;

ScriptList* ScriptList::create(ConfirmationMenu* confirmationMenuRef, std::function<void(ScriptEntry*)> onScriptSelect)
{
	ScriptList* instance = new ScriptList(confirmationMenuRef, onScriptSelect);

	instance->autorelease();

	return instance;
}

ScriptList::ScriptList(ConfirmationMenu* confirmationMenuRef, std::function<void(ScriptEntry*)> onScriptSelect)
{
	this->onScriptSelect = onScriptSelect;
	this->scriptsNode = Node::create();
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Hacking_CodeEditor_YourScripts::create());
	this->scripts = std::vector<ScriptEntry*>();
	this->createNewScriptButton = ClickableNode::create(UIResources::Menus_HackerModeMenu_ScriptEntry, UIResources::Menus_HackerModeMenu_ScriptEntrySelected);
	this->createNewScriptLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_CreateNewScript::create());
	this->createNewScriptSprite = Sprite::create(UIResources::Menus_HackerModeMenu_Plus);
	this->confirmationMenuRef = confirmationMenuRef;
	this->hackableCode = nullptr;
	this->activeScript = nullptr;
	this->readOnlyCount = 0;

	this->createNewScriptLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->createNewScriptSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->createNewScriptButton->addChild(this->createNewScriptLabel);
	this->createNewScriptButton->addChild(this->createNewScriptSprite);

	this->addChild(this->titleLabel);
	this->addChild(this->scriptsNode);
	this->addChild(this->createNewScriptButton);
}

ScriptList::~ScriptList()
{
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

	for (auto script : this->scripts)
	{
		script->setPosition(Vec2(0.0f, -((float)index++ * entrySize) - titleOffset));
	}

	this->createNewScriptButton->setPosition(Vec2(0.0f, -((float)index++ * entrySize) - titleOffset - 8.0f));
}

void ScriptList::initializeListeners()
{
	super::initializeListeners();

	this->createNewScriptButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->addNewScript(); });
}

void ScriptList::setActiveScriptText(std::string text)
{
	if (this->activeScript != nullptr)
	{
		this->activeScript->setScript(text);
	}
}

ScriptEntry* ScriptList::addNewScript()
{
	if (this->scripts.size() >= ScriptList::MaxScripts)
	{
		return nullptr;
	}

	LocalizedString* newScriptName = Strings::Common_ConcatSpaced::create();

	newScriptName->setStringReplacementVariables(
	{
		Strings::Menus_Hacking_CodeEditor_MyNewScript::create(),
		ConstantString::create(std::to_string(int(this->scripts.size()) - this->readOnlyCount + 1))
	});

	std::string script = this->hackableCode == nullptr ? "" : this->hackableCode->getOriginalAssemblyString();
	ScriptEntry* newScriptEntry = ScriptEntry::create(
		ConstantString::create(newScriptName->getString()),
		script,
		false,
		[=](ScriptEntry* entry) { this->onScriptEntryClick(entry); }, 
		[=](ScriptEntry* entry) { this->onScriptEntryCopyClick(entry); },
		[=](ScriptEntry* entry) { this->onScriptEntryDeleteClick(entry); }
	);
	
	this->scripts.push_back(newScriptEntry);
	this->scriptsNode->addChild(newScriptEntry);

	this->setActiveScript(newScriptEntry);

	// Re-initialize positions
	this->initializePositions();

	return newScriptEntry;
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

	LocalizedString* scriptName = (scriptEntry->getName() == nullptr) ? Strings::Menus_Hacking_CodeEditor_UnnamedScript::create() : scriptEntry->getName()->clone();
	
	GameUtils::focus(this->confirmationMenuRef);

	this->confirmationMenuRef->showMessage(Strings::Menus_Hacking_CodeEditor_DeleteConfirmation::create()->setStringReplacementVariables(scriptName),
	[=]()
	{
		int scriptIndex = std::distance(this->scripts.begin(), std::find(this->scripts.begin(), this->scripts.end(), scriptEntry));

		this->scripts.erase(std::remove(this->scripts.begin(), this->scripts.end(), scriptEntry), this->scripts.end());
		this->scriptsNode->removeChild(scriptEntry);

		// Re-initialize positions
		this->initializePositions();

		if (scriptEntry == this->activeScript)
		{
			if (!this->scripts.empty())
			{
				scriptIndex = MathUtils::clamp(scriptIndex, 0, this->scripts.size() - 1);

				this->setActiveScript(scripts[scriptIndex]);
			}
			else
			{
				this->addNewScript();
			}
		}

		GameUtils::focus(this->getParent());

		return false;
	},
	[=]()
	{
		GameUtils::focus(this->getParent());

		return false;
	});
}

void ScriptList::copyScript(ScriptEntry* scriptEntry)
{
	ScriptEntry* newScript = this->addNewScript();

	// Exit if unable to create a new script (ie script list is full)
	if (newScript == nullptr)
	{
		return;
	}

	newScript->setScript(scriptEntry->getScript());

	// For now, no name copy is made.
	// newScript->setName(scriptEntry->getName() == nullptr ? "" : scriptEntry->getName()->getString());

	// Refresh view
	this->onScriptSelect(this->activeScript);
}

void ScriptList::loadScripts(HackableCode* hackableCode)
{
	this->hackableCode = hackableCode;
	this->scriptsNode->removeAllChildren();
	this->scripts.clear();

	std::vector<HackableCode::ReadOnlyScript> readonlyScripts = hackableCode->getReadOnlyScripts();
	this->readOnlyCount = int(readonlyScripts.size());

	for (auto readOnlyScript : readonlyScripts)
	{
		ScriptEntry* scriptEntry = ScriptEntry::create(
			readOnlyScript.title == nullptr ? nullptr : readOnlyScript.title->clone(),
			(sizeof(void*) == 4) ? readOnlyScript.scriptx86 : readOnlyScript.scriptx64,
			true,
			[=](ScriptEntry* entry) { this->onScriptEntryClick(entry); }, 
			[=](ScriptEntry* entry) { this->onScriptEntryCopyClick(entry); }, 
			nullptr
		);

		this->scripts.push_back(scriptEntry);
		this->scriptsNode->addChild(scriptEntry);
	}

	ValueVector savedScripts = SaveManager::GetProfileDataOrDefault(hackableCode->getHackableIdentifier(), Value(ValueVector())).asValueVector();

	// Add user scripts
	for (auto savedScript : savedScripts)
	{
		ValueMap attributes = savedScript.asValueMap();
		const std::string scriptName = attributes[ScriptList::ScriptNameKey].asString();
		const std::string script = attributes[ScriptList::ScriptKey].asString();

		ScriptEntry* scriptEntry = ScriptEntry::create(
			ConstantString::create(scriptName),
			script,
			false,
			[=](ScriptEntry* entry) { this->onScriptEntryClick(entry); }, 
			[=](ScriptEntry* entry) { this->onScriptEntryCopyClick(entry); },
			[=](ScriptEntry* entry) { this->onScriptEntryDeleteClick(entry); }
		);

		this->scripts.push_back(scriptEntry);
		this->scriptsNode->addChild(scriptEntry);
	}

	// Adding an initial fork of the default script is only useful when it is the ONLY readonly script.
	if (savedScripts.empty() && readonlyScripts.size() <= 1)
	{
		this->addNewScript();
	}

	this->initializePositions();

	// Try focusing the saved last selected script
	if (SaveManager::HasProfileData(ScriptList::SaveKeyLastSelectedScriptIndexPrefix + this->hackableCode->getHackableIdentifier()))
	{
		int activeScriptIndex = SaveManager::GetProfileDataOrDefault(ScriptList::SaveKeyLastSelectedScriptIndexPrefix + this->hackableCode->getHackableIdentifier(), Value(-1)).asInt();

		if (activeScriptIndex >= 0 && activeScriptIndex < int(this->scripts.size()))
		{
			this->setActiveScript(this->scripts[activeScriptIndex]);
			return;
		}
	}

	// Focus the first non-readonly script
	for (auto script : this->scripts)
	{
		if (script->isReadOnly)
		{
			continue;
		}

		this->setActiveScript(script);
		return;
	}

	// If none found, focus the last script
	for (auto it = this->scripts.rbegin(); it != this->scripts.rend(); it++)
	{
		this->setActiveScript(*it);
		return;
	}
}

void ScriptList::saveScripts()
{
	ValueVector scriptsToSave = ValueVector();

	for (auto script : this->scripts)
	{
		if (script->isReadOnly)
		{
			continue;
		}

		ValueMap attributes = ValueMap();

		attributes[ScriptList::ScriptNameKey] = Value(script->getName()->getString());
		attributes[ScriptList::ScriptKey] = Value(script->getScript());

		scriptsToSave.push_back(Value(attributes));
	}

	SaveManager::SaveProfileData(this->hackableCode->getHackableIdentifier(), Value(scriptsToSave));
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

void ScriptList::onScriptEntryCopyClick(ScriptEntry* scriptEntry)
{
	this->copyScript(scriptEntry);
}

void ScriptList::onScriptEntryDeleteClick(ScriptEntry* scriptEntry)
{
	this->deleteScript(scriptEntry);
}

void ScriptList::setActiveScript(ScriptEntry* activeScript)
{
	int activeScriptIndex = 0;
	this->activeScript = activeScript;

	for (int index = 0; index < int(this->scripts.size()); index++)
	{
		if (this->scripts[index] == this->activeScript)
		{
			activeScriptIndex = index;
		}

		this->scripts[index]->toggleSelected(false);
	}

	SaveManager::SoftSaveProfileData(ScriptList::SaveKeyLastSelectedScriptIndexPrefix + this->hackableCode->getHackableIdentifier(), Value(activeScriptIndex));

	this->activeScript->toggleSelected(true);
	this->onScriptSelect(this->activeScript);
}
