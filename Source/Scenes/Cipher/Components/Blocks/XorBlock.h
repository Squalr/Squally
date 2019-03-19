#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class XorBlock : public BlockBase
{
public:
	static XorBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	XorBlock(bool isToolBoxItem);
	~XorBlock();

	void onEnter() override;
	void initializePositions() override;
};
