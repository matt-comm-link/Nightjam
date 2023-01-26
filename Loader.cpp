#pragma once

#ifndef DEFLOADERCPP

#define DEFLOADERCPP "LOADERCPP"



#include "loader.h"
#include "Environment.h"

#ifndef DEFCONSTRUCTCPP
#include "stringtools.h"
#endif // !stringfunc

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#endif // !STB_IMAGE_IMPLEMENTATION


#ifndef FTBUILD
#define FTBUILD

#include <ft2build.h>
#include FT_FREETYPE_H    
#endif // !FTBUILD


FT_Library ft;
std::vector<FT_Face> faces;



int LoadTexture(std::string path, Environment &environment)
{
	//return existing texture
	for (int i = 0; i < environment.texname.size(); i++)
	{
		if (path == environment.texname[i])
			return i;
	}

	stbi_set_flip_vertically_on_load(true);

	std::string texpath = environment.ApplicationPath + "graphics//" + path + ".png";
	int width, height, nrChannels;
	struct stat buffer;
	unsigned char* data = stbi_load(texpath.c_str(), &width, &height, &nrChannels, 0);
	environment.textures.push_back(Texture(path, data, width, height, nrChannels));
	environment.texname.push_back(path);
	stbi_image_free(data);
	return environment.textures.size() - 1;

}

int LoadMesh(std::string path, Environment &environment)
{
	//return existing mesh
	for (int i = 0; i < environment.meshname.size(); i++)
	{
		if (path == environment.meshname[i])
			return i;
	}


	std::vector<std::string> vlines;
	std::string line;
	std::string address = environment.ApplicationPath + "graphics//" + path + ".vi";
	std::ifstream meshfile(environment.ApplicationPath + "graphics//" + path + ".vi");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			vlines.push_back(line);
		meshfile.close();
	}


	std::vector<std::string> ilines;
	std::ifstream imeshfile(environment.ApplicationPath + "graphics//" + path + ".im");
	if (imeshfile.is_open())
	{
		while (getline(imeshfile, line))
			ilines.push_back(line);
		imeshfile.close();
	}
	std::vector<Vertex> verts;
	for (uint i = 0; i < vlines.size(); i++)
	{
		float values[12];
		std::vector<std::string> indNotes = split(vlines[i], ' ');
		if (indNotes.size() != 12)
			return -1;
		for (uint j = 0; j < 12; j++)
		{
			values[j] = std::stof(indNotes[j]);
		}
		verts.push_back(Vertex(values));
	}
	std::vector<uint> inds;
	for (uint i = 0; i < ilines.size(); i++)
	{
		std::vector<std::string> indNotes = split(ilines[i], ' ');
		if (indNotes.size() != 3)
			return -1;
		for (uint j = 0; j < 3; j++)
		{
			inds.push_back(std::stoi(indNotes[j]));
		}
	}

	Texture tex = Texture();
	std::ifstream f((environment.ApplicationPath + "graphics//" + path + ".png").c_str());
	if (f.good())
		tex = environment.textures[LoadTexture(path, environment)];

	environment.meshname.push_back(path);
	environment.meshes.push_back(Mesh(verts, inds, tex));

	return environment.meshes.size() - 1;

}

int LoadMesh(std::string path, std::string usa, Environment &environment)
{
	//return existing mesh
	for (int i = 0; i < environment.meshname.size(); i++)
	{
		if (path == environment.meshname[i])
			return i;
	}


	std::vector<std::string> vlines;
	std::string line;
	std::string address = environment.ApplicationPath + "graphics//" + path + ".vi";
	std::ifstream meshfile(environment.ApplicationPath + "graphics//" + path + ".vi");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			vlines.push_back(line);
		meshfile.close();
	}


	std::vector<std::string> ilines;
	std::ifstream imeshfile(environment.ApplicationPath + "graphics//" + path + ".im");
	if (imeshfile.is_open())
	{
		while (getline(imeshfile, line))
			ilines.push_back(line);
		imeshfile.close();
	}
	std::vector<Vertex> verts;
	for (uint i = 0; i < vlines.size(); i++)
	{
		float values[12];
		std::vector<std::string> indNotes = split(vlines[i], ' ');
		if (indNotes.size() != 12)
			return -1;
		for (uint j = 0; j < 12; j++)
		{
			values[j] = std::stof(indNotes[j]);
		}
		verts.push_back(Vertex(values));
	}
	std::vector<uint> inds;
	for (uint i = 0; i < ilines.size(); i++)
	{
		std::vector<std::string> indNotes = split(ilines[i], ' ');
		if (indNotes.size() != 3)
			return -1;
		for (uint j = 0; j < 3; j++)
		{
			inds.push_back(std::stoi(indNotes[j]));
		}
	}
	Texture tex;
	tex = environment.textures[LoadTexture(path, environment)];

	GLenum usage = GL_STATIC_DRAW;
	if (usa == "dynamic")
		usage = GL_DYNAMIC_DRAW;

	environment.meshname.push_back(path);
	environment.meshes.push_back(Mesh(verts, inds, tex, usage));

	return environment.meshes.size() - 1;

}


