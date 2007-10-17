//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("test.res");
USEFORM("MainTest.cpp", Form1);
USELIB("sword.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
