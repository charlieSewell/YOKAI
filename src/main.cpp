#include "Controller/Yokai.hpp"
int main()
{
	auto& engine = Yokai::getInstance();
	engine.Init();
    engine.Run();
	return 0;
}
