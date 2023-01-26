#pragma once

#ifndef DefGameConstructs
#define DefGameConstructs "GAMECONSTRUCTS"



#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>




#ifndef uint
#define uint unsigned int
#endif // !uint


struct SceneTag
{
	//in seconds
	float lifetime;
	std::string contents;

	SceneTag(){}

	SceneTag(float ltS, std::string c)
	{
		contents = c;
		lifetime = ltS;
	}
};

struct GameConstruct
{
	//everything has a name
	std::string name; //NAME [rest of line]
	//path to asset (doesn't necessarily line up with name
	std::string path; //Gets this from constructor or set for saving
	//Generalised protection flag, use as approrpiate.
	bool ReadOnly;  //READONLY (if present)
	//When requesting a mesh or texture will thing require an instance?
	bool Altering; //ALTERING (if present)
	//default tag
	SceneTag pingTag; //PING [time float] [rest of line]

	std::string AttachedScript; //CODE: [bunch of dialogscript] *

	GameConstruct()
	{

	}
	GameConstruct(std::string data)
	{
		Unpack(data);
	}

	virtual void Unpack(std::string data);

	virtual std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if(AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

	virtual SceneTag Ping()
	{
		return pingTag;
	}

	virtual std::string Script()
	{
		return AttachedScript;
	}
};

struct UIElement : public GameConstruct
{

	//positional data
	glm::vec3 centre; //POSITION [x y z]
	float width; //DIMENSIONS [w h]
	float height;
	float left, right, up, down; //[name] [float]

	//display data
	std::string Mesh; //MESH [name]
	std::string texture; //TEXTURE [name]
	//blend colour with this if mouse hovers
	glm::vec4 HighlightTint; //HIGHLIGHT [r g b a]

	//Allows the UI to toggle groups of UI based on this tag
	std::vector<std::string> Groups; //GROUP [tag]

	std::string text; //TEXT [x y] [message], defaults to nothing to display at offset 0,0
	glm::vec2 textOffset;
	std::string font; //FONT [name] [size]
	int fontsize; //what size of font to use

	std::string TalkingHead; //HEAD [name]
	std::string Mood; //set in code, choses mood for talking head

	//Does this element follow the cursor and if so by how many pixels
	bool FollowCursor; //FOLLOW (if present) [x y]
	glm::vec2 followCursorOffset; 
	bool FollowingCursor; //Set in code, defaults to FollowCursor but can be turned off.

	//interaction data
	//is it currently pressable
	bool pressable; //PRESSABLE (if present)
	//is it being pressed by the user
	bool pressed;


	UIElement(std::string p, std::string serial)
	{
		path = p;

	}

	UIElement(std::string data)
	{
		Unpack(data);
	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';

		packedfile += "POSITON " + std::to_string(centre.x) + " " + std::to_string(centre.y) + " " + std::to_string(centre.z) + '\n';
		packedfile += "DIMENSIONS " + std::to_string(width) + " " + std::to_string(height) +'\n';
		//Redundant but probably good for readibility in file
		packedfile += "LEFT " + std::to_string(left) + '\n';
		packedfile += "RIGHT " + std::to_string(right) + '\n';
		packedfile += "UP " + std::to_string(up) + '\n';
		packedfile += "DOWN " + std::to_string(down) + '\n';

		packedfile += "MESH " + Mesh + '\n';
		packedfile += "TEXTURE " + texture + '\n';
		packedfile += "HIGHLIGHT " + std::to_string(HighlightTint.x) + " " + std::to_string(HighlightTint.y) + " " + std::to_string(HighlightTint.z) + " " + std::to_string(HighlightTint.w) + '\n';

		if (text != "") {
			packedfile += "TEXT " + text + '\n';
			packedfile += "FONT " + font + " " + std::to_string(fontsize) + '\n';
		}
		if (TalkingHead != "")
			packedfile += "HEAD " + TalkingHead + '\n';
		if (FollowCursor)
			packedfile += "FOLLOW " + std::to_string(followCursorOffset.x) + " " + std::to_string(followCursorOffset.y) + '\n';
		if(pressable)
			packedfile += "PRESSABLE" + '\n';

		for (size_t i = 0; i < Groups.size(); i++)
		{
			packedfile += "GROUP " + Groups.size() + '\n';
		}

		//These always stay at the end when packing
		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}


};






struct TalkingHead : public GameConstruct
{
	std::string texture; //TEXTURE [name] (non-altering use of UISquare)
	glm::vec2 pDimension; //width, height of portrait in pixels. DIMENSIONS [x y]
	std::map<std::string, glm::vec2> Moods; //for each portrait, specify MOOD [name] [bottom and top x & y]


