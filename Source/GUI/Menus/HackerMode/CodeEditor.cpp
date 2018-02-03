#include "CodeEditor.h"

const float CodeEditor::compileDelayMaxSeconds = 0.1f;
const float CodeEditor::lineNumberMargin = 32.0f;;
const Size CodeEditor::textSize = Size(512.0f, 640.0f);
const Size CodeEditor::statusSize = Size(512.0f, 640.0f);
const Size CodeEditor::functionSize = Size(512.0f, 640.0f);
const Size CodeEditor::secondarySize = Size(512.0f, 640.0f);
const std::string CodeEditor::delimiters = "[],:; \n\t";
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

	this->codeEditorBackground = Sprite::create(Resources::Menus_HackerModeMenu_EmptyFullScreenMenu);
	this->codeEditorTitle = MenuLabel::create("Script Editor", Resources::Fonts_Montserrat_Medium, 32);

	this->statusWindow = TextWindow::create("Status", CodeEditor::statusSize, 32, CodeEditor::defaultColor);
	this->functionWindow = EditableTextWindow::create("Code Editor", CodeEditor::functionSize, 32, CodeEditor::defaultColor);
	this->secondaryWindow = EditableTextWindow::create("Allocation Editor", CodeEditor::secondarySize, 32, CodeEditor::defaultColor);
	this->cancelButton = MenuSprite::create(Resources::Menus_HackerModeMenu_TrashButton, Resources::Menus_HackerModeMenu_TrashButtonHover, Resources::Menus_HackerModeMenu_TrashButtonClick);
	this->acceptButton = MenuSprite::create(Resources::Menus_HackerModeMenu_PlayButton, Resources::Menus_HackerModeMenu_PlayButtonHover, Resources::Menus_HackerModeMenu_PlayButtonClick);
	this->acceptButtonGrayed = Sprite::create(Resources::Menus_HackerModeMenu_PlayButtonGray);

	this->functionWindow->setTokenizationCallback(CC_CALLBACK_2(CodeEditor::tokenizeCallback, this));
	this->secondaryWindow->setTokenizationCallback(CC_CALLBACK_2(CodeEditor::tokenizeCallback, this));
	this->functionWindow->setOnEditCallback(CC_CALLBACK_1(CodeEditor::compile, this));
	this->secondaryWindow->setOnEditCallback(CC_CALLBACK_1(CodeEditor::compile, this));
	this->functionWindow->setMarginSize(32.0f);
	this->secondaryWindow->setMarginSize(32.0f);

	this->addChild(this->codeEditorBackground);
	this->addChild(this->codeEditorTitle);
	this->addChild(this->statusWindow);
	this->addChild(this->functionWindow);
	this->addChild(this->secondaryWindow);
	this->addChild(this->cancelButton);
	this->addChild(this->acceptButton);
	this->addChild(this->acceptButtonGrayed);

	this->initializePositions();
	this->initializeListeners();
	this->scheduleUpdate();
}

CodeEditor::~CodeEditor()
{
}

void CodeEditor::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeEditorBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->codeEditorTitle->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 444.0f));
	this->acceptButton->setPosition(Vec2(visibleSize.width / 2.0f + 224.0f, visibleSize.height / 2.0f + 348.0f));
	this->cancelButton->setPosition(Vec2(visibleSize.width / 2.0f - 224.0f, visibleSize.height / 2.0f + 348.0f));
	this->acceptButtonGrayed->setPosition(this->acceptButton->getPosition());

	this->statusWindow->setPosition(Vec2(visibleSize.width / 2.0f - 560.0f, visibleSize.height / 2.0f - 64.0f));
	this->functionWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 64.0f));
	this->secondaryWindow->setPosition(Vec2(visibleSize.width / 2.0f + 560.0f, visibleSize.height / 2.0f - 64.0f));
}

void CodeEditor::initializeListeners()
{
	this->acceptButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onAccept, this));
	this->cancelButton->setClickCallback(CC_CALLBACK_1(CodeEditor::onCancel, this));
}

void CodeEditor::onFunctionTextUpdate(std::string text)
{
	// Reset compile delay
	this->disableAccept();
	this->compileDelay = 0.0f;
}

void CodeEditor::onAllocationTextUpdate(std::string text)
{
	// Reset compile delay
	this->disableAccept();
	this->compileDelay = 0.0f;
}

