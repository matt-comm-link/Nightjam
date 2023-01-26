#pragma once

#ifndef DEFLOADER

#define DEFLOADER "LOADER"

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <map>


#include "GameConstructs.h"
#include "Environment.h"



int LoadTexture(std::string path, Environment &environment);

int LoadMesh(std::string path, Environment &environment);

int LoadMesh(std::string path, std::string usa, Environment &environment);


void LoadFont(std::string path, int pheight, Environment &environment);


std::vector<std::string> LoadManifest(std::string path, Environment &environment);

std::vector<std::string> LoadManifest(Environment &environment);


Bounds LoadBounds(std::string input);

SceneData LoadLevel(std::string path, Environment& environment);

std::vector<std::string> LoadConversation(std::string path, Environment& environment);

BattleData LoadBattle(std::string path, Environment& environment);

bool LoadEffects(std::string path, Environment& environment);

bool LoadWeapons(std::string path, Environment& environment);

bool LoadDefences(std::string path, Environment& environment);

ActorData LoadEnemy(std::string path, Environment& environment);

PlayerData LoadSave(int save, Environment& environment);

bool SetupGame(std::string path, Environment &environment);
#endif // !LOADER
