﻿

#include "Application.h"



int main(void)
{

	Application* app = new Application();

	app->Initialization();
	app->CreateModels();
	app->Run();
}