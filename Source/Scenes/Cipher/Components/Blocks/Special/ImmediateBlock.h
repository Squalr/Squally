#pragma once

#include "Events/CipherEvents.h"
#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ConstantString;
class LocalizedLabel;

class ImmediateBlock : public BlockBase
{
public:
	static ImmediateBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	ImmediateBlock(BlockType blockType);
	~ImmediateBlock();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadDisplayValue();

	char charValue;
	CipherEvents::DisplayDataType displayDataType;

	ConstantString* displayValue;
	LocalizedLabel* displayLabel;

	cocos2d::Sprite* spriteAscii;
	cocos2d::Sprite* spriteBin;
	cocos2d::Sprite* spriteDec;
	cocos2d::Sprite* spriteHex;
	cocos2d::Sprite* spriteAsciiSelected;
	cocos2d::Sprite* spriteBinSelected;
	cocos2d::Sprite* spriteDecSelected;
	cocos2d::Sprite* spriteHexSelected;
};