	TalkingHead(std::string data)
	{
		Unpack(data);
	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';

		packedfile += "TEXTURE " + texture;
		packedfile += "DIMENSIONS " + std::to_string(pDimension.x) + " " + std::to_string(pDimension.y) + '\n';

		for(const std::pair<std::string, glm::vec2>& p : Moods)
		{
			packedfile += "MOOD " + p.first + " " + std::to_string(p.second.x) + " " + std::to_string(p.second.y) + '\n';
		}

		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}



		return packedfile;
	}

};



struct WeaponData : public GameConstruct
{
	bool heal; //HEALING (if present)
	//minimum deal
	uint damageMin; //DAMAGE [min] [max]
	//add random range (top this) and level to get damage dealt
	uint damageAdd;
	//Crits work on a roll where if you hit 10 you crit, by default this is the crit score of the attacker and crit score of the weapon minus the crit resistance of the defence, added to a roll of a d6
	uint CritScore;  //CRITSCORE [value]
	//Keywords compared against resistances, if anything left after testing them, then this means the attack is resisted
	std::vector<std::string> Boons; //For each, BOON [name]
	//effect type applied on successful attack.
	std::string Effect; //EFFECT [name]

	WeaponData()
	{
		name = "";
		heal = false;
		damageMin = 0;
		damageAdd = 0;
		CritScore = 0;
		Effect = "";
	}
	WeaponData(std::string n, bool h, uint dm, uint da, uint cr)
	{
		name = n;
		heal = h;
		damageMin = dm;
		damageAdd = da;
		CritScore = cr;
		Effect = "";
	}
	WeaponData(std::string n, bool h, uint dm, uint da, uint cr, std::string e)
	{
		name = n;
		heal = h;
		damageMin = dm;
		damageAdd = da;
		CritScore = cr;
		Effect = e;
	}
	WeaponData(std::string n, bool h, uint dm, uint da, uint cr, std::string e, std::vector<std::string> b)
	{
		name = n;
		heal = h;
		damageMin = dm;
		damageAdd = da;
		CritScore = cr;
		Effect = e;
		Boons = b;
	}
	WeaponData(std::string n, bool h, uint dm, uint da, uint cr, std::vector<std::string> b)
	{
		name = n;
		heal = h;
		damageMin = dm;
		damageAdd = da;
		CritScore = cr;
		Effect = "";
		Boons = b;
	}

	WeaponData(std::string data)
	{
		Unpack(data);
	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		if (heal)
			packedfile += "HEALING" + '\n';
		packedfile += "DAMAGE " + std::to_string(damageMin) + " " + std::to_string(damageMin + damageAdd) + '\n';
		packedfile += "CRITSCORE " + CritScore;
		for (size_t i = 0; i < Boons.size(); i++)
		{
			packedfile += "BOON " + Boons[i] + '\n';
		}
		packedfile += "EFFECT " + Effect + '\n';
		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

};

struct DefenceData : public GameConstruct
{	
	//See Weapondata for how Crits work. This works as a negative to crits.
	uint CritResistance; //CRITRESIST [int]
	//on attack, compare boons against resistances, If there are any boons left, attack does double damage. Resistances can include effect names to cancel an effect
	std::vector<std::string> resistances; //For each, RESISTS [name]


	DefenceData()
	{
		name = "";
		CritResistance = 0;
	}

	DefenceData(std::string n, uint ct)
	{
		name = n;
		CritResistance = ct;
	}

	DefenceData(std::string n, uint ct, std::vector<std::string> res)
	{
		name = n;
		CritResistance = ct;
		resistances = res;
	}

