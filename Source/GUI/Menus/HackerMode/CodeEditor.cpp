#include "CodeEditor.h"

const float CodeEditor::compileDelayMaxSeconds = 0.1f;
const Size CodeEditor::textSize = Size(448.0f, 640.0f);
const std::string CodeEditor::delimiters = "[],; \n\t";
const Color3B CodeEditor::defaultColor = Color3B::WHITE;
const Color3B CodeEditor::subtextColor = Color3B::GRAY;
const Color3B CodeEditor::headerColor = Color3B(188, 188, 64);
const Color3B CodeEditor::errorColor = Color3B(196, 82, 82);
const Color3B CodeEditor::registerColor = Color3B(86, 156, 214);
const Color3B CodeEditor::numberColor = Color3B(181, 206, 168); // Color3B(78, 201, 176);
const Color3B CodeEditor::commentColor = Color3B(87, 166, 74);

const std::set<std::string> CodeEditor::registers =
{
	// General registers
	"ax", "bx", "cx", "dx", "si", "di", "bp", "sp",
	"r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w",
	"al", "bl", "cl", "dl", "sil", "dil", "bpl", "spl",
	"r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b",
	"eax", "ebx", "ecx" ,"edx" ,"esi", "edi", "ebp", "esp",
	"r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d",
	"rax", "rbx", "rcx" ,"rdx" ,"rdi", "rsi", "rbp", "rsp",
	"r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",

	// FPU registers
	"fp0", "fp1", "fp2", "fp3", "fp4", "fp5", "fp6", "fp7",

	// MMX registers
	"mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7",
	"mm8", "mm9", "mm10", "mm11", "mm12", "mm13", "mm14", "mm15",
	"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
	"xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15",
	"ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7",
	"ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15",

	// Segment registers
	"cs", "ds", "es", "fs", "gs", "ss",

	// Instruction pointers
	"eip", "rip"
};

CodeEditor* CodeEditor::create()
{
	CodeEditor* codeEditor = new CodeEditor();

	codeEditor->autorelease();

	return codeEditor;
}

CodeEditor::CodeEditor()
{
	this->compileDelay = CodeEditor::compileDelayMaxSeconds;
	this->activeHackableCode = nullptr;
	this->displayTextElements = new std::vector<RichElement*>();
	this->outputTextElements = new std::vector<RichElement*>();

	this->codeEditorBackground = Sprite::create(Resources::Menus_HackerModeMenu_CodeEditMenu);
	this->codeEditorScrollView = ScrollView::create();
	this->assemblyCodeText = TextField::create("<Click to Edit Assembly Code>", Resources::Fonts_UbuntuMono_B, 32);
	this->displayText = RichText::create();
	this->cancelButton = MenuSprite::create(Resources::Menus_Buttons_CancelButton, Resources::Menus_Buttons_CancelButtonHover, Resources::Menus_Buttons_CancelButtonClick);
	this->acceptButton = MenuSprite::create(Resources::Menus_Buttons_AcceptButton, Resources::Menus_Buttons_AcceptButtonHover, Resources::Menus_Buttons_AcceptButtonClick);
	this->acceptButtonGrayed = Sprite::create(Resources::Menus_Buttons_AcceptButtonGray);
	this->codeEditorTitle = MenuLabel::create("Code Editor", Resources::Fonts_Montserrat_Medium, 32);

	this->allocEditorBackground = Sprite::create(Resources::Menus_HackerModeMenu_OutputMenu);
	this->allocEditorTitle = MenuLabel::create("Alloc Editor", Resources::Fonts_Montserrat_Medium, 32);

	this->outputBackground = Sprite::create(Resources::Menus_HackerModeMenu_OutputMenu);
	this->outputTitle = MenuLabel::create("Status", Resources::Fonts_Montserrat_Medium, 32);
	this->outputScrollView = ScrollView::create();
	this->outputText = RichText::create();

	this->acceptButtonGrayed->setVisible(false);

	this->codeEditorScrollView->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->assemblyCodeText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->assemblyCodeText->setOpacity(0);
	this->assemblyCodeText->setCascadeOpacityEnabled(false);
	this->assemblyCodeText->setCursorEnabled(true);
	this->assemblyCodeText->setHighlighted(true);
	this->assemblyCodeText->setSize(CodeEditor::textSize);
	this->assemblyCodeText->ignoreContentAdaptWithSize(false);
	this->displayText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->displayText->setSize(CodeEditor::textSize);
	this->displayText->ignoreContentAdaptWithSize(false);
	this->outputScrollView->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->outputText->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->outputText->setSize(CodeEditor::textSize);
	this->outputText->ignoreContentAdaptWithSize(false);

	this->codeEditorScrollView->setSize(CodeEditor::textSize);
	this->codeEditorScrollView->setDirection(SCROLLVIEW_DIR_BOTH);
	this->codeEditorScrollView->setInnerContainerSize(Size(CodeEditor::textSize.width, CodeEditor::textSize.height * 2));

	this->outputScrollView->setSize(CodeEditor::textSize);
	this->outputScrollView->setDirection(SCROLLVIEW_DIR_BOTH);
	this->outputScrollView->setInnerContainerSize(Size(CodeEditor::textSize.width, CodeEditor::textSize.height * 2));

	this->codeEditorScrollView->addChild(this->assemblyCodeText);
	this->codeEditorScrollView->addChild(this->displayText);
	this->outputScrollView->addChild(this->outputText);

	this->addChild(this->codeEditorBackground);
	this->addChild(this->codeEditorScrollView);
	this->addChild(this->cancelButton);
	this->addChild(this->acceptButton);
	this->addChild(this->acceptButtonGrayed);
	this->addChild(this->codeEditorTitle);

	this->addChild(this->allocEditorBackground);
	this->addChild(this->allocEditorTitle);

	this->addChild(this->outputBackground);
	this->addChild(this->outputTitle);
	this->addChild(this->outputScrollView);

	this->initializePositions();
	this->initializeListeners();
	this->scheduleUpdate();
}

