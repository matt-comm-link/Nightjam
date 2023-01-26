#pragma once

#ifndef DEFEDITOR
#define DEFEDITOR "EDITOR"


#include "GameConstructs.h"
#include "Loader.h"
#include "Environment.h"
#include "mesh.h"
#include "RenderHelpers.h"

class LevelEdit
{
public:
	Environment environment;
	SceneData Scene;
	UIData SceneUI;
	std::string sceneName;

	void EditLevel(Environment e, std::string sn)
	{
		environment = e;
		sceneName = sn;
		std::string sceneload = "";
		bool copied = false;
		for (uint i = 0; i <environment.sceneNames.size(); i++)
		{
			if (environment.sceneNames[i] == sceneName)
			{
				sceneload = environment.scenes[i].Pack();
			}
		}
		if (sceneload.size() > 0)
			Scene = SceneData(sceneload);

		for (uint i = 0; i < environment.sceneNames.size(); i++)
		{
			if (environment.sceneNames[i] == sceneName)
			{
				sceneload = environment.UIs[i].Pack();
			}
		}
		if (sceneload.size() > 0)
			SceneUI = UIData(sceneload);


	}

};
#endif // !DEFEDITOR

