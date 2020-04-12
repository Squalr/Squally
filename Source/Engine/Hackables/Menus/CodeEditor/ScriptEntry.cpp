#include "ScriptEntry.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Save/SaveManager.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ScriptEntry* ScriptEntry::create(LocalizedString* scriptName, std::string script, bool isReadOnly, std::function<void(ScriptEntry*)> onScriptEntryClick, std::function<void(ScriptEntry*)> onCopyClick, std::function<void(ScriptEntry*)> onDeleteClick)
{
	ScriptEntry* instance = new ScriptEntry(scriptName, script, isReadOnly, onScriptEntryClick, onCopyClick, onDeleteClick);

	instance->autorelease();

	return instance;
}

ScriptEntry::ScriptEntry(LocalizedString* scriptName, std::string script, bool isReadOnly, std::function<void(ScriptEntry*)> onScriptEntryClick, std::function<void(ScriptEntry*)> onCopyClick, std::function<void(ScriptEntry*)> onDeleteClick)
{
	this->scriptName = scriptName;
	this->script = script;
	this->isReadOnly = isReadOnly;
	this->onScriptEntryClick = onScriptEntryClick;
	this->onCopyClick = onCopyClick;
	this->onDeleteClick = onDeleteClick;
	this->deleteButton = nullptr;
	this->deletePanel = nullptr;
	this->deleteLabel = nullptr;
	
	if (this->isReadOnly)
	{
		LocalizedString* readOnly = Strings::Menus_Hacking_CodeEditor_Readonly::create();

		readOnly->setStringReplacementVariables(this->scriptName);
		
		this->scriptName = readOnly;

		this->backPlate = ClickableNode::create(UIResources::Menus_HackerModeMenu_NewScriptEntry, UIResources::Menus_HackerModeMenu_NewScriptEntrySelected);
	}
	else
	{
		this->backPlate = ClickableNode::create(UIResources::Menus_HackerModeMenu_ScriptEntry, UIResources::Menus_HackerModeMenu_ScriptEntrySelected);
	}

	this->selectedSprite = Sprite::create(UIResources::Menus_HackerModeMenu_SelectedScriptArrow);
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, this->scriptName);
	this->copyButton = ClickableNode::create(UIResources::Menus_HackerModeMenu_Copy, UIResources::Menus_HackerModeMenu_CopySelected);
	this->copyPanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
	this->copyLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_CopyScript::create());

	this->selectedSprite->setColor(Color3B::YELLOW);
	this->selectedSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->label->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->backPlate);
	this->addChild(this->selectedSprite);
	this->addChild(this->label);
	this->addChild(this->copyButton);

	if (!this->isReadOnly)
	{
		this->deletePanel = LayerColor::create(Color4B::BLACK, 256.0f, 48.0f);
		this->deleteLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Hacking_CodeEditor_DeleteScript::create());
		this->deleteButton = ClickableNode::create(UIResources::Menus_HackerModeMenu_TrashCan, UIResources::Menus_HackerModeMenu_TrashCanSelected);
		this->addChild(this->deleteButton);
		this->addChild(this->deletePanel);
		this->addChild(this->deleteLabel);
	}

	this->addChild(this->copyPanel);
	this->addChild(this->copyLabel);
}

ScriptEntry::~ScriptEntry()
{
}

void ScriptEntry::onEnter()
{
	super::onEnter();
	
	if (this->deleteButton != nullptr)
	{
		this->deletePanel->setOpacity(0);
		this->deleteLabel->setOpacity(0);
	}

	this->copyPanel->setOpacity(0);
	this->copyLabel->setOpacity(0);
}

void ScriptEntry::initializePositions()
{
	super::initializePositions();

	const float Margin = 16.0f;

	this->label->setPositionX(-this->backPlate->getContentSize().width / 2.0f + Margin);
	this->selectedSprite->setPositionX(-this->backPlate->getContentSize().width / 2.0f + Margin);
	this->copyButton->setPositionX(this->backPlate->getContentSize().width / 2.0f - 24.0f);
	this->copyPanel->setPosition(this->copyButton->getPosition() + Vec2(0.0f, 48.0f) - Vec2(this->copyPanel->getContentSize() / 2.0f));
	this->copyLabel->setPosition(this->copyButton->getPosition() + Vec2(0.0f, 48.0f));

	if (this->deleteButton != nullptr)
	{
		this->deleteButton->setPositionX(this->backPlate->getContentSize().width / 2.0f - 24.0f - 40.0f);
		this->deletePanel->setPosition(this->deleteButton->getPosition() + Vec2(0.0f, 48.0f) - Vec2(this->deletePanel->getContentSize() / 2.0f));
		this->deleteLabel->setPosition(this->deleteButton->getPosition() + Vec2(0.0f, 48.0f));
	}
}

void ScriptEntry::initializeListeners()
{
	super::initializeListeners();

	this->backPlate->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->onScriptEntryClick != nullptr)
		{
			this->onScriptEntryClick(this);
		}
	});

	this->copyButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->onCopyClick != nullptr)
		{
			this->onCopyClick(this);
		}
	});
	
	if (this->deleteButton != nullptr)
	{
		this->deleteButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
		{
			if (this->onDeleteClick != nullptr)
			{
				this->onDeleteClick(this);
			}
		});
	}

	if (this->deleteButton != nullptr)
	{
		this->deleteButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
		{
			this->deletePanel->setOpacity(196);
			this->deleteLabel->setOpacity(255);
		});
		this->deleteButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
		{
			this->deletePanel->setOpacity(0);
			this->deleteLabel->setOpacity(0);
		});
	}

	this->copyButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->copyPanel->setOpacity(196);
		this->copyLabel->setOpacity(255);
	});
	this->copyButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->copyPanel->setOpacity(0);
		this->copyLabel->setOpacity(0);
	});
}

void ScriptEntry::toggleSelected(bool isSelected)
{
	const float Margin = 16.0f;
	const float SelectedOffset = 32.0f;

	this->selectedSprite->setVisible(isSelected);

	this->label->setTextColor(isSelected ? Color4B::YELLOW : Color4B::WHITE);
	this->label->setPositionX(-this->backPlate->getContentSize().width / 2.0f + Margin + (isSelected ? SelectedOffset : 0.0f));
}

void ScriptEntry::deleteScript()
{
	if (this->onDeleteClick != nullptr)
	{
		this->onDeleteClick(this);
	}
}

void ScriptEntry::copyScript()
{
	if (this->onCopyClick != nullptr)
	{
		this->onCopyClick(this);
	}
}

LocalizedString* ScriptEntry::getName()
{
	return this->scriptName;
}

void ScriptEntry::setName(std::string name)
{
	if (dynamic_cast<ConstantString*>(this->scriptName) != nullptr)
	{
		dynamic_cast<ConstantString*>(this->scriptName)->setString(name);
	}
}

std::string ScriptEntry::getScript()
{
	return this->script;
}

void ScriptEntry::setScript(std::string script)
{
	this->script = script;
}
