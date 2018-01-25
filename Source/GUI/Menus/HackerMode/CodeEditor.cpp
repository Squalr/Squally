#include "CodeEditor.h"

CodeEditor* CodeEditor::create()
{
	CodeEditor* codeEditor = new CodeEditor();

	codeEditor->autorelease();

	return codeEditor;
}

CodeEditor::CodeEditor()
{
	this->codeEditorBackground = Sprite::create(Resources::Menus_HackerModeMenu_CodeMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);

	this->initializePositions();
	this->initializeListeners();
}

CodeEditor::~CodeEditor()
{
}

void CodeEditor::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeEditorBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 336.0f));
}

void CodeEditor::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onClose, this));
}

void CodeEditor::open(HackableCode* hackableCode)
{
	const float spacing = -36.0f;
	const float fontSize = 24.0f;

	this->setVisible(true);
	Utils::focus(this);
}

void CodeEditor::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
