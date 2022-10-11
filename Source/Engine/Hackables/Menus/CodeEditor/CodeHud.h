#pragma once
#include <set>
#include <string>
#include <vector>

#include "Engine/GlobalHud.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class CodeWindow;
class ConfirmationMenu;
class HackableCode;
class LabelStack;
template <class T> class LazyNode;
class Lexicon;
class LocalizedLabel;
class ScriptList;

struct AsmToken;

struct HackableObjectEditArgs;

class CodeHud : public GlobalHud
{
public:
	static CodeHud* create();
	
protected:
	CodeHud();
	virtual ~CodeHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;

private:
	typedef SmartNode super;

	void open(HackableObjectEditArgs* args);
	void close();
	void enableAccept();
	void disableAccept();
	void buildRegisterWindow();
	void compile(std::string rawText);
	void tokenizeCallback(std::string text, std::vector<AsmToken>&);
	void onAccept();
	void onCancel();
	void setWindowColor(cocos2d::Color4B windowColor);
	void setTitleBarColor(cocos2d::Color4B titleBarColor);
	Lexicon* buildLexicon();

	// This is an unused label that is simply kept around to steal attributes from (font size, font style, etc)
	LocalizedLabel* referenceContentLabel = nullptr;

	float marginSize = 0.0f;

	cocos2d::Sprite* statusBackground = nullptr;
	cocos2d::Sprite* rightBarBackground = nullptr;
	cocos2d::Sprite* radialEye = nullptr;
	cocos2d::Node* previewNode = nullptr;
	cocos2d::Node* clippyNode = nullptr;
	CodeWindow* functionWindow = nullptr;
	LabelStack* statusWindow = nullptr;
	LabelStack* registerWindow = nullptr;
	ScriptList* scriptList = nullptr;
	ClickableTextNode* cancelButton = nullptr;
	ClickableTextNode* applyChangesButton = nullptr;
	cocos2d::Node* applyChangesButtonGrayed = nullptr;
	LocalizedLabel* titleLabel = nullptr;
	ClickableTextNode* stuckButton = nullptr;
	ClickableTextNode* lexiconButton = nullptr;
	LazyNode<Lexicon>* lexicon = nullptr;
	ConfirmationMenu* confirmationMenu = nullptr;

	HackableCode* activeHackableCode = nullptr;
	float timeSinceLastCompile = 0.0f;

	static const cocos2d::CSize Padding;
	static const float CompileDelayMaxSeconds;
	static const float LineNumberMargin;
	static const cocos2d::CSize StatusSize;
	static const cocos2d::CSize FunctionSize;
	static const cocos2d::Color4B SubtextColor;
	static const cocos2d::Color4B HeaderColor;
	static const cocos2d::Color4B ErrorColor;
	static const cocos2d::Color4B RegisterColor;
};
