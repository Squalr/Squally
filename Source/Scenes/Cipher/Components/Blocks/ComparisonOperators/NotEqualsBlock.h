#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class NotEqualsBlock : public ComparisonBlockBase
{
public:
	static NotEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;
	bool compare(char inputA, char inputB) override;

private:
	typedef ComparisonBlockBase super;
	NotEqualsBlock(BlockType blockType);
	~NotEqualsBlock();
};
