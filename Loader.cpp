#pragma once
#include "loader.h"
#include "Environment.h"
#include "stringtools.h"

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
vector<FT_Face> faces;



int LoadTexture(string path, Environment &environment)
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

int LoadMesh(string path, Environment &environment)
{
	//return existing mesh
	for (int i = 0; i < environment.meshname.size(); i++)
	{
		if (path == environment.meshname[i])
			return i;
	}


	vector<string> vlines;
	string line;
	string address = environment.ApplicationPath + "graphics//" + path + ".vi";
	ifstream meshfile(environment.ApplicationPath + "graphics//" + path + ".vi");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			vlines.push_back(line);
		meshfile.close();
	}


	vector<string> ilines;
	ifstream imeshfile(environment.ApplicationPath + "graphics//" + path + ".im");
	if (imeshfile.is_open())
	{
		while (getline(imeshfile, line))
			ilines.push_back(line);
		imeshfile.close();
	}
	vector<Vertex> verts;
	for (uint i = 0; i < vlines.size(); i++)
	{
		float values[12];
		vector<string> indNotes = split(vlines[i], ' ');
		if (indNotes.size() != 12)
			return -1;
		for (uint j = 0; j < 12; j++)
		{
			values[j] = std::stof(indNotes[j]);
		}
		verts.push_back(Vertex(values));
	}
	vector<uint> inds;
	for (uint i = 0; i < ilines.size(); i++)
	{
		vector<string> indNotes = split(ilines[i], ' ');
		if (indNotes.size() != 3)
			return -1;
		for (uint j = 0; j < 3; j++)
		{
			inds.push_back(std::stoi(indNotes[j]));
		}
	}

	Texture tex = Texture();
	ifstream f((environment.ApplicationPath + "graphics//" + path + ".png").c_str());
	if (f.good())
		tex = environment.textures[LoadTexture(path, environment)];

	environment.meshname.push_back(path);
	environment.meshes.push_back(Mesh(verts, inds, tex));

	return environment.meshes.size() - 1;

}

int LoadMesh(string path, string usa, Environment &environment)
{
	//return existing mesh
	for (int i = 0; i < environment.meshname.size(); i++)
	{
		if (path == environment.meshname[i])
			return i;
	}


	vector<string> vlines;
	string line;
	string address = environment.ApplicationPath + "graphics//" + path + ".vi";
	ifstream meshfile(environment.ApplicationPath + "graphics//" + path + ".vi");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			vlines.push_back(line);
		meshfile.close();
	}


	vector<string> ilines;
	ifstream imeshfile(environment.ApplicationPath + "graphics//" + path + ".im");
	if (imeshfile.is_open())
	{
		while (getline(imeshfile, line))
			ilines.push_back(line);
		imeshfile.close();
	}
	vector<Vertex> verts;
	for (uint i = 0; i < vlines.size(); i++)
	{
		float values[12];
		vector<string> indNotes = split(vlines[i], ' ');
		if (indNotes.size() != 12)
			return -1;
		for (uint j = 0; j < 12; j++)
		{
			values[j] = std::stof(indNotes[j]);
		}
		verts.push_back(Vertex(values));
	}
	vector<uint> inds;
	for (uint i = 0; i < ilines.size(); i++)
	{
		vector<string> indNotes = split(ilines[i], ' ');
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


void LoadFont(string path, int pheight, Environment &environment)
{
	FT_Face face;
	if (FT_New_Face(ft, (environment.ApplicationPath + "graphics//" + path + ".ttf").c_str(), 0, &face))
	{
		std::cout << "Failed to load font" << path << std::endl;
		return;
	}
	FT_Set_Pixel_Sizes(face, 0, pheight);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	map<char, Character> characters;

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


vector<string> LoadManifest(string path, Environment &environment)
{
	vector<string> slines;
	string line;
	ifstream meshfile(environment.ApplicationPath + path + "manifest.txt");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			slines.push_back(line);
		meshfile.close();
	}
	return slines;
}

vector<string> LoadManifest(Environment &environment)
{
	vector<string> slines;
	string line;
	ifstream meshfile(environment.ApplicationPath + "manifest.txt");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			slines.push_back(line);
		meshfile.close();
	}
	return slines;
}












