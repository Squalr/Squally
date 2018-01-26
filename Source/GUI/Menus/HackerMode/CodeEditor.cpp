#include "CodeEditor.h"

const Size CodeEditor::textSize = Size(480.0f, 640.0f);

CodeEditor* CodeEditor::create()
{
	CodeEditor* codeEditor = new CodeEditor();

	codeEditor->autorelease();

	return codeEditor;
}

CodeEditor::CodeEditor()
{
	this->displayTextElements = new std::vector<RichElementText*>();
	this->codeEditorBackground = Sprite::create(Resources::Menus_HackerModeMenu_CodeEditMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);
	this->assemblyCodeText = EditBox::create(CodeEditor::textSize, Resources::EmptyImage);
	this->displayText = RichText::create();

	this->assemblyCodeText->setFontName(Resources::Fonts_Montserrat_Medium.c_str());
	this->assemblyCodeText->setFontSize(24);
	this->assemblyCodeText->setFontColor(Color3B::WHITE);
	this->assemblyCodeText->setPlaceHolder("<Assembly code here>");
	this->assemblyCodeText->setPlaceholderFontColor(Color3B::GRAY);
	this->assemblyCodeText->setPlaceholderFontSize(24);
	this->assemblyCodeText->setInputMode(EditBox::InputMode::ANY);
	this->assemblyCodeText->setInputFlag(EditBox::InputFlag::SENSITIVE);
	this->assemblyCodeText->setOpacity(0);
	this->assemblyCodeText->setCascadeOpacityEnabled(true);

	this->displayText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->codeEditorBackground);
	this->addChild(this->closeButton);
	this->addChild(this->assemblyCodeText);
	this->addChild(this->displayText);

	this->initializePositions();
	this->initializeListeners();
	this->scheduleUpdate();
}

CodeEditor::~CodeEditor()
{
	delete(this->displayTextElements);
}

void CodeEditor::update(float dt)
{
	if (this->previousAssemblyText != this->assemblyCodeText->getText())
	{
		this->previousAssemblyText = this->assemblyCodeText->getText();

		for (auto iterator = this->displayTextElements->begin(); iterator != this->displayTextElements->end(); iterator++)
		{
			this->displayText->removeElement(*iterator);
		}

		this->displayTextElements->clear();

		// Reconstruct text
		RichElementText* element = RichElementText::create(0, Color3B::WHITE, 255, this->assemblyCodeText->getText(), Resources::Fonts_Montserrat_Medium, 24);
		this->displayTextElements->push_back(element);
		this->displayText->pushBackElement(element);
	}
}

void CodeEditor::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeEditorBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 336.0f));
	this->assemblyCodeText->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->displayText->setPosition(Vec2(visibleSize.width / 2.0f - CodeEditor::textSize.width / 2, visibleSize.height / 2.0f + CodeEditor::textSize.height / 2));
}

void CodeEditor::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onClose, this));
}

void CodeEditor::open(HackableCode* hackableCode)
{
	this->assemblyCodeText->setText(HackUtils::disassemble(hackableCode->codePointer, hackableCode->codeOriginalLength).c_str());

	this->setVisible(true);
	Utils::focus(this);
}

void CodeEditor::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