void LoadFont(std::string path, int pheight, Environment &environment)
{
	FT_Face face;
	if (FT_New_Face(ft, (environment.ApplicationPath + "graphics//" + path + ".ttf").c_str(), 0, &face))
	{
		std::cout << "Failed to load font" << path << '\n';
		return;
	}
	FT_Set_Pixel_Sizes(face, 0, pheight);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	std::map<char, Character> characters;

	for (uint as = 0; as < 128; as++)
	{
		FT_Load_Char(face, as, FT_LOAD_RENDER);
		characters.insert(std::pair<char, Character>(as, Character(Texture(path, face), glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x)));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	environment.fonts.push_back(characters);
	faces.push_back(face);
	environment.fontnames.push_back(path);

}


std::vector<std::string> LoadManifest(std::string path, Environment &environment)
{
	std::vector<std::string> slines;
	std::string line;
	std::ifstream meshfile(environment.ApplicationPath + path + "manifest.txt");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			slines.push_back(line);
		meshfile.close();
	}
	return slines;
}

std::vector<std::string> LoadManifest(Environment &environment)
{
	std::vector<std::string> slines;
	std::string line;
	std::ifstream meshfile(environment.ApplicationPath + "manifest.txt");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			slines.push_back(line);
		meshfile.close();
	}
	return slines;
}












Bounds LoadBounds(std::string input)
{
	return(Bounds(input));
}

UIElement LoadElement(std::string input)
{
	return(UIElement(input));
}


SceneData LoadLevel(std::string path, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath + path);
	fileStream << file.rdbuf();

	return SceneData(fileStream.str());


}

std::vector<std::string> LoadConversation(std::string path, Environment& environment)
{
	std::vector<std::string> clines;
	std::string line;
	std::ifstream meshfile(environment.ApplicationPath + path);
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			clines.push_back(line);
		meshfile.close();
	}
	return clines;
}

BattleData LoadBattle(std::string path, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath + path);
	fileStream << file.rdbuf();

	return BattleData(fileStream.str());
}

bool LoadEffects(std::string path, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath + path);
	fileStream << file.rdbuf();
	std::vector<std::string> chunks = split(fileStream.str(), '**');
	
	for (size_t i = 0; i < chunks.size(); i++)
	{
		environment.effects.push_back(EffectData(chunks[i]));
		environment.effectNames.push_back(environment.effects[environment.effects.size()].name);
	}
	
	return chunks.size() > 0;
}

bool LoadWeapons(std::string path, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath + path);
	fileStream << file.rdbuf();
	std::vector<std::string> chunks = split(fileStream.str(), '**');

	for (size_t i = 0; i < chunks.size(); i++)
	{
		environment.weapons.push_back(WeaponData(chunks[i]));
		environment.weaponNames.push_back(environment.effects[environment.weapons.size()].name);
	}

	return chunks.size() > 0;
}
bool LoadDefences(std::string path, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath + path);
	fileStream << file.rdbuf();
	std::vector<std::string> chunks = split(fileStream.str(), '**');

	for (size_t i = 0; i < chunks.size(); i++)
	{
		environment.defences.push_back(DefenceData(chunks[i]));
		environment.defenceNames.push_back(environment.effects[environment.defences.size()].name);
	}

	return chunks.size() > 0;
}

ActorData LoadEnemy(std::string path, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath + path);
	fileStream << file.rdbuf();

	return ActorData(fileStream.str());
}

PlayerData LoadSave(int save, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath + "\Save\save" + std::to_string(save) + ".cst");
	fileStream << file.rdbuf();

	return PlayerData(fileStream.str());

}

