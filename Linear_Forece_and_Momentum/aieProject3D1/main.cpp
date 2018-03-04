#include "aieProject3D1App.h"
#include <crtdbg.h>

//----------------------------------------------------------------------------------------------
// main funtion that runs the application
//
//	Return:
//		Returns 0 when we close the application
//----------------------------------------------------------------------------------------------
int main() {
	
	// detects memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// allocation
	auto app = new aieProject3D1App();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}