#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class AndBlock : public BlockBase
{
public:
	static AndBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	AndBlock(BlockType blockType);
	virtual ~AndBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
