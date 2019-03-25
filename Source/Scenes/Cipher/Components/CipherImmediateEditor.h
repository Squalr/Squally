#pragma once
#include <functional>

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class ImmediateBlock;
class InputText;
class LocalizedLabel;
class RadioButton;

class CipherImmediateEditor : public CipherComponentBase
{
public:
	static CipherImmediateEditor* create();

	void open(ImmediateBlock* immediateBlock, std::function<void()> onCloseCallback);
	
protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	CipherImmediateEditor();
	~CipherImmediateEditor();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void close();

	cocos2d::Sprite* background;
	RadioButton* toggleButtonBin;
	RadioButton* toggleButtonDec;
	RadioButton* toggleButtonHex;
	RadioButton* toggleButtonAscii;
	ImmediateBlock* previewImmediate;
	cocos2d::Sprite* inputFrame;
	InputText* inputText;
	cocos2d::Sprite* frame;
	LocalizedLabel* enterAValueLabel;
	LocalizedLabel* immediateEditorLabel;
	ClickableTextNode* acceptButton;

	ImmediateBlock* immediateBlock;
	std::function<void()> onCloseCallback;

	static const int GroupIdCipherImmediateEditor;
};
