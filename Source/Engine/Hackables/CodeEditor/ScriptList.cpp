#include "ScriptList.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/CodeEditor/ScriptEntry.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Save/SaveManager.h"

#include "Strings/Hacking/CodeEditor/NewScript.h"
#include "Strings/Hacking/CodeEditor/OriginalCode.h"
#include "Strings/Hacking/CodeEditor/YourScripts.h"

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

	this->addChild(this->titleLabel);
	this->addChild(this->scriptsNode);
}

void ScriptList::initializePositions()
{
	super::initializePositions();

	const float titleOffset = 48.0f;
	const float entrySize = 48.0f;
	int index = 0;

	for (auto it = this->scripts.begin(); it != this->scripts.end(); it++)
	{
		(*it)->setPosition(Vec2(0.0f, -((float)index * entrySize) - titleOffset));

		index++;
	}
}

void ScriptList::setActiveScriptText(std::string text)
{
	if (!this->scripts.empty())
	{
		if (this->activeScript == this->scripts.front())
		{
			ScriptEntry* newScript = ScriptEntry::create(Strings::Hacking_CodeEditor_NewScript::create(), text, [=](ScriptEntry* entry) { this->onScriptSelect(entry); });
			this->scripts.push_back(newScript);
			this->scriptsNode->addChild(newScript);

			this->activeScript = newScript;

			// Re-initialize positions
			this->initializePositions();
		}
		else
		{
			this->activeScript->setScriptUnsaved(text);
		}
	}
}

void ScriptList::loadScripts(HackableCode* hackableCode)
{
	this->scriptsNode->removeAllChildren();
	this->scripts.clear();

	ValueMap savedScripts = SaveManager::getProfileDataOrDefault(hackableCode->getHackableCodeIdentifier(), Value(ValueMap())).asValueMap();

	// Add the original script
	{
		std::string script = hackableCode->getOriginalAssemblyString();
		ScriptEntry* scriptEntry = ScriptEntry::create(Strings::Hacking_CodeEditor_OriginalCode::create(), script, [=](ScriptEntry* entry) { this->onScriptEntryClick(entry); });
		this->scripts.push_back(scriptEntry);
		this->scriptsNode->addChild(scriptEntry);
		this->activeScript = scriptEntry;
	}

	// Add user scripts
	for (auto it = savedScripts.begin(); it != savedScripts.end(); it++)
	{
		ScriptEntry* scriptEntry = ScriptEntry::create(ConstantString::create(it->first), it->second.asString(), [=](ScriptEntry* entry) { this->onScriptEntryClick(entry); });
		this->scripts.push_back(scriptEntry);
		this->scriptsNode->addChild(scriptEntry);
	}
}

void ScriptList::onScriptEntryClick(ScriptEntry* scriptEntry)
{
	this->activeScript = scriptEntry;

	this->onScriptSelect(scriptEntry);
}
