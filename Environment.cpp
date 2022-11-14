#pragma once
#include "Environment.h"


inline Mesh& GetMesh(string n)
{
	int index = 0;
	for (uint i = 0; i < meshname.size(); i++)
	{
		if (meshname[i] == n)
		{
			index = i;
			break;
		}
	}
	//returns default if not present
	return meshes[index];

}

inline shader& GetShader(string n)
{
	int index = 0;
	for (uint i = 0; i < shaderNames.size(); i++)
	{
		if (shaderNames[i] == n)
		{
			index = i;
			break;
		}
	}
	//returns default if not present
	return shaders[index];

}

inline map<char, Character>& GetFont(string n)
{
	int index = 0;
	for (uint i = 0; i < fontnames.size(); i++)
	{
		if (fontnames[i] == n)
		{
			index = i;
			break;
		}
	}
	//returns default if not present
	return fonts[index];

}