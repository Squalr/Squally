#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class ConstantString;

class RegisterBlock : public SmartNode
{
public:
	static RegisterBlock* create();

	void initEax(unsigned long eax, std::vector<unsigned long> values = { });
	void initEbx(unsigned long ebx, std::vector<unsigned long> values = { });
	void initEcx(unsigned long ecx, std::vector<unsigned long> values = { });
	void initEdx(unsigned long edx, std::vector<unsigned long> values = { });
	void initEdi(unsigned long edi, std::vector<unsigned long> values = { });
	void initEsi(unsigned long esi, std::vector<unsigned long> values = { });
	void initEbp(unsigned long ebp, std::vector<unsigned long> values = { });
	void initEsp(unsigned long esp, std::vector<unsigned long> values = { });
	void initEip(unsigned long eip, std::vector<unsigned long> values = { });

	void setEax(unsigned long eax);
	void setEbx(unsigned long ebx);
	void setEcx(unsigned long ecx);
	void setEdx(unsigned long edx);
	void setEdi(unsigned long edi);
	void setEsi(unsigned long esi);
	void setEbp(unsigned long ebp);
	void setEsp(unsigned long esp);
	void setEip(unsigned long eip);

	void setEaxPtr(unsigned long value, int offset);
	void setEbxPtr(unsigned long value, int offset);
	void setEcxPtr(unsigned long value, int offset);
	void setEdxPtr(unsigned long value, int offset);
	void setEdiPtr(unsigned long value, int offset);
	void setEsiPtr(unsigned long value, int offset);
	void setEbpPtr(unsigned long value, int offset);
	void setEspPtr(unsigned long value, int offset);
	void setEipPtr(unsigned long value, int offset);

	unsigned long getEax();
	unsigned long getEbx();
	unsigned long getEcx();
	unsigned long getEdx();
	unsigned long getEdi();
	unsigned long getEsi();
	unsigned long getEbp();
	unsigned long getEsp();
	unsigned long getEip();

	unsigned long getEaxPtr(int offset);
	unsigned long getEbxPtr(int offset);
	unsigned long getEcxPtr(int offset);
	unsigned long getEdxPtr(int offset);
	unsigned long getEdiPtr(int offset);
	unsigned long getEsiPtr(int offset);
	unsigned long getEbpPtr(int offset);
	unsigned long getEspPtr(int offset);
	unsigned long getEipPtr(int offset);

protected:
	RegisterBlock();
	~RegisterBlock();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	struct Register
	{
		bool initialized;
		unsigned long currentValue;
		unsigned long initialValue;
		std::vector<unsigned long> initialValues;
		std::vector<unsigned long> currentValues;

		Register() : initialized(false), currentValue(0), initialValue(0), initialValues({}), currentValues({}) { }
		Register(unsigned long currentValue, unsigned long initialValue, std::vector<unsigned long> initialValues, std::vector<unsigned long> currentValues) :
			initialized(true), currentValue(currentValue), initialValue(initialValue), initialValues(initialValues), currentValues(currentValues) {}
	};

	cocos2d::Sprite* registerBlock;
	LocalizedLabel* titleLabel;
	LocalizedLabel* eaxLabel;
	LocalizedLabel* ebxLabel;
	LocalizedLabel* ecxLabel;
	LocalizedLabel* edxLabel;
	LocalizedLabel* ediLabel;
	LocalizedLabel* esiLabel;
	LocalizedLabel* ebpLabel;
	LocalizedLabel* espLabel;
	LocalizedLabel* eipLabel;
	cocos2d::Node* eaxPtrNode;
	cocos2d::Node* ebxPtrNode;
	cocos2d::Node* ecxPtrNode;
	cocos2d::Node* edxPtrNode;
	cocos2d::Node* ediPtrNode;
	cocos2d::Node* esiPtrNode;
	cocos2d::Node* ebpPtrNode;
	cocos2d::Node* espPtrNode;
	cocos2d::Node* eipPtrNode;

	std::vector<ConstantString*> eaxPtrStrings;
	std::vector<ConstantString*> ebxPtrStrings;
	std::vector<ConstantString*> ecxPtrStrings;
	std::vector<ConstantString*> edxPtrStrings;
	std::vector<ConstantString*> ediPtrStrings;
	std::vector<ConstantString*> esiPtrStrings;
	std::vector<ConstantString*> ebpPtrStrings;
	std::vector<ConstantString*> espPtrStrings;
	std::vector<ConstantString*> eipPtrStrings;

	std::vector<LocalizedLabel*> eaxPtrLabels;
	std::vector<LocalizedLabel*> ebxPtrLabels;
	std::vector<LocalizedLabel*> ecxPtrLabels;
	std::vector<LocalizedLabel*> edxPtrLabels;
	std::vector<LocalizedLabel*> ediPtrLabels;
	std::vector<LocalizedLabel*> esiPtrLabels;
	std::vector<LocalizedLabel*> ebpPtrLabels;
	std::vector<LocalizedLabel*> espPtrLabels;
	std::vector<LocalizedLabel*> eipPtrLabels;

	ConstantString* eaxString;
	ConstantString* ebxString;
	ConstantString* ecxString;
	ConstantString* edxString;
	ConstantString* ediString;
	ConstantString* esiString;
	ConstantString* ebpString;
	ConstantString* espString;
	ConstantString* eipString;

	Register eax;
	Register ebx;
	Register ecx;
	Register edx;
	Register edi;
	Register esi;
	Register ebp;
	Register esp;
	Register eip;

	static const float RegisterPtrSpacing;
};
