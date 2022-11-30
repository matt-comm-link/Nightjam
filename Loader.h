#pragma once



#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <map>


#include "GameConstructs.h"
#include "Environment.h"



int LoadTexture(string path, Environment &environment);

int LoadMesh(string path, Environment &environment);

int LoadMesh(string path, string usa, Environment &environment);


void LoadFont(string path, int pheight, Environment &environment);


vector<string> LoadManifest(string path, Environment &environment);

vector<string> LoadManifest(Environment &environment);


Bounds LoadBounds(string input);

SceneData LoadLevel(string path, Environment& environment);

vector<string> LoadConversation(string path, Environment& environment);

BattleData LoadBattle(string path, Environment& environment);

bool LoadEffects(string path, Environment& environment);

bool LoadWeapons(string path, Environment& environment);

bool LoadDefences(string path, Environment& environment);

EnemyData LoadEnemy(string path, Environment& environment);

PlayerData LoadSave(int save, Environment& environment);

bool SetupGame(string path, Environment &environment);