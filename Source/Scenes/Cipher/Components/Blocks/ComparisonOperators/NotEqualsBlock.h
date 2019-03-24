#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class NotEqualsBlock : public BlockBase
{
public:
	static NotEqualsBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	NotEqualsBlock(BlockType blockType);
	~NotEqualsBlock();

	void onEnter() override;
	void initializePositions() override;
};
