#ifndef NDEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#include <cstdlib>
#endif

#include <StarletEngine/engine.hpp>

int main() {
#ifndef NDEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc();
#endif
	
	Engine engine;
	engine.assetPath = std::string(ASSET_DIR);

	if (!engine.initialize(1920, 1080, "Test")) 
		return -1;

	/* Current Scene(s)
		- Default
		- EmptyScene
		- GridScene
		- PrimitiveScene
		- TestScene
	*/
	if (!engine.loadScene("TestScene"))          
		return -1;
	
	engine.run();
}
