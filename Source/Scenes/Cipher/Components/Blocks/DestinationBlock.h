#pragma once

#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ConstantString;
class LocalizedLabel;

class DestinationBlock : public BlockBase
{
public:
	static DestinationBlock* create(int cipherIndex);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	DestinationBlock(int cipherIndex);
	~DestinationBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadDisplayValue();

	ConstantString* displayValue;
	LocalizedLabel* displayLabel;

	int cipherIndex;
	char charValue;
	CipherEvents::DisplayDataType displayDataType;

	cocos2d::Sprite* spriteAscii;
	cocos2d::Sprite* spriteBin;
	cocos2d::Sprite* spriteDec;
	cocos2d::Sprite* spriteHex;
};
