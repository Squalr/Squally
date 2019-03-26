#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class ImmediateBlock;
class RadioButton;
class ScrollPane;
class SmartAsciiLabel;

class AsciiTable : public CipherComponentBase
{
public:
	static AsciiTable* create();

	void open(ImmediateBlock* immediateBlock, std::function<void()> onCloseCallback);

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	AsciiTable();
	~AsciiTable();

	std::vector<SmartAsciiLabel*> asciiLetters;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void close();

	cocos2d::Sprite* background;
	ScrollPane* scrollPane;
	RadioButton* toggleButtonBin;
	RadioButton* toggleButtonDec;
	RadioButton* toggleButtonHex;
	RadioButton* toggleButtonAscii;
	cocos2d::Sprite* frame;
	ClickableTextNode* returnButton;

	ImmediateBlock* immediateBlock;
	std::function<void()> onCloseCallback;

	static const int GroupIdAsciiTable;
};
