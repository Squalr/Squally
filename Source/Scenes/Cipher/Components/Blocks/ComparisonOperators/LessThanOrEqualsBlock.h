#pragma once

#include "Scenes/Cipher/Components/Blocks/ComparisonOperators/ComparisonBlockBase.h"

class LessThanOrEqualsBlock : public ComparisonBlockBase
{
public:
	static LessThanOrEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;
	BlockBase* spawn() override;
	bool compare(unsigned char inputA, unsigned char inputB) override;

private:
	typedef ComparisonBlockBase super;
	LessThanOrEqualsBlock(BlockType blockType);
	~LessThanOrEqualsBlock();
};
