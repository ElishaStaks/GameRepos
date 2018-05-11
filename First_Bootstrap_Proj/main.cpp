#include "First_Bootstrap_ProjApp.h"
#include <iostream>
#include <exception>

int main() {

	// Log memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// allocation
	auto app = new First_Bootstrap_ProjApp();
	
	try {
		// initialise and loop
		app->run("AIE", 1920, 1080, false);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	
	//deallocation
	delete app;

	return 0;
}