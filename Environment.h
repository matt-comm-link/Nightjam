#pragma once

#include "mesh.h"
#include "shader.h"
#include <string>
#include <vector>
#include <map>

#include "GameConstructs.h"
#include "framebuffering.h"

struct Environment {

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
	glm::mat4 postView;


	glm::mat4 globalProjection;
	glm::mat4 UIOrtho;
	glm::mat4 gameOrtho;
	glm::mat4 postOrtho;


	float TwidthR = 4;
	float TheightR = 3;
	float Twidth = 640;
	float Theight = 480;
	//window height and width
	float Wwidth = 640, Wheight = 480;
	//render height and width of game window
	float RWidth = 640, RHeight = 480;
	//target aspect ratio of screen 
	float wRatio = 1;
	float hRatio = 1;
	
	//ergo using that, 
	float wRatioAdjust;
	float hRatioAdjust;

	//Scalar used for UI positioning
	float UIRatio = 1;
	glm::vec2 MPosOffset;

	FrameBuffer gameBuffer;
	FrameBuffer postBuffer;

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


	//INPUT STATE
	glm::vec2 InputWASD;
	glm::vec2 InputLastMousePos;
	glm::vec2 InputMousePos;
	glm::vec2 InputMouseCentred;
	glm::vec2 InputMousePosRatioed;
	glm::vec2 InputMousePosRatioedCentred;


	bool InputLastMouse0;
	bool InputLastMouse1;
	bool InputLastESC;
	bool InputLastSpace;

	bool InputMouse0;
	bool InputMouse1;
	bool InputESC;
	bool InputSpace;

	Mesh& GetMesh(string n);

	Mesh& GetMeshInstance(string n);

	Texture& GetTexture(string n);

	Texture& GetTextureInstance(string n);

	shader& GetShader(string n);

	map<char, Character>& GetFont(string n);
};