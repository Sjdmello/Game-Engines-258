#include "CoreEngine.h"



int main(int argc, char* argv[]) {
	
	if (!CoreEngine::GetInstance()->OnCreate("Game Engines 4", 800, 600)) {
		std::cout << "failed to create engine" << std::endl;
		return 0;
	}
	CoreEngine::GetInstance()->Run();
	return 0;
	
}