	DefenceData (std::string data)
	{
		Unpack(data);
	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		packedfile += "CRITRESIST " + std::to_string(CritResistance) + '\n';

		for (size_t i = 0; i < resistances.size(); i++)
		{
			packedfile += "RESISTS " + resistances[i] + '\n';
		}

		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

};

struct EffectData : public GameConstruct
{
	//how many rounds to count before it goes
	uint rounds; //ROUNDS [value]
	//effects with higher priority aren't replaced
	uint priority;  //PRIORITY [value]
	//What resistences prevent this effect from happening
	std::vector<std::string>  resistanceBlocks; //For each, BLOCKEDBY [name]
	//what resistences to ignore when this is in effect
	std::vector<std::string>  resistanceDrops; //For each, COUNTERS [name]
	//what resistences to add when this is in effect
	std::vector<std::string>  resistanceAdds; //For each, GRANTS [name]
	//damage over time, if negative, this heals
	int damagePerRound; //ROUNDDAMAGE [value]
	//how much subsequent hits do while this is in effect
	float damageMod; //PAINMOD [value]
	//how much subsequent attacks do while this is in effect
	float attackMod; //ATTACKMOD [value]
	//any crit chance changes to the target's defence and weapon
	float critdefenceMod; //CRITDEF (value) 
	float critattackMod; //CRITATTK (value)


	EffectData()
	{
		name = "";
		rounds = 0;
	}

	EffectData(std::string n, uint r, uint p, int dpr, float dm, float am, std::vector<std::string> rb, std::vector<std::string> rd, std::vector<std::string> ra)
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
	
	EffectData(std::string data)
	{
		Unpack(data);
	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		if (rounds > 1)
			packedfile += "ROUNDS " + std::to_string(rounds) + '\n';
		if (priority > 0)
			packedfile += "PRIORITY " + std::to_string(priority) + '\n';

		for (size_t i = 0; i < resistanceBlocks.size(); i++)
		{
			packedfile += "BLOCKEDBY " + resistanceBlocks[i] + '\n';
		}
		for (size_t i = 0; i < resistanceDrops.size(); i++)
		{
			packedfile += "COUNTERS " + resistanceDrops[i] + '\n';
		}		
		for (size_t i = 0; i < resistanceAdds.size(); i++)
		{
			packedfile += "GRANTS " + resistanceAdds[i] + '\n';
		}

		packedfile += "ROUNDDAMAGE " + std::to_string(damagePerRound) + '\n';
		if (damageMod != 0)
			packedfile += "PAINMOD " + std::to_string(damageMod) + '\n';
		if (attackMod != 0)
			packedfile += "ATTACKMOD " + std::to_string(attackMod) + '\n';
		if (critdefenceMod != 0)
			packedfile += "CRITDEF " + std::to_string(critdefenceMod) + '\n';
		if (critattackMod != 0)
			packedfile += "CRITATTK " + std::to_string(critattackMod) + '\n';

		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}



};

//COMBAT ACTOR
struct ActorData : public GameConstruct
{
	//This is taken into consideration for various things
	int Level;
	//0 = Player Controlled, others correspond to levels of sophistication delivered by the battle engine, defaults to 1 if out of range
	uint AIProfile; //CONTROL [int]
	//graphics stuff
	std::string mesh;//MESH [name]
	std::string texture; //TEXTURE [name]
	//shader
	std::string shader; //SHADER [name]
	//current health
	int healthBar; //STARTHP [int]
	//max state of healthbar
	uint maxHealth;  //MAXHP [int]
	//use for undead I guess?
	bool HealingHurts; //HEALHURTS (if present)
	//current weapon, cross referenced against loaded table
	std::string weaponUsed; //WEAPON [name]
	//current defence, cross referenced against loaded table
	std::string defenceUsed; //DEFENCE [name]
	//what effect is in play
	std::string currentEffect; //STARTFX [name] [int] [int]
	//current effect priority
	int currentEffectPriority;
	//how long the effect has left
	uint currentEffectTurns;
	//Tags that change how much someone with that preference targets them
	std::map<std::string, int> rankedPulls; //PULL [name] [int]
	//Either the above or stuff like LowHealth where it's situational.
	std::map<std::string, int> PulledBy; //PULLEDBY [name] [int];
	//Add points to preference based on which current opponent hurt it the most/last
	uint currentFoeBias[4]; //knight, ranger, wizard, you 


	ActorData()
	{
		name = "";
		mesh = "default";
		shader = "default";
		healthBar = 0;
		maxHealth = 0;
		weaponUsed = "";
		defenceUsed = "";
		currentEffect = "";
		currentEffectTurns = 0;
		for (uint i = 0; i < 4; i++)
		{
			currentFoeBias[i] = 0;
		}
	}

	ActorData(std::string data)
	{
		Unpack(data);
	}

