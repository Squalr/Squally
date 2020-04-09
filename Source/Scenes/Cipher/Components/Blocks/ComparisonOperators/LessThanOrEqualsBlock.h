#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class LessThanOrEqualsBlock : public ComparisonBlockBase
{
public:
	static LessThanOrEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	LessThanOrEqualsBlock(BlockType blockType);
	virtual ~LessThanOrEqualsBlock();
	unsigned char compute() override;
	bool compare(unsigned char inputA, unsigned char inputB) override;

private:
	typedef ComparisonBlockBase super;
};
