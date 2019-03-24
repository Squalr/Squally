#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class LessThanOrEqualsBlock : public BlockBase
{
public:
	static LessThanOrEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	LessThanOrEqualsBlock(BlockType blockType);
	~LessThanOrEqualsBlock();

	void onEnter() override;
	void initializePositions() override;
};