CodeEditor::~CodeEditor()
{
	delete(this->displayTextElements);
	delete(this->outputTextElements);
}

void CodeEditor::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeEditorBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->acceptButton->setPosition(Vec2(this->codeEditorBackground->getPositionX() + 224.0f, this->codeEditorBackground->getPositionY() - 336.0f));
	this->cancelButton->setPosition(Vec2(this->codeEditorBackground->getPositionX() - 224.0f, this->codeEditorBackground->getPositionY() - 336.0f));
	this->acceptButtonGrayed->setPosition(this->acceptButton->getPosition());
	this->codeEditorScrollView->setPosition(Vec2(this->codeEditorBackground->getPositionX() - CodeEditor::textSize.width / 2, this->codeEditorBackground->getPositionY() + CodeEditor::textSize.height / 2 - 32.0f));
	this->assemblyCodeText->setPosition(Vec2(0.0f, this->codeEditorScrollView->getInnerContainerSize().height));
	this->displayText->setPosition(this->assemblyCodeText->getPosition());
	this->codeEditorTitle->setPosition(this->codeEditorBackground->getPositionX(), this->codeEditorBackground->getPositionY() + 340.0f);

	this->allocEditorBackground->setPosition(Vec2(visibleSize.width / 2.0f + 640.0f, visibleSize.height / 2.0f));
	this->allocEditorTitle->setPosition(this->allocEditorBackground->getPositionX(), this->allocEditorBackground->getPositionY() + 340.0f);

	this->outputBackground->setPosition(Vec2(visibleSize.width / 2.0f - 640.0f, visibleSize.height / 2.0f));
	this->outputTitle->setPosition(this->outputBackground->getPositionX(), this->outputBackground->getPositionY() + 340.0f);
	this->outputScrollView->setPosition(Vec2(this->outputBackground->getPositionX() - CodeEditor::textSize.width / 2, this->outputBackground->getPositionY() + CodeEditor::textSize.height / 2 - 32.0f));
	this->outputText->setPosition(Vec2(0.0f, this->outputScrollView->getInnerContainerSize().height));
}

