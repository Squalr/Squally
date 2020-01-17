#include "ScriptList.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/CodeEditor/ScriptEntry.h"
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

	LocalizedString* newScriptName = Strings::Common_Count::create();

	newScriptName->setStringReplacementVariables(
	{
		Strings::Menus_Hacking_CodeEditor_MyNewScript::create(),
		ConstantString::create(std::to_string(this->scripts.size()))
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
	},
	[=]()
	{
		GameUtils::focus(this->getParent());
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

	for (auto readOnlyScript : hackableCode->getReadOnlyScripts())
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

	ValueVector savedScripts = SaveManager::getProfileDataOrDefault(hackableCode->getHackableCodeIdentifier(), Value(ValueVector())).asValueVector();

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

	if (savedScripts.empty())
	{
		this->addNewScript();
	}

	this->initializePositions();

	// Focus the first non-readonly script
	for (auto script : this->scripts)
	{
		if (script->isReadOnly)
		{
			continue;
		}

		this->setActiveScript(script);
		break;
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

	SaveManager::SaveProfileData(this->hackableCode->getHackableCodeIdentifier(), Value(scriptsToSave));
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
	this->activeScript = activeScript;

	for (auto script : this->scripts)
	{
		script->toggleSelected(false);
	}

	this->activeScript->toggleSelected(true);
	this->onScriptSelect(this->activeScript);
}