UIData LoadUI(std::string path, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath +  path);
	fileStream << file.rdbuf();

	return UIData(fileStream.str());
}

GameConstruct LoadConstruct(std::string path, Environment& environment)
{
	std::stringstream fileStream;
	std::ifstream file(environment.ApplicationPath + path);
	fileStream << file.rdbuf();

	return UIData(fileStream.str());
}

bool SetupGame(std::string path, Environment &environment)
{
	environment.ApplicationPath = path;
	std::vector<std::string> manifest = LoadManifest(environment);
	FT_Init_FreeType(&ft);

	environment.globalProjection = glm::perspective(45.0f, GLfloat(4.0f / 3.0f), 0.01f, 10000.0f);
	environment.UIOrtho = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, 10.0f, -10.0f);
	environment.gameOrtho = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, 10.0f, -10.0f);

	environment.campos = glm::vec3(0, 0, 2);

	for (uint i = 0; i < manifest.size(); i++)
	{
		std::vector<std::string> parseLine = split(manifest[i], ' ');
		if (parseLine.size() > 1 && parseLine[0][0] != '#')
		{
			if (parseLine[0] == "scene" || parseLine[0] == "Scene")
			{
				environment.scenes.push_back(LoadLevel(parseLine[1], environment));
				environment.sceneNames.push_back(environment.scenes.back().name);
			}
			else if (parseLine[0] == "mesh" || parseLine[0] == "Mesh")
			{
				if (parseLine.size() > 2)
					LoadMesh(parseLine[1], parseLine[2], environment);
				else
					LoadMesh(parseLine[1], environment);
			}
			else if (parseLine[0] == "texture" || parseLine[0] == "Texture")
			{
				LoadTexture(parseLine[1], environment);
			}
			else if (parseLine[0] == "font" || parseLine[0] == "Font")
			{
				if (parseLine.size() > 2)
					LoadFont(parseLine[1], std::stoi(parseLine[2]), environment);
			}
			else if (parseLine[0] == "shader" || parseLine[0] == "Shader")
			{
				environment.shaderNames.push_back(parseLine[1]);
				environment.shaders.push_back(shader((environment.ApplicationPath + "graphics//" + parseLine[1] + ".vert").c_str(), (environment.ApplicationPath + "graphics//" + parseLine[1] + ".frag").c_str()));
			}
			else if (parseLine[0] == "battle" || parseLine[0] == "Battle")
			{
				environment.battles.push_back(LoadBattle(parseLine[1], environment));
				environment.battleNames.push_back(environment.battles.back().name);
			}
			else if (parseLine[0] == "conversation" || parseLine[0] == "Conversation" || parseLine[0] == "cutscene" || parseLine[0] == "Cutscene" || parseLine[0] == "dialog" || parseLine[0] == "Dialog")
			{
				environment.conversations.push_back(LoadConversation(parseLine[1], environment));
				environment.conversationNames.push_back(environment.conversations.back()[0]);
			}
			else if (parseLine[0] == "effects" || parseLine[0] == "Effects")
			{
				LoadEffects(path, environment);
			}
			else if (parseLine[0] == "weapons" || parseLine[0] == "Weapons")
			{
				LoadWeapons(path, environment);
			}
			else if (parseLine[0] == "defences" || parseLine[0] == "Defences")
			{
				LoadDefences(path, environment);
			}
			else if (parseLine[0] == "enemy" || parseLine[0] == "Enemy")
			{
				environment.enemies.push_back(LoadEnemy(parseLine[1], environment));
				environment.enemyNames.push_back(environment.enemies.back().name);
			}
			else if (parseLine[0] == "ui" || parseLine[0] == "UI")
			{
				environment.UIs.push_back(LoadUI(parseLine[1], environment));
				environment.UINames.push_back(environment.UIs.back().name);
			}
			else if(parseLine[0] == "script" || parseLine[0] == "Script")
			{
				environment.scriptableObjects.push_back(LoadConstruct(parseLine[1], environment));
				environment.scriptableNames.push_back(environment.scriptableObjects.back().name);
			}
		}
	}

	environment.RWidth = environment.Twidth;
	environment.RHeight = environment.Theight;

	environment.FontMesh = environment.GetMeshInstance("uisquare");
	environment.FontShader = environment.GetShader("ui");
	
	environment.CurrentScene = SceneData();



	return true;
}

#endif // !DEFLOADERCPP
