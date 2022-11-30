#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "mesh.h"


#ifndef uint
#define uint unsigned int
#endif // !uint

struct PlayerData
{	
	uint saveFileNom;

	//Scene to load game into
	std::string CurrentScene = "";
	//Total number of collected dice
	uint diceCount = 0;
	//Current level (goes up and add to stats from table)
	uint level[4] = { 1, 1, 1, 1 }; //knight, ranger, wizard, you
	//current max state of healthbar
	uint maxHealth[4] = { 0, 0, 0, 0 };	//knight, ranger, wizard
	//current weapon, cross referenced against loaded table
	string weaponUsed[4] = { "", "", "", ""}; //knight, ranger, wizard
	//backup weapon, cross referenced against loaded table. You can give this to the AI if you find one
	string secondaryWeaponUsed[4] = { "", "", "", "" }; //knight, ranger, wizard
	//current defence, cross referenced against loaded table
	string defenceUsed[4] = { "","","","" }; //knight, ranger, wizard, you
	//current relationship with party members
	uint friendship[3] = {0, 0, 0}; //knight, ranger, wizard

	//positions on map
	glm::vec2 Positions[4] = { glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0) }; //knight, ranger, wizard, you

	//used for dialog branching
	vector<string> tagsAmassed;


	PlayerData()
	{
	}

	PlayerData(uint sn, string cs, uint dc, vector<string> lvls, vector<string> mhps, vector<string> wud, vector<string> swud, vector<string> dud, vector<string> fs, vector<string> ps, vector<string> tags)
	{
		saveFileNom = sn;
		CurrentScene = cs;
		diceCount = dc;
		for (uint i = 0; i < 4; i++)
		{
			if (i < lvls.size())
				level[i] = std::stoi(lvls[i]);
			else
				level[i] = 1;
		}
		for (uint i = 0; i < 4; i++)
		{
			if (i < mhps.size())
				maxHealth[i] = std::stoi(mhps[i]);
			else
				maxHealth[i] = 1;
		}
		for (uint i = 0; i < 4; i++)
		{
			if (i < wud.size())
				weaponUsed[i] = wud[i];
			else
				weaponUsed[i] = "default";
		}
		for (uint i = 0; i < 4; i++)
		{
			if (i < swud.size())
				secondaryWeaponUsed[i] = swud[i];
			else
				secondaryWeaponUsed[i] = "default";
		}
		for (uint i = 0; i < 4; i++)
		{
			if (i < dud.size())
				defenceUsed[i] = dud[i];
			else
				defenceUsed[i] = "default";
		}
		for (uint i = 0; i < 3; i++)
		{
			if (i < fs.size())
				friendship[i] = std::stoi(fs[i]);
			else
				friendship[i] = 0;
		}
		for (uint i = 0; i < 8; i+= 2)
		{
			if (i + 1 < ps.size())
				Positions[i/2] = glm::vec2(std::stof(ps[i]), std::stof(ps[i+1]));
			else
				Positions[i] = glm::vec2(0, 0);
		}
		for (uint i = 0; i < tags.size(); i ++)
		{
			tagsAmassed.push_back(tags[i]);
		}
	}


	vector<string> Save()
	{
		vector<string> output;
		output.push_back(std::to_string(saveFileNom));
		output.push_back(CurrentScene);
		output.push_back(std::to_string(diceCount));
		output.push_back(std::to_string(level[0]) + " " + std::to_string(level[1]) + " " + std::to_string(level[2]) + " " + std::to_string(level[3]));
		output.push_back(std::to_string(maxHealth[0]) + " " + std::to_string(maxHealth[1]) + " " + std::to_string(maxHealth[2]) + " " + std::to_string(maxHealth[3]));
		output.push_back(weaponUsed[0] + " " + weaponUsed[1] + " " + weaponUsed[2] + " " + weaponUsed[3]);
		output.push_back(secondaryWeaponUsed[0] + " " + secondaryWeaponUsed[1] + " " + secondaryWeaponUsed[2] + " " + secondaryWeaponUsed[3]);
		output.push_back(defenceUsed[0] + " " + defenceUsed[1] + " " + defenceUsed[2] + " " + defenceUsed[3]);
		output.push_back(std::to_string(friendship[0]) + " " + std::to_string(friendship[1]) + " " + std::to_string(friendship[2]));
		output.push_back(std::to_string(Positions[0].x) + " " + std::to_string(Positions[0].y) + " " + std::to_string(Positions[1].x) + " " + std::to_string(Positions[1].y) + " " + std::to_string(Positions[2].x) + " " + std::to_string(Positions[2].y) + " " + std::to_string(Positions[3].x) + " " + std::to_string(Positions[3].y));
		string tags;
		for (uint i = 0; i < tagsAmassed.size(); i++)
		{
			tags += tagsAmassed[i];
			if (i + 1 < tagsAmassed.size())
				tags += " ";
		}
		output.push_back(tags);
		return output;
	}
};

