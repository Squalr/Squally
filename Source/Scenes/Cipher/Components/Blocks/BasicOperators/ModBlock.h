#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ModBlock : public BlockBase
{
public:
	static ModBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	ModBlock(BlockType blockType);
	virtual ~ModBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
