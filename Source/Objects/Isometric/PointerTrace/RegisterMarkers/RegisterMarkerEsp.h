#pragma once

#include "Objects/Isometric/PointerTrace/RegisterMarkers/RegisterMarker.h"

class RegisterMarkerEsp : public RegisterMarker
{
public:
	static RegisterMarkerEsp* create();

protected:
	RegisterMarkerEsp();
	virtual ~RegisterMarkerEsp();

	int getRegisterIndex() override;

private:
	typedef RegisterMarker super;
};
