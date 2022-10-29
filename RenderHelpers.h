#pragma once

#include "Environment.h"

void DrawMesh(Bounds b)
{
	int index = 0;
	for (uint i = 0; i < meshname.size(); i++)
	{
		if (meshname[i] == b.model)
		{
			index = i;
			break;
		}
	}
	int sindex = 0;
	for (uint i = 0; i < shaderNames.size(); i++)
	{
		if (shaderNames[i] == b.shader)
		{
			sindex = i;
			break;
		}
	}
	//returns default if not present
	meshes[index].Draw(shaders[sindex], b.centre, b.modelRot, globalProjection, globalView);

}

void DrawMesh(EnemyData e, glm::vec3 p)
{
	int index = 0;
	for (uint i = 0; i < meshname.size(); i++)
	{
		if (meshname[i] == e.name)
		{
			index = i;
			break;
		}
	}
	int sindex = 0;
	for (uint i = 0; i < shaderNames.size(); i++)
	{
		if (shaderNames[i] == e.shader)
		{
			sindex = i;
			break;
		}
	}
	//returns default if not present
	meshes[index].Draw(shaders[sindex], p, glm::half_pi<float>(), globalProjection, globalView);

}

void DrawText(string text, string font, glm::vec3 loc, glm::vec3 scale, glm::vec4 color)
{
	FontMesh.DrawFont(text, GetFont(font), FontShader, UIOrtho, globalView, loc, scale, color);
}



void DrawBattle()
{
}