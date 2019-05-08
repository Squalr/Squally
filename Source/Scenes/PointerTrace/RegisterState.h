#pragma once

class RegisterState
{
public:
	static int getRegisterEax();
	static void setRegisterEax(int value);
	static int getRegisterEbx();
	static void setRegisterEbx(int value);
	static int getRegisterEcx();
	static void setRegisterEcx(int value);
	static int getRegisterEdx();
	static void setRegisterEdx(int value);
	static int getRegisterEdi();
	static void setRegisterEdi(int value);
	static int getRegisterEsi();
	static void setRegisterEsi(int value);
	static int getRegisterEbp();
	static void setRegisterEbp(int value);
	static int getRegisterEsp();
	static void setRegisterEsp(int value);
	static int getRegisterEip();
	static void setRegisterEip(int value);
	static void setRegisterMax(int registerMax);

private:
	static int RegisterEax;
	static int RegisterEbx;
	static int RegisterEcx;
	static int RegisterEdx;
	static int RegisterEdi;
	static int RegisterEsi;
	static int RegisterEbp;
	static int RegisterEsp;
	static int RegisterEip;
	static int RegisterMax;
};
