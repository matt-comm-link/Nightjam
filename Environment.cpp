#include "Environment.h"




Texture& Environment::GetTexture(string n)
{
	int index = 0;
	for (uint i = 0; i < texname.size(); i++)
	{
		if (texname[i] == n)
		{
			index = i;
			break;
		}
	}
	//returns default if not present
	return textures[index];


}

Texture& Environment::GetTextureInstance(string n)
{
	int index = 0;
	for (uint i = 0; i < texname.size(); i++)
	{
		if (texname[i] == n)
		{
			index = i;
			break;
		}
	}
	//returns default if not present
	Texture t = Texture(textures[index].path, textures[index].storedData, textures[index].swidth, textures[index].sheight, textures[index].schan);
	texname.push_back((n + "instance" + std::to_string(texname.size())));
	textures.push_back(t);

	return textures[textures.size() - 1];

}


Mesh& Environment::GetMesh(string n)
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

Mesh& Environment::GetMeshInstance(string n)
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
	Mesh m = Mesh(meshes[index].vertices, meshes[index].indices, GetTextureInstance(meshes[index].texture.path), meshes[index].usage);
	meshname.push_back((n + "instance" + std::to_string(meshname.size())));
	meshes.push_back(m);
	
	return meshes[meshes.size() - 1];

}

shader& Environment::GetShader(string n)
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

map<char, Character>& Environment::GetFont(string n)
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