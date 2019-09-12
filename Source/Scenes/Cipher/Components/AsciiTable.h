#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class DisplayModeToggles;
class ImmediateBlock;
class LocalizedLabel;
class RadioButton;
class ScrollPane;
class SmartAsciiLabel;

class AsciiTable : public CipherComponentBase
{
public:
	static AsciiTable* create();

	void open(ImmediateBlock* immediateBlock, std::function<void()> onCloseCallback);

protected:
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	AsciiTable();
	~AsciiTable();

	std::vector<ImmediateBlock*> asciiLetters;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void select(ImmediateBlock* block);
	void close();

	cocos2d::Sprite* background;
	ScrollPane* scrollPane;
	cocos2d::Sprite* selectionSprite;
	DisplayModeToggles* displayModeToggles;
	cocos2d::Sprite* frame;
	ClickableTextNode* returnButton;
	LocalizedLabel* asciiTableTitle;
	LocalizedLabel* chooseANewValueTitle;

	ImmediateBlock* selectedBlock;
	ImmediateBlock* immediateBlock;
	std::function<void()> onCloseCallback;
};
