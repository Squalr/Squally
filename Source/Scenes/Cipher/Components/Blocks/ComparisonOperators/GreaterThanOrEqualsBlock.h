#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class GreaterThanOrEqualsBlock : public ComparisonBlockBase
{
public:
	static GreaterThanOrEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;
	bool compare(unsigned char inputA, unsigned char inputB) override;

private:
	typedef ComparisonBlockBase super;
	GreaterThanOrEqualsBlock(BlockType blockType);
	~GreaterThanOrEqualsBlock();
};