struct WeaponData
{
	string name;
	//heal instead
	bool heal;
	//minimum deal
	uint damageMin;
	//add random range (top this) and level to get damage dealt
	uint damageAdd;
	//crit bonus, add to roll to see to crit
	uint CritRate;
	//Tags compared against resistances, if anything left after testing them, then this means the attack is resisted
	vector<string> Boons;
	//effect type applied on successful attack.
	string Effect;

	WeaponData()
	{
		name = "";
		heal = false;
		damageMin = 0;
		damageAdd = 0;
		CritRate = 0;
		Effect = "";
	}
	WeaponData(string n, bool h, uint dm, uint da, uint cr)
	{
		name = n;
		heal = h;
		damageMin = dm;
		damageAdd = da;
		CritRate = cr;
		Effect = "";
	}
	WeaponData(string n, bool h, uint dm, uint da, uint cr, string e)
	{
		name = n;
		heal = h;
		damageMin = dm;
		damageAdd = da;
		CritRate = cr;
		Effect = e;
	}
	WeaponData(string n, bool h, uint dm, uint da, uint cr, string e, vector<string> b)
	{
		name = n;
		heal = h;
		damageMin = dm;
		damageAdd = da;
		CritRate = cr;
		Effect = e;
		Boons = b;
	}
	WeaponData(string n, bool h, uint dm, uint da, uint cr, vector<string> b)
	{
		name = n;
		heal = h;
		damageMin = dm;
		damageAdd = da;
		CritRate = cr;
		Effect = "";
		Boons = b;
	}

};

struct DefenceData
{	
	string name;
	//If pass this roll, crit and deal double
	uint CritTarget;
	//tags compared against resistances, if anything left after testing them, then this means the attack does half damage
	vector<string> resistances;

	DefenceData()
	{
		name = "";
		CritTarget = 0;
	}

	DefenceData(string n, uint ct)
	{
		name = n;
		CritTarget = ct;
	}

	DefenceData(string n, uint ct, vector<string> res)
	{
		name = n;
		CritTarget = ct;
		resistances = res;
	}
};

struct EffectData
{
	string name;
	//how many rounds to count before it goes
	uint rounds;
	//effects with higher priority aren't replaced
	uint priority;
	//What resistences prevent this effect from happening
	vector<string>  resistanceBlocks;
	//what resistences to ignore when this is in effect
	vector<string>  resistanceDrops;
	//what resistences to add when this is in effect
	vector<string>  resistanceAdds;
	//damage over time, if negative, this heals
	int damagePerRound;
	//how much subsequent hits do while this is in effect
	float damageMod;
	//how much subsequent attacks do while this is in effect
	float attackMod;

	EffectData()
	{
		name = "";
		rounds = 0;
	}

	EffectData(string n, uint r, uint p, int dpr, float dm, float am, vector<string> rb, vector<string> rd, vector<string> ra)
	{
		name = n;
		rounds = r;
		priority = p;
		resistanceBlocks = rb;
		resistanceDrops = rd;
		resistanceAdds = ra;
		damagePerRound = dpr;
		damageMod = dm;
		attackMod = am;
	}

};

struct EnemyData
{
	//also used to display name
	string name;
	//graphics stuff
	string model;
	//shader
	string shader;
	//current health
	int healthBar;
	//max state of healthbar
	uint maxHealth;
	//current weapon, cross referenced against loaded table
	string weaponUsed;
	//current defence, cross referenced against loaded table
	string defenceUsed;
	//what effect is in play
	EffectData currentEffect;
	//how long the effect has left
	uint currentEffectTurns;
	//Modifier to how much each party member prefers to attack it
	uint partyPreference[3]; //knight, ranger, wizard
	//How much each party member has pissed it off/predelection to target party members
	uint currentPartyBias[4]; //knight, ranger, wizard, you


	EnemyData()
	{
		name = "";
		model = "default";
		shader = "default";
		healthBar = 0;
		maxHealth = 0;
		weaponUsed = "";
		defenceUsed = "";
		currentEffect = EffectData();
		currentEffectTurns = 0;
		for (uint i = 0; i < 3; i++)
		{
			partyPreference[i] = 0;
		}
		for (uint i = 0; i < 4; i++)
		{
			currentPartyBias[i] = 0;
		}
	}

