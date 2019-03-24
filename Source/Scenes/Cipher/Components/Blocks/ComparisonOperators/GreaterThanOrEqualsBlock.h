#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class GreaterThanOrEqualsBlock : public ComparisonBlockBase
{
public:
	static GreaterThanOrEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;
	bool compare(char inputA, char inputB) override;

private:
	typedef ComparisonBlockBase super;
	GreaterThanOrEqualsBlock(BlockType blockType);
	~GreaterThanOrEqualsBlock();
};