void CodeEditor::initializeListeners()
{
	this->acceptButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onAccept, this));
	this->cancelButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onCancel, this));
}

void CodeEditor::update(float dt)
{
	std::string currentText = this->assemblyCodeText->getString();

	// Keep the assembly code editor focused. Will need to update this when alloc editor is supported.
	this->assemblyCodeText->attachWithIME();

	// Update compile based on compile delay
	if (this->compileDelay <= CodeEditor::compileDelayMaxSeconds)
	{
		this->compileDelay += dt;

		if (this->compileDelay > CodeEditor::compileDelayMaxSeconds)
		{
			this->compile(currentText);
		}
	}

	if (this->previousAssemblyText != currentText)
	{
		this->previousAssemblyText = currentText;
		this->constructCodeRichText(currentText);

		// Reset compile delay
		this->disableAccept();
		this->compileDelay = 0.0f;
	}
}

void CodeEditor::enableAccept()
{
	this->acceptButtonGrayed->setVisible(false);
	this->acceptButton->setVisible(true);
}

void CodeEditor::disableAccept()
{
	this->acceptButtonGrayed->setVisible(true);
	this->acceptButton->setVisible(false);
}

void CodeEditor::compile(std::string rawText)
{
	if (this->activeHackableCode == nullptr)
	{
		return;
	}

	// Remove existing rich text
	for (auto iterator = this->outputTextElements->begin(); iterator != this->outputTextElements->end(); iterator++)
	{
		this->outputText->removeElement(*iterator);
	}

	this->outputTextElements->clear();

	// Do the actual compile
	HackUtils::CompileResult compileResult = HackUtils::assemble(rawText, this->activeHackableCode->codePointer);

	// Build text and enable/disable the accept button
	if (!compileResult.hasError)
	{
		bool byteOverflow = compileResult.byteCount > this->activeHackableCode->codeOriginalLength;

		RichElementText* statusHeaderLabel = RichElementText::create(0, CodeEditor::headerColor, 0xFF, "Status: ", Resources::Fonts_UbuntuMono_B, 32);
		RichElementText* statusLabel = RichElementText::create(0, CodeEditor::defaultColor, 0xFF, "Compile Successful", Resources::Fonts_UbuntuMono_B, 32);
		RichElementNewLine* newLine1 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementNewLine* newLine2 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementText* addressHeaderLabel = RichElementText::create(0, CodeEditor::headerColor, 0xFF, "Address: ", Resources::Fonts_UbuntuMono_B, 32);
		RichElementText* addressLabel = RichElementText::create(0, CodeEditor::defaultColor, 0xFF, HackUtils::hexAddressOf(this->activeHackableCode->codePointer, true, true), Resources::Fonts_UbuntuMono_B, 32);
		RichElementNewLine* newLine3 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementNewLine* newLine4 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementText* byteCountHeaderLabel = RichElementText::create(0, CodeEditor::headerColor, 0xFF, "Byte Count: ", Resources::Fonts_UbuntuMono_B, 32);
		RichElementText* byteCountLabel = RichElementText::create(0, byteOverflow ? CodeEditor::errorColor : CodeEditor::defaultColor, 0xFF, to_string(compileResult.byteCount) + " / " + to_string(this->activeHackableCode->codeOriginalLength), Resources::Fonts_UbuntuMono_B, 32);
		RichElementNewLine* newLine5 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementNewLine* newLine6 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementText* byteCountaddendum = RichElementText::create(0, byteOverflow ? CodeEditor::errorColor : CodeEditor::subtextColor, 0xFF, byteOverflow ? "Byte overflow! Use allocations to write more assembly." : "Unfilled bytes will be filled with nop (empty) instructions.", Resources::Fonts_UbuntuMono_B, 32);
		RichElementNewLine* newLine7 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementNewLine* newLine8 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementText* bytesHeaderLabel = RichElementText::create(0, CodeEditor::headerColor, 0xFF, "Bytes: ", Resources::Fonts_UbuntuMono_B, 32);
		RichElementText* bytesLabel = RichElementText::create(0, CodeEditor::defaultColor, 0xFF, HackUtils::arrayOfByteStringOf(compileResult.compiledBytes, compileResult.byteCount, compileResult.byteCount), Resources::Fonts_UbuntuMono_B, 32);

		this->outputText->pushBackElement(statusHeaderLabel);
		this->outputText->pushBackElement(statusLabel);
		this->outputText->pushBackElement(newLine1);
		this->outputText->pushBackElement(newLine2);
		this->outputText->pushBackElement(addressHeaderLabel);
		this->outputText->pushBackElement(addressLabel);
		this->outputText->pushBackElement(newLine3);
		this->outputText->pushBackElement(newLine4);
		this->outputText->pushBackElement(byteCountHeaderLabel);
		this->outputText->pushBackElement(byteCountLabel);
		if (compileResult.byteCount != this->activeHackableCode->codeOriginalLength)
		{
			this->outputText->pushBackElement(newLine5);
			this->outputText->pushBackElement(newLine6);
			this->outputText->pushBackElement(byteCountaddendum);
		}
		this->outputText->pushBackElement(newLine7);
		this->outputText->pushBackElement(newLine8);
		this->outputText->pushBackElement(bytesHeaderLabel);
		this->outputText->pushBackElement(bytesLabel);

		this->outputTextElements->push_back(statusHeaderLabel);
		this->outputTextElements->push_back(statusLabel);
		this->outputTextElements->push_back(newLine1);
		this->outputTextElements->push_back(newLine2);
		this->outputTextElements->push_back(addressHeaderLabel);
		this->outputTextElements->push_back(addressLabel);
		this->outputTextElements->push_back(newLine3);
		this->outputTextElements->push_back(newLine4);
		this->outputTextElements->push_back(byteCountHeaderLabel);
		this->outputTextElements->push_back(byteCountLabel);
		if (compileResult.byteCount != this->activeHackableCode->codeOriginalLength)
		{
			this->outputTextElements->push_back(newLine5);
			this->outputTextElements->push_back(newLine6);
			this->outputTextElements->push_back(byteCountaddendum);
		}
		this->outputTextElements->push_back(newLine7);
		this->outputTextElements->push_back(newLine8);
		this->outputTextElements->push_back(bytesHeaderLabel);
		this->outputTextElements->push_back(bytesLabel);

		if (byteOverflow)
		{
			this->disableAccept();
		}
		else
		{
			this->enableAccept();
		}
	}
	else
	{
		RichElementText* statusHeaderLabel = RichElementText::create(0, CodeEditor::headerColor, 0xFF, "Status: ", Resources::Fonts_UbuntuMono_B, 32);
		RichElementText* statusLabel = RichElementText::create(0, CodeEditor::errorColor, 0xFF, "Compile Errors", Resources::Fonts_UbuntuMono_B, 32);
		RichElementNewLine* newLine1 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementNewLine* newLine2 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementText* errorHeaderLabel = RichElementText::create(0, CodeEditor::headerColor, 0xFF, "Error: ", Resources::Fonts_UbuntuMono_B, 32);
		RichElementText* errorLabel = RichElementText::create(0, CodeEditor::defaultColor, 0xFF, compileResult.errorData.message, Resources::Fonts_UbuntuMono_B, 32);
		RichElementNewLine* newLine3 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementNewLine* newLine4 = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
		RichElementText* innerErrorHeaderLabel = RichElementText::create(0, CodeEditor::headerColor, 0xFF, "Line Number: ", Resources::Fonts_UbuntuMono_B, 32);
		RichElementText* innerErrorLabel = RichElementText::create(0, CodeEditor::defaultColor, 0xFF, to_string(compileResult.errorData.lineNumber), Resources::Fonts_UbuntuMono_B, 32);

		this->outputText->pushBackElement(statusHeaderLabel);
		this->outputText->pushBackElement(statusLabel);
		this->outputText->pushBackElement(newLine1);
		this->outputText->pushBackElement(newLine2);
		this->outputText->pushBackElement(errorHeaderLabel);
		this->outputText->pushBackElement(errorLabel);
		this->outputText->pushBackElement(newLine3);
		this->outputText->pushBackElement(newLine4);
		this->outputText->pushBackElement(innerErrorHeaderLabel);
		this->outputText->pushBackElement(innerErrorLabel);

		this->outputTextElements->push_back(statusHeaderLabel);
		this->outputTextElements->push_back(statusLabel);
		this->outputTextElements->push_back(newLine1);
		this->outputTextElements->push_back(newLine2);
		this->outputTextElements->push_back(errorHeaderLabel);
		this->outputTextElements->push_back(errorLabel);
		this->outputTextElements->push_back(newLine3);
		this->outputTextElements->push_back(newLine4);
		this->outputTextElements->push_back(innerErrorHeaderLabel);
		this->outputTextElements->push_back(innerErrorLabel);

		this->disableAccept();
	}

	this->outputText->formatText();
}

