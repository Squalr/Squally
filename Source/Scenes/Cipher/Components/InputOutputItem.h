#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class CipherState;
class ClickableNode;
class SmartAsciiLabel;

class InputOutputItem : public CipherComponentBase
{
public:
	static InputOutputItem* create(unsigned char input, unsigned char output, std::function<void(InputOutputItem*)> selectCallback);

	void enableInteraction();
	void disableInteraction();
	void setStatusPassed();
	void setStatusFailed();
	void clearStatus();

protected:
	InputOutputItem(unsigned char input, unsigned char output, std::function<void(InputOutputItem*)> selectCallback);
	~InputOutputItem();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;

	ClickableNode* panel;
	SmartAsciiLabel* inputLabel;
	SmartAsciiLabel* outputLabel;
	cocos2d::Sprite* failedIcon;
	cocos2d::Sprite* passedIcon;

	unsigned char input;
	unsigned char output;
	std::function<void(InputOutputItem*)> selectCallback;
};
