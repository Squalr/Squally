#pragma once

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

	ConstantString* displayValue;
	LocalizedLabel* displayLabel;
};