void CodeEditor::constructCodeRichText(std::string rawText)
{
	// Remove existing rich text
	for (auto iterator = this->displayTextElements->begin(); iterator != this->displayTextElements->end(); iterator++)
	{
		this->displayText->removeElement(*iterator);
	}

	this->displayTextElements->clear();

	// Tokenize x86/x64 assembly
	std::vector <std::string> * tokenStrings = StrUtils::tokenize(rawText, CodeEditor::delimiters);

	for (auto iterator = tokenStrings->begin(); iterator != tokenStrings->end(); iterator++)
	{
		// Create tokens from the token string (usually this is 1:1, but can sometimes break down further due to edge cases with newlines)
		std::vector<CodeEditor::token>* tokens = this->createTokens(*iterator);

		for (auto tokenIterator = tokens->begin(); tokenIterator != tokens->end(); tokenIterator++)
		{
			CodeEditor::token token = *tokenIterator;

			RichElement* element;

			if (token.tokenStr == "\n")
			{
				// For some reason RichElementText is too fucking stupid to handle newlines -- these are their own object
				element = RichElementNewLine::create(0, CodeEditor::defaultColor, 0xFF);
			}
			else
			{
				element = RichElementText::create(0, token.color, 0xFF, token.tokenStr, Resources::Fonts_UbuntuMono_B, 32);
			}

			this->displayTextElements->push_back(element);
			this->displayText->pushBackElement(element);
		}

		delete(tokens);
	}

	delete(tokenStrings);

	this->displayText->formatText();
}

