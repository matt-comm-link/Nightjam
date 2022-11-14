#pragma once


#include "mesh.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <map>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#endif // !STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "GameConstructs.h"

#ifndef FTBUILD
#define FTBUILD

#include <ft2build.h>
#include FT_FREETYPE_H    
#endif // !FTBUILD


FT_Library ft;
vector<FT_Face> faces;


int LoadTexture(string path);

int LoadMesh(string path);

int LoadMesh(string path, string usa);


void LoadFont(string path, int pheight);


vector<string> LoadManifest(string path);

vector<string> LoadManifest();


Bounds LoadBounds(string input);

SceneData LoadLevel(string path);

vector<string> LoadConversation(string path);

BattleData LoadBattle(string path);

bool LoadEffects(string path);

bool LoadWeapons(string path);

bool LoadDefences(string path);

EnemyData LoadEnemy(string path);

PlayerData LoadSave(int save);

bool SetupGame(string path);