	//NEED TO REMOVE ALL OLD CONSTRUCTORS AT SOME POINT
	ActorData(std::string n, std::string m, std::string s, uint mh, std::string wu, std::string du, std::vector<std::string> pp, std::vector<std::string> cpb)
	{
		name = n;
		mesh = m;
		shader = s;
		healthBar = mh;
		maxHealth = mh;
		weaponUsed = wu;
		defenceUsed = du;
		currentEffect = "";
		currentEffectTurns = 0;
		for (uint i = 0; i < 3; i++)
		{
			if (pp.size() < i)
				rankedPulls.insert({ pp[i], 1 });
		}
		for (uint i = 0; i < 4; i++)
		{
			if (cpb.size() < i)
				currentFoeBias[i] = std::stoi(cpb[i]);
		}

	}

	ActorData(std::string n, std::string m, std::string s, uint mh, std::string wu, std::string du, std::vector<uint> pp, std::vector<uint> cpb)
	{
		name = n;
		mesh = m;
		shader = s;
		healthBar = mh;
		maxHealth = mh;
		weaponUsed = wu;
		defenceUsed = du;
		currentEffect = "";
		currentEffectTurns = 0;

		for (uint i = 0; i < 4; i++)
		{
			if (cpb.size() < i)
				currentFoeBias[i] = cpb[i];
		}

	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		packedfile += "LEVEL " + Level;
		packedfile += "CONTROL " + std::to_string(AIProfile) + '\n';
		packedfile += "MESH " + mesh + '\n';
		packedfile += "TEXTURE " + texture + '\n';
		packedfile += "SHADER " + shader + '\n';
		
		packedfile += "STARTHP " + std::to_string(healthBar) + '\n';
		packedfile += "MAXHP " + std::to_string(maxHealth) + '\n';
		if (HealingHurts)
			packedfile += "HEALHURTS" + '\n';
		
		packedfile += "WEAPON " + weaponUsed + '\n';
		packedfile += "DEFENCE " + defenceUsed + '\n';
		if (currentEffect != "")
			packedfile += "STARTFX " + currentEffect + " " + std::to_string(currentEffectPriority) + " " + std::to_string(currentEffectTurns) + '\n';
		
		
		for (const std::pair<std::string, int>& p : rankedPulls)
		{
			packedfile += "PULL " + p.first + " " + std::to_string(p.second) + '\n';
		}
		for (const std::pair<std::string, int>& p : PulledBy)
		{
			packedfile += "PULLEDBY " + p.first + " " + std::to_string(p.second) + '\n';
		}


		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

	void AddEffect(EffectData &e)
	{
		if (e.priority >= currentEffectPriority) {
			currentEffect = e.name;
			currentEffectTurns = e.rounds;
			currentEffectPriority = e.priority;

		}
	}
};

//This can be used for objects, NPCs, triggers, etc.
struct Bounds : public GameConstruct
{
	//extents, most in given direction
	glm::vec3 centre; //POSITION [x y z]
	float width; //DIMENSIONS [w h]
	float height;
	float left, right, up, down; //name [float]
	//Only interacts with player object if they're within 1m of this floor
	float Floor; //FLOOR [float]

	float modelRot = 0; //YAW [y]
	float modelScale = 1; //SIZE [float]
	std::string type; //TYPE [passable, solid, trigger solid, trigger passable, walk trap]

	//graphics stuff
	std::string mesh;//MESH [name]
	std::string texture; //TEXTURE [name]
	//shader
	std::string shader; //SHADER [name]

	std::string action; //interpreted. Load new scene, load dialog scene, load battle, with note as to whether to overwrite player position

	Bounds(glm::vec3 c, float w, float h, std::string t, std::string m, std::string s, std::string a)
	{
		centre = c;
		width = w;
		height = h;
		left = centre.x - width/2;
		right = centre.x + width / 2;
		up = centre.y + height / 2;
		down = centre.y - height / 2;
		type = t;
		mesh = m;
		shader = s;
		action = a;
	}

	Bounds(float l, float r, float u, float d, std::string t, std::string m, std::string s, std::string a)
	{
		width = abs(r) + abs(l);
		height = abs(u) + abs(d);
		left = l;
		right = r;
		up = u;
		down = d;
		centre = glm::vec3((l + r) / 2, 0, (u + d) / 2);
		type = t;
		mesh = m;
		shader = s;
		action = a;
	}
	Bounds()
	{
		centre = glm::vec3(0, 0, 0);
		width = 2;
		height = 2;
		type = "";
		mesh = "default";
		shader = "default";
		action = "none";
	}