	EnemyData(string n, string m, string s, uint mh, string wu, string du, vector<string> pp, vector<string> cpb)
	{
		name = n;
		model = m;
		shader = s;
		healthBar = mh;
		maxHealth = mh;
		weaponUsed = wu;
		defenceUsed = du;
		currentEffect = EffectData();
		currentEffectTurns = 0;
		for (uint i = 0; i < 3; i++)
		{
			if (pp.size() < i)
				partyPreference[i] = std::stoi(pp[i]);
		}
		for (uint i = 0; i < 4; i++)
		{
			if (cpb.size() < i)
				currentPartyBias[i] = std::stoi(cpb[i]);
		}

	}

	EnemyData(string n, string m, string s, uint mh, string wu, string du, vector<uint> pp, vector<uint> cpb)
	{
		name = n;
		model = m;
		shader = s;
		healthBar = mh;
		maxHealth = mh;
		weaponUsed = wu;
		defenceUsed = du;
		currentEffect = EffectData();
		currentEffectTurns = 0;
		for (uint i = 0; i < 3; i++)
		{
			if (pp.size() < i)
				partyPreference[i] = pp[i];
		}
		for (uint i = 0; i < 4; i++)
		{
			if (cpb.size() < i)
				currentPartyBias[i] = cpb[i];
		}

	}


	void AddEffect(EffectData &e)
	{
		currentEffect = e;
		currentEffectTurns = e.rounds;
	}
};

struct Bounds 
{
	//extents, most in given direction
	glm::vec3 centre;
	float modelRot = 0;
	float width, height;
	float left, right, up, down;
	string type; //passable, solid, trigger solid, trigger passable, walk trap
	string model; //model and texture data
	string shader; //shader stripped from model
	string action; //interpreted. Load new scene, load dialog scene, load battle, with note as to whether to overwrite player position

	Bounds(glm::vec3 c, float w, float h, string t, string m, string s, string a)
	{
		centre = c;
		width = w;
		height = h;
		left = centre.x - width/2;
		right = centre.x + width / 2;
		up = centre.y + height / 2;
		down = centre.y - height / 2;
		type = t;
		model = m;
		shader = s;
		action = a;
	}

	Bounds(float l, float r, float u, float d, string t, string m, string s, string a)
	{
		width = abs(r) - abs(l);
		height = abs(u) - abs(d);
		left = l;
		right = r;
		up = u;
		down = d;
		centre = glm::vec3((l + r) / 2, 0, (u + d) / 2);
		type = t;
		model = m;
		shader = s;
		action = a;
	}
	Bounds()
	{
		centre = glm::vec3(0, 0, 0);
		width = 2;
		height = 2;
		type = "";
		model = "default";
		shader = "default";
		action = "none";
	}


};


struct SceneData
{
	//also used to load model & sound
	string name;
	//keep player within
	Bounds limits;
	//form structure, keep player out, 
	vector<Bounds> Objects;
	//where players spawn in
	glm::vec2 StartingPositions[4] = { glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0) }; //knight, ranger, wizard, you 


	SceneData()
	{
		name = "";
		limits = Bounds();
	}

	SceneData(string n, Bounds l, vector<Bounds> o, vector<glm::vec2> sp)
	{
		name = n;
		limits = l;
		for (uint i = 0; i < o.size(); i++)
		{
			if (o.size() < i)
				Objects[i] = o[i];
			else
				Objects[i] = Bounds();
		}
		for (uint i = 0; i < 4; i++)
		{
			if (sp.size() < i)
				StartingPositions[i] = sp[i];
			else
				StartingPositions[i] = glm::vec2(0, 0);
		}

	}

	SceneData(string n, Bounds l, Bounds o[16], glm::vec2 sp[4])
	{
		name = n;
		limits = l;
		for (uint i = 0; i < 16; i++)
		{
			Objects[i] = o[i];
		}
		for (uint i = 0; i < 4; i++)
		{
			StartingPositions[i] = sp[i];
		}

	}


};

struct BattleData
{
	//also used to load music
	string name;
	//is there a starting effect applied to everyone?
	string startEff;
	//collects foes
	vector<string> foes;

	BattleData()
	{
		name = "";
		startEff = "";
	}

	BattleData(string n, string s, vector<string> f)
	{
		name = n;
		startEff = s;
		foes = f;
	}
};