void CodeEditor::update(float dt)
{
	// Update compile based on compile delay
	if (this->compileDelay <= CodeEditor::compileDelayMaxSeconds)
	{
		this->compileDelay += dt;

		if (this->compileDelay > CodeEditor::compileDelayMaxSeconds)
		{
			this->compile(this->functionWindow->getText());
		}
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

void CodeEditor::compile(std::string assemblyText)
{
	if (this->activeHackableCode == nullptr)
	{
		return;
	}

	this->statusWindow->clearText();

	// Do the actual compile
	HackUtils::CompileResult compileResult = HackUtils::assemble(assemblyText, this->activeHackableCode->codePointer);

	// Build text and enable/disable the accept button
	if (!compileResult.hasError)
	{
		bool byteOverflow = compileResult.byteCount > this->activeHackableCode->codeOriginalLength;

		this->statusWindow->insertText("Status:", CodeEditor::headerColor);
		this->statusWindow->insertText("Compile Successful", CodeEditor::defaultColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		this->statusWindow->insertText("Address:", CodeEditor::headerColor);
		this->statusWindow->insertText(HackUtils::hexAddressOf(this->activeHackableCode->codePointer, true, true), CodeEditor::defaultColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		this->statusWindow->insertText("Byte Count:", CodeEditor::headerColor);
		this->statusWindow->insertText(to_string(compileResult.byteCount) + " / " + to_string(this->activeHackableCode->codeOriginalLength), byteOverflow ? CodeEditor::errorColor : CodeEditor::defaultColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		if (compileResult.byteCount != this->activeHackableCode->codeOriginalLength)
		{
			this->statusWindow->insertText(byteOverflow ? "Byte overflow! Use allocations to write more assembly." : "Unfilled bytes will be filled with nop (empty) instructions.", byteOverflow ? CodeEditor::errorColor : CodeEditor::subtextColor);
			this->statusWindow->insertNewline();
			this->statusWindow->insertNewline();
		}
		this->statusWindow->insertText("Bytes:", CodeEditor::headerColor);
		this->statusWindow->insertText(HackUtils::arrayOfByteStringOf(compileResult.compiledBytes, compileResult.byteCount, compileResult.byteCount), CodeEditor::defaultColor);

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
		this->statusWindow->insertText("Status:", CodeEditor::headerColor);
		this->statusWindow->insertText("Compile Errors", CodeEditor::errorColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		this->statusWindow->insertText("Error:", CodeEditor::headerColor);
		this->statusWindow->insertText(compileResult.errorData.message, CodeEditor::defaultColor);
		this->statusWindow->insertNewline();
		this->statusWindow->insertNewline();
		this->statusWindow->insertText("Line Number:", CodeEditor::headerColor);
		this->statusWindow->insertText(to_string(compileResult.errorData.lineNumber), CodeEditor::defaultColor);

		this->disableAccept();
	}
}

void CodeEditor::tokenizeCallback(std::string text, std::vector<EditableTextWindow::token>* tokens)
{
	std::vector<std::string>* tokenStrings = StrUtils::tokenize(text, CodeEditor::delimiters);

	for (auto iterator = tokenStrings->begin(); iterator != tokenStrings->end(); iterator++)
	{
		std::string tokenString = *iterator;

		// Due to RichTextBoxes being garbage, we need to split tokens down further if they contain newlines
		std::vector <std::string> * tokenStrings = StrUtils::splitOn(tokenString, "\n");

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

			EditableTextWindow::token nextToken = EditableTextWindow::token(innerToken, color);
			tokens->push_back(nextToken);
		}
	}

	delete(tokenStrings);
}

void CodeEditor::open(HackableCode* hackableCode)
{
	this->activeHackableCode = hackableCode;

	this->functionWindow->setTitle("Function '" + hackableCode->functionName + "'");
	this->functionWindow->setText(HackUtils::disassemble(hackableCode->codePointer, hackableCode->codeOriginalLength).c_str());
	this->functionWindow->focus();

	this->setVisible(true);
	Utils::focus(this);
}

void CodeEditor::onAccept(MenuSprite* menuSprite)
{
	HackUtils::CompileResult compileResult = HackUtils::assemble(this->functionWindow->getText(), this->activeHackableCode->codePointer);

	// Sanity check that the code compiles -- it should at this point
	if (compileResult.hasError || compileResult.byteCount > this->activeHackableCode->codeOriginalLength)
	{
		this->disableAccept();
		return;
	}

	int unfilledBytes = this->activeHackableCode->codeOriginalLength - compileResult.byteCount;

	memcpy(this->activeHackableCode->codePointer, compileResult.compiledBytes, compileResult.byteCount);

	for (int index = 0; index < unfilledBytes; index++)
	{
		const byte nop = 0x90;
		((byte*)this->activeHackableCode->codePointer)[compileResult.byteCount + index] = nop;
	}

	this->setVisible(false);

	this->getParent()->setOpacity(0xFF);
	Utils::focus(this->getParent());
}

void CodeEditor::onCancel(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