std::vector<CodeEditor::token>* CodeEditor::createTokens(std::string tokenStr)
{
	std::vector<CodeEditor::token>* tokens = new std::vector<CodeEditor::token>();
	std::vector <std::string> * tokenStrings = StrUtils::splitOn(tokenStr, "\n");

	for (auto tokenIterator = tokenStrings->begin(); tokenIterator != tokenStrings->end(); tokenIterator++)
	{
		std::string innerToken = *tokenIterator;
		Color3B color = CodeEditor::defaultColor;

		if (CodeEditor::registers.find(innerToken) != CodeEditor::registers.end())
		{
			color = CodeEditor::registerColor;
		}
		else if (StrUtils::isInteger(innerToken) || StrUtils::isFloat(innerToken) || StrUtils::isHexNumber(innerToken))
		{
			color = CodeEditor::numberColor;
		}

		CodeEditor::token nextToken = CodeEditor::token(innerToken, color);
		tokens->push_back(nextToken);
	}

	delete(tokenStrings);

	return tokens;
}

void CodeEditor::open(HackableCode* hackableCode)
{
	this->activeHackableCode = hackableCode;

	this->codeEditorTitle->setText("Function '" + hackableCode->functionName + "'");

	this->assemblyCodeText->setText(HackUtils::disassemble(hackableCode->codePointer, hackableCode->codeOriginalLength).c_str());
	this->assemblyCodeText->attachWithIME();

	this->setVisible(true);
	Utils::focus(this);
}

void CodeEditor::onAccept(MenuSprite* menuSprite)
{
	this->setVisible(false);

	this->getParent()->setOpacity(0xFF);
	Utils::focus(this->getParent());
}

void CodeEditor::onCancel(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
