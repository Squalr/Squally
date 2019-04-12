#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class AndBlock : public BlockBase
{
public:
	static AndBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	unsigned char compute() override;
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	AndBlock(BlockType blockType);
	~AndBlock();

	void onEnter() override;
	void initializePositions() override;
};