Bounds LoadBounds(string input)
{
	vector<string> lrud = split(input, ' ');
	if (lrud.size() < 9)
		return Bounds();
	return Bounds(glm::vec3(std::stof(lrud[0]), std::stof(lrud[1]), std::stof(lrud[2])), std::stof(lrud[3]), std::stof(lrud[4]), lrud[5], lrud[6], lrud[7], lrud[8]);

}


SceneData LoadLevel(string path, Environment& environment)
{

	vector<string> slines;
	string line;
	ifstream meshfile(environment.ApplicationPath + path + ".lvl");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			slines.push_back(line);
		meshfile.close();
	}
	vector<glm::vec2> poses;
	vector<string> posstring = split(slines[1], ' ');
	for (uint i = 0; i < 8; i += 2)
	{
		if (i < posstring.size() - 1)
			poses.push_back(glm::vec2(std::stoi(posstring[i]), std::stoi(posstring[i + 1])));
		else
			poses.push_back(glm::vec2(0, 0));
	}

	vector<Bounds> objects;
	for (uint i = 2; i < 18; i++)
	{
		if (i < slines.size())
			objects.push_back(LoadBounds(slines[i]));
		else
			objects.push_back(Bounds());
	}

	return SceneData(path, LoadBounds(slines[0]), objects, poses);


}

vector<string> LoadConversation(string path, Environment& environment)
{
	vector<string> clines;
	string line;
	ifstream meshfile(environment.ApplicationPath + path + ".tlk");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			clines.push_back(line);
		meshfile.close();
	}
	return clines;
}

BattleData LoadBattle(string path, Environment& environment)
{
	vector<string> BattleLs;
	string line;
	ifstream meshfile(environment.ApplicationPath + path + ".btl");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			BattleLs.push_back(line);
		meshfile.close();
	}

	return BattleData(path, BattleLs[0], split(BattleLs[1], ' '));
}

bool LoadEffects(string path, Environment& environment)
{
	vector<string> EffectLs;
	string line;
	ifstream meshfile(environment.ApplicationPath + path + ".efx");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			EffectLs.push_back(line);
		meshfile.close();
	}

	//Load Effects, stored as 4 lines
	for (uint i = 0; i + 3 < EffectLs.size(); i += 4)
	{
		vector<string> parseLine = split(EffectLs[i], ' ');
		for (int i = 0; i < environment.effectNames.size(); i++)
		{
			if (parseLine[0] == environment.effectNames[i])
				continue;
		}
		environment.effectNames.push_back(parseLine[0]);
		environment.effects.push_back(EffectData(parseLine[0], std::stof(parseLine[1]), std::stof(parseLine[2]), std::stoi(parseLine[3]), std::stof(parseLine[4]), std::stof(parseLine[5]), split(EffectLs[i + 1], ' '), split(EffectLs[i + 2], ' '), split(EffectLs[i + 3], ' ')));
	}
	return EffectLs.size() > 3;
}