	Bounds(float l, float r, float u, float d)
	{
		width = r - l;
		height = u - d;
		left = l;
		right = r;
		up = u;
		down = d;
		centre = glm::vec3((l + r) / 2, 0, (u + d) / 2);
		name = "LevelBounds";
		type = "";
		mesh = "none";
		shader = "none";
		action = "none";
	}
	
	Bounds(std::string data)
	{
		Unpack(data);
	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';

		packedfile += "POSITON " + std::to_string(centre.x) + " " + std::to_string(centre.y) + " " + std::to_string(centre.z) + '\n';
		packedfile += "DIMENSIONS " + std::to_string(width) + " " + std::to_string(height) + '\n';
		//Redundant if both are included but probably good for readibility in file
		packedfile += "LEFT " + std::to_string(left) + '\n';
		packedfile += "RIGHT " + std::to_string(right) + '\n';
		packedfile += "UP " + std::to_string(up) + '\n';
		packedfile += "DOWN " + std::to_string(down) + '\n';

		packedfile += "FLOOR " + std::to_string(Floor) + '\n';
		if (modelRot != 0)
			packedfile += "YAW " + std::to_string(modelRot) + '\n';
		if (modelScale != 1)
			packedfile += "SIZE " + std::to_string(modelScale) + '\n';

		packedfile += "MESH " + mesh + '\n';
		packedfile += "TEXTURE " + texture + '\n';
		packedfile += "SHADER " + shader + '\n';

		packedfile += "TYPE " + type + '\n';
		packedfile += "ACTION" + action + '\n';

		//These always stay at the end when packing
		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

};
struct BattleData : public GameConstruct
{

	//is there a starting effect applied to everyone?
	std::string startEff; //STARTFX [name]
	//collects foes, either spawned from name or draw from playerdata
	std::vector<std::string> Team0; //TEAM [0] [enemy name]
	std::vector<std::string> Team1; //TEAM [1] PARTY [int]

	//Controller Slots for each team, defaults to -1 (NPC), though any variable not 0 or 1 is NPC.
	int Team0Slot; //TEAM [0] 0
	int Team1Slot; //TEAM [1] NPC

	BattleData()
	{
		name = "";
		startEff = "";
	}

	BattleData(std::string data)
	{
		Unpack(data);
	}


	BattleData(std::string n, std::string s, std::vector<std::string> f)
	{
		name = n;
		startEff = s;
		Team0.push_back("Playerdata0");
		Team0.push_back("Playerdata1");
		Team0.push_back("Playerdata2");
		Team0.push_back("Playerdata3");
		Team1 = f;
	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		packedfile += "STARTFX " + startEff + '\n';

		if(Team0Slot = -1)
			packedfile += "TEAM 0 NPC" + '\n';
		else
			packedfile += "TEAM 0 " + std::to_string(Team0Slot) + '\n';
		for (size_t i = 0; i < Team0.size(); i++)
		{
			packedfile += "TEAM 0 " + Team0[i] + '\n';
		}

		if (Team1Slot = -1)
			packedfile += "TEAM 1 NPC" + '\n';
		else
			packedfile += "TEAM 1 " + std::to_string(Team1Slot) + '\n';
		for (size_t i = 0; i < Team1.size(); i++)
		{
			packedfile += "TEAM 1 " + Team1[i] + '\n';
		}

		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

};

struct UIData : public GameConstruct
{
	//orthographic worldbox for the UI; 
	int width; //DIMENSIONS [w h]
	int height;

	std::vector<UIElement> elements; //ELEMENT [code] *

	UIData(std::string data)
	{
		Unpack(data);
	}

	void Unpack(std::string data);
	
	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		packedfile += "DIMENSIONS " + std::to_string(width) + " " + std::to_string(height) + '\n';

		for (size_t i = 0; i < elements.size(); i++)
		{
			packedfile += "ELEMENT" + '\n';
			packedfile += elements[i].Pack();
			packedfile += "\n**\n";
		}

		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

};

struct SceneData : public GameConstruct
{
	//UI to bring with the scene. "inherit" keyword keeps the last one and leaving it blank clears the UI entirely
	std::string UILoad; //UI [name]
	//Generated Bounds object to keep player within
	Bounds limits; //LIMITS [left, right, up, down, floor]
	bool Limited; //True unless keyword UNLIMITED or no limits provided


	//Walls, NPCs, Pickups, Triggers
	std::vector<Bounds> Objects; //BOUNDS [code] *


