#pragma once

#ifndef DefEnivronment

#define DefEnvironment "ENVIRONMENT"



#include "mesh.h"
#include "shader.h"
#include <string>
#include <vector>
#include <map>

#include "GameConstructs.h"
#include "framebuffering.h"

struct Environment {

	std::string ApplicationPath;

	//These are vectors of all loaded assets
	//Loaded Graphics Assets 


	std::vector<std::string> shaderNames;
	std::vector<shader> shaders;

	std::vector<std::string> meshname;
	std::vector<Mesh> meshes;

	std::vector<std::string> texname;
	std::vector<Texture> textures;

	std::vector<std::string> fontnames;
	std::vector<std::map<char, Character>> fonts;
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

	std::vector<std::string> effectNames;
	std::vector<EffectData> effects;

	std::vector<std::string> weaponNames;
	std::vector<WeaponData> weapons;

	std::vector<std::string> defenceNames;
	std::vector<DefenceData> defences;

	std::vector<std::string> enemyNames;
	std::vector<ActorData> enemies;

	std::vector<std::string> sceneNames;
	std::vector<SceneData> scenes;

	std::vector<std::string> UINames;
	std::vector<UIData> UIs;

	std::vector<std::string> battleNames;
	std::vector<BattleData> battles;

	std::vector<std::string> conversationNames;
	std::vector<std::vector<std::string>> conversations;

	std::vector<std::string> scriptableNames;
	std::vector<GameConstruct> scriptableObjects;

	//SCENE SCREEN
	glm::vec3 PlayerPos;
	SceneData CurrentScene;
	PlayerData CurrentSave;


	//tags currently in play
	std::vector<SceneTag> currentTags;
	//These ones don't get timed out
	std::vector<SceneTag> indefiniteTags;

	//BATTLE SCREEN
	bool inBattle = false;
	std::vector<ActorData> currentFoes;
	//what effect is in play
	std::string currentEffect[4]; //knight, ranger, wizard, you
	//how long the effect has left
	uint currentEffectTurns[4]; //knight, ranger, wizard, you
	//current health (doesn't carry over between fights)
	int healthBars[4];	//knight, ranger, wizard, you
	//dice available still this round, reset to dice in playerdata at the end.
	int diceleft;

	//CONVERSATION SCREEN
	bool inConversation = false;
	std::vector<std::string> ConversationScript;
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

	Mesh& GetMesh(std::string n);

	Mesh& GetMeshInstance(std::string n);

	Texture& GetTexture(std::string n);

	Texture& GetTextureInstance(std::string n);

	shader& GetShader(std::string n);

	std::map<char, Character>& GetFont(std::string n);
};

#endif // !DefEnivronment