bool LoadWeapons(string path, Environment& environment)
{
	vector<string> WeapLs;
	string line;
	ifstream meshfile(environment.ApplicationPath + path + ".wps");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			WeapLs.push_back(line);
		meshfile.close();
	}

	//Load weapons, stored as 1-2 lines
	for (uint i = 0; i < WeapLs.size(); i++)
	{
		vector<string> parseLine = split(WeapLs[i], ' ');
		for (int i = 0; i < environment.weaponNames.size(); i++)
		{
			if (parseLine[0] == environment.weaponNames[i])
				continue;
		}
		if (parseLine.size() == 5)
			environment.weapons.push_back(WeaponData(parseLine[0], parseLine[1] == "true", std::stoi(parseLine[2]), std::stoi(parseLine[3]), std::stoi(parseLine[4])));
		else if (parseLine.size() == 6)
			environment.weapons.push_back(WeaponData(parseLine[0], parseLine[1] == "true", std::stoi(parseLine[2]), std::stoi(parseLine[3]), std::stoi(parseLine[4]), parseLine[5]));
		else
			continue;
		environment.weaponNames.push_back(parseLine[0]);
		//see if there's any boons to load
		if (i + 1 < WeapLs.size())
		{
			vector<string> parseBoon = split(WeapLs[i], ' ');
			if (parseBoon[0] == "boon" || parseBoon[0] == "Boon")
			{
				for (uint i = 1; i < parseBoon.size(); i++)
				{
					environment.weapons[environment.weapons.size() - 1].Boons.push_back(parseBoon[i]);
				}
				i++;
			}
		}

	}
	return WeapLs.size() > 0;
}
bool LoadDefences(string path, Environment& environment)
{
	vector<string> DefLs;
	string line;
	ifstream meshfile(environment.ApplicationPath + path + ".dfs");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			DefLs.push_back(line);
		meshfile.close();
	}
	for (size_t i = 0; i < DefLs.size(); i++)
	{


		vector<string> parseLine = split(DefLs[i], ' ');
		for (int i = 0; i < environment.weaponNames.size(); i++)
		{
			if (parseLine[0] == environment.weaponNames[i])
				continue;
		}
		if (parseLine.size() == 2)
			environment.defences.push_back(DefenceData(parseLine[0], stoi(parseLine[1])));
		else
			return false;
		environment.defenceNames.push_back(parseLine[0]);

		if (i + 1 < DefLs.size())
		{
			vector<string> parseRes = split(DefLs[i], ' ');
			if (parseRes[0] == "resistances" || parseRes[0] == "Resistances")
			{
				for (uint i = 1; i < parseRes.size(); i++)
				{
					environment.defences[environment.defences.size() - 1].resistances.push_back(parseRes[i]);
				}
				i++;
			}
		}
	}
	return DefLs.size() > 0;
}

EnemyData LoadEnemy(string path, Environment& environment)
{
	vector<string> elines;
	string line;
	ifstream meshfile(environment.ApplicationPath + path + ".foe");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			elines.push_back(line);
		meshfile.close();
	}

	vector<string> parseLine = split(elines[0], ' ');
	return EnemyData(parseLine[0], parseLine[1], parseLine[2], std::stoi(parseLine[3]), parseLine[4], parseLine[5], split(elines[1], ' '), split(elines[2], ' '));

}

PlayerData LoadSave(int save, Environment& environment)
{
	vector<string> clines;
	string line;
	ifstream meshfile(environment.ApplicationPath + R"(/saves/save_)" + std::to_string(save) + ".sav");
	if (meshfile.is_open())
	{
		while (getline(meshfile, line))
			clines.push_back(line);
		meshfile.close();
	}
	if (std::stoi(clines[0]) == save)
	{
		return PlayerData(std::stoi(clines[0]), clines[1], std::stoi(clines[2]), split(clines[3], ' '), split(clines[4], ' '), split(clines[5], ' '), split(clines[6], ' '), split(clines[7], ' '), split(clines[8], ' '), split(clines[9], ' '), split(clines[10], ' '));
	}
	return PlayerData();

}

bool SetupGame(string path, Environment &environment)
{
	environment.ApplicationPath = path;
	vector<string> manifest = LoadManifest(environment);
	FT_Init_FreeType(&ft);

	environment.globalProjection = glm::perspective(45.0f, GLfloat(4.0f / 3.0f), 0.01f, 10000.0f);
	environment.UIOrtho = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, 10.0f, -10.0f);
	environment.gameOrtho = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, 10.0f, -10.0f);

	environment.campos = glm::vec3(0, 0, 2);

	for (uint i = 0; i < manifest.size(); i++)
	{
		vector<string> parseLine = split(manifest[i], ' ');
		if (parseLine.size() > 1 && parseLine[0][0] != '#')
		{
			if (parseLine[0] == "scene" || parseLine[0] == "Scene")
			{
				environment.sceneNames.push_back(parseLine[1]);
				environment.scenes.push_back(LoadLevel(parseLine[1], environment));
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
				environment.battleNames.push_back(parseLine[1]);
				environment.battles.push_back(LoadBattle(parseLine[1], environment));
			}
			else if (parseLine[0] == "conversation" || parseLine[0] == "Conversation" || parseLine[0] == "cutscene" || parseLine[0] == "Cutscene" || parseLine[0] == "dialog" || parseLine[0] == "Dialog")
			{
				environment.conversationNames.push_back(parseLine[1]);
				environment.conversations.push_back(LoadConversation(parseLine[1], environment));
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
				environment.enemyNames.push_back(environment.enemies[environment.enemies.size() - 1].name);
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

