#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class LessThanOrEqualsBlock : public ComparisonBlockBase
{
public:
	static LessThanOrEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;
	bool compare(char inputA, char inputB) override;

private:
	typedef ComparisonBlockBase super;
	LessThanOrEqualsBlock(BlockType blockType);
	~LessThanOrEqualsBlock();
};
