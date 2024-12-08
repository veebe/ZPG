/* Vratislav Blunar - BLU0015 */
#include "Application.h"

int main(void)
{
	Application& app = Application::getInstance();
	app.Initialization();
	app.CreateModels();
	app.Run();
}