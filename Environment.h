#pragma once

#include "mesh.h"
#include "shader.h"
#include <string>
#include <vector>
#include <map>


#include "GameConstructs.h"



string ApplicationPath;

//These are vectors of all loaded assets
//Loaded Graphics Assets 


vector<string> shaderNames;
vector<shader> shaders;

vector<string> meshname;
vector<Mesh> meshes;

vector<string> texname;
vector<Texture> textures;

vector<string> fontnames;
vector<map<char, Character>> fonts;
shader FontShader;
Mesh FontMesh;


glm::vec3 campos;
glm::mat4 globalView;

glm::mat4 globalProjection;
glm::mat4 UIOrtho;

//Loaded game assets

vector<string> effectNames;
vector<EffectData> effects;

vector<string> weaponNames;
vector<WeaponData> weapons;

vector<string> defenceNames;
vector<DefenceData> defences;

vector<string> enemyNames;
vector<EnemyData> enemies;

vector<string> sceneNames;
vector<SceneData> scenes;

vector<string> battleNames;
vector<BattleData> battles;

vector<string> conversationNames;
vector<vector<string>> conversations;

//SCENE SCREEN
glm::vec3 PlayerPos;
SceneData CurrentScene;
PlayerData CurrentSave;

//BATTLE SCREEN
bool inBattle = false;
vector<EnemyData> currentFoes;
//what effect is in play
string currentEffect[4]; //knight, ranger, wizard, you
//how long the effect has left
uint currentEffectTurns[4]; //knight, ranger, wizard, you
//current health (doesn't carry over between fights)
int healthBars[4];	//knight, ranger, wizard, you
//dice available still this round, reset to dice in playerdata at the end.
int diceleft;

//CONVERSATION SCREEN
bool inConversation = false;
vector<string> ConversationScript;
uint ConversationPlace;

//CONSTANTS
//How far til bump
float playerCollisionRadius = 0.5f;
float playerSpeed;
bool MovementInputLocked;
bool MovementPhysicsLocked;

float deltaTime;
static int Wwidth, Wheight;

//INPUT STATE
glm::vec2 InputWASD;
glm::vec2 InputLastMousePos;
glm::vec2 InputMousePos;
glm::vec2 InputMouseCentred;
bool InputLastMouse0;
bool InputLastMouse1;
bool InputLastESC;
bool InputLastSpace;

bool InputMouse0;
bool InputMouse1;
bool InputESC;
bool InputSpace;


Mesh& GetMesh(string n)
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

shader& GetShader(string n)
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

map<char, Character>& GetFont(string n)
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