	int activeplayers; //PLAYERS [int]  Default 1, can be 2, any other number is 0
	glm::vec2 StartingPos0; //PLAYER [int] [x y z]
	glm::vec2 StartingPos1;


	SceneData()
	{
		name = "";
		UILoad = "inherit";
		limits = Bounds();
	}

	SceneData(std::string n, Bounds l, std::vector<Bounds> o, std::vector<glm::vec2> sp)
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


	}

	SceneData(std::string n, Bounds l, Bounds o[16], glm::vec2 sp[4])
	{
		name = n;
		limits = l;
		for (uint i = 0; i < 16; i++)
		{
			Objects[i] = o[i];
		}


	}

	SceneData(std::string data)
	{
		Unpack(data);
	}

	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		packedfile += "UI " + UILoad + '\n';
		if (!Limited)
			packedfile += "UNLIMITED" + '\n';

		packedfile += "LIMITS " + std::to_string(limits.left) + " " + std::to_string(limits.right) + " " + std::to_string(limits.up) + " " + std::to_string(limits.down) + '\n';

		for (size_t i = 0; i < Objects.size(); i++)
		{
			packedfile += "BOUNDS" + '\n';
			packedfile += Objects[i].Pack();
			packedfile += "\n**\n";
		}

		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

};

//THIS IS LIKELY TO BE CHANGED BASED ON GAME RPG ENGINE NEEDS
struct PlayerData : public GameConstruct
{
	uint saveFileNom; //SAVESLOT [int]

	//Scene to load game into
	std::string CurrentScene = ""; //SCENE [name]
	std::string CurrentUI = ""; //UI [name]

	//Total number of collected dice
	uint diceCount = 0; //DICE [int]


	//Our characters
	std::vector<ActorData> Party; //CHARACTER [data] *

	std::vector<std::string> Arsenal; //WEAPON [name]
	std::vector<std::string> Armoury; //ARMOUR [name]
	//Need to adjust this for arbitrary party size if the engine will support more games. Potentially in ActorData
	uint friendship[3] = { 0, 0, 0 }; //knight, ranger, wizard. FRIENDVALUE [index] [int]

	//saved position on map
	glm::vec3 Position; //POSITION [x, y, z]

	//tags that are saved throughout the game, regardless of if you save and quit
	std::vector<SceneTag> SavedIndefiniteTags;

	PlayerData()
	{
		saveFileNom = 0;
		CurrentScene = "Menu";
		CurrentUI = "Menu";
	}

	PlayerData(std::string data)
	{
		Unpack(data);
	}


	void Unpack(std::string data);

	std::string Pack()
	{
		std::string packedfile;
		packedfile += "NAME " + name + '\n';
		if (ReadOnly)
			packedfile += "READONLY" + '\n';
		if (Altering)
			packedfile += "ALTERING" + '\n';
		packedfile += "SAVESLOT " + std::to_string(saveFileNom) + '\n';
		packedfile += "SCENE " + CurrentScene + '\n';
		packedfile += "UI " + CurrentScene + '\n';
		packedfile += "DICE " + std::to_string(diceCount) + '\n';
		for (size_t i = 0; i < Arsenal.size(); i++)
		{
			packedfile += "WEAPON " + Arsenal[i] + '\n';
		}
		for (size_t i = 0; i < Armoury.size(); i++)
		{
			packedfile += "ARMOUR " + Armoury[i] + '\n';
		}
		for (size_t i = 0; i < 3; i++)
		{
			packedfile += "FRIENDVALUE " + std::to_string(i) + " " + std::to_string(friendship[i]);
		}
		for (size_t i = 0; i < Party.size(); i++)
		{
			packedfile += "CHARACTER\n" + Party[i].Pack() + "\n**\n";
		}
		packedfile += "POSITION " + std::to_string(Position.x) + " " + std::to_string(Position.y) + " " + std::to_string(Position.z) + '\n';

		for (size_t i = 0; i < SavedIndefiniteTags.size(); i++)
		{
			packedfile += "SAVEDTAG " + std::to_string(SavedIndefiniteTags[i].lifetime) + " " + pingTag.contents + '\n';

		}

		packedfile += "PING " + std::to_string(pingTag.lifetime) + " " + pingTag.contents + '\n';
		if (AttachedScript.size() > 0)
		{
			packedfile += '\n' + "CODE:" + '\n';
			packedfile += AttachedScript;
			packedfile += "\n*";
		}

		return packedfile;
	}

};


#endif // !GameConstructs
