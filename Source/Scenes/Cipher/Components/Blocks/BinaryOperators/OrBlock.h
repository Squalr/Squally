#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class OrBlock : public BlockBase
{
public:
	static OrBlock* create(BlockType blockType = BlockType::Normal);
	
protected:
	OrBlock(BlockType blockType);
	virtual ~OrBlock();

	void onEnter() override;
	void initializePositions() override;
	unsigned char compute() override;

private:
	typedef BlockBase super;
};
