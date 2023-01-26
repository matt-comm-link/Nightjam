#pragma once
#ifndef DEFCONSTRUCTCPP

#define DEFCONSTRUCTCPP "CONSTRUCTCPP"
#include "GameConstructs.h"
#ifndef DEFLOADERCPP
#include "stringtools.h"
#endif


void GameConstruct::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}


void UIElement::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;
	pressable = false;
	FollowCursor = false;

	Mesh = "uisquare";
	texture = "default";

	centre = glm::vec3(0, 0, 0);
	bool UsePosition = false;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "POSITION")
			{
				centre = glm::vec3(std::stof(splitted[1]), std::stof(splitted[2]), std::stof(splitted[3]));
				UsePosition = true;
				width = 1;
				height = 1;
			}
			else if (splitted[0] == "DIMENSIONS")
			{
				UsePosition = true;
				width = std::stof(splitted[1]);
				height = std::stof(splitted[2]);
			}
			else if (splitted[0] == "LEFT")
			{
				if (!UsePosition)
					left = std::stof(splitted[1]);
			}
			else if (splitted[0] == "RIGHT")
			{
				if (!UsePosition)
					right = std::stof(splitted[1]);
			}
			else if (splitted[0] == "UP")
			{
				if (!UsePosition)
					up = std::stof(splitted[1]);
			}
			else if (splitted[0] == "DOWN")
			{
				if (!UsePosition)
					down = std::stof(splitted[1]);
			}
			else if (splitted[0] == "MESH")
			{
				Mesh = splitted[1];
			}
			else if (splitted[0] == "TEXTURE")
			{
				texture = splitted[1];
			}
			else if (splitted[0] == "HIGHLIGHT")
			{
				HighlightTint = glm::vec4(std::stof(splitted[1]), std::stof(splitted[2]), std::stof(splitted[3]), std::stof(splitted[4]));
			}
			else if (splitted[0] == "TEXT")
			{
				textOffset = glm::vec2(std::stof(splitted[1]), std::stof(splitted[2]));
				text = splitted[3];
			}
			else if (splitted[0] == "FONT")
			{
				font = splitted[1];
				fontsize = std::stof(splitted[2]);
			}
			else if (splitted[0] == "HEAD")
			{
				TalkingHead = splitted[1];
				Mood = "default";
			}
			else if (splitted[0] == "FOLLOW")
			{
				FollowCursor = true;
				FollowingCursor = true;
				followCursorOffset = glm::vec2(std::stof(splitted[1]), std::stof(splitted[2]));
			}
			else if (splitted[0] == "PRESSABLE")
			{
				pressable = true;
			}
			else if (splitted[0] == "GROUP")
			{
				Groups.push_back(splitted[1]);
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}

	}
	if (UsePosition)
	{
		//work out lrud based on stuff

		left = centre.x - (width / 2);
		right = centre.x + (width / 2);
		up = centre.y + (height / 2);
		down = centre.y - (height / 2);


	}
	else
	{
		//work out centre and wh based on stuff

		centre.x = (left + right) / 2;
		centre.y = (up + down) / 2;

		width = right - left;
		height = up - down;


	}


}

void TalkingHead::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "TEXTURE")
			{
				texture = splitted[1];
			}
			else if (splitted[0] == "DIMENSIONS")
			{
				pDimension = glm::vec2(std::stof(splitted[1]), std::stof(splitted[2]));
			}
			else if (splitted[0] == "MOOD")
			{
				Moods.insert({ splitted[1], glm::vec2(std::stof(splitted[2]), std::stof(splitted[3])) });
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}
}


void WeaponData::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;
	heal = false;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "HEALING")
			{
				heal = true;
			}
			else if (splitted[0] == "DAMAGE")
			{
				damageMin = std::stoi(splitted[1]);
				damageAdd = std::stoi(splitted[2]) - damageMin;
			}
			else if (splitted[0] == "CRITSCORE")
			{
				CritScore = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "BOON")
			{
				Boons.push_back(splitted[1]);
			}
			else if (splitted[0] == "EFFECT")
			{
				Effect = splitted[1];
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}


void DefenceData::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "CRITRESIST")
			{
				CritResistance = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "RESISTS")
			{
				resistances.push_back(splitted[1]);
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}


void EffectData::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;
	priority = 0;
	rounds = 1;


	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "ROUNDS")
			{
				rounds = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "PRIORITY")
			{
				priority = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "BLOCKEDBY")
			{
				resistanceBlocks.push_back(splitted[1]);
			}
			else if (splitted[0] == "COUNTERS")
			{
				resistanceDrops.push_back(splitted[1]);
			}
			else if (splitted[0] == "GRANTS")
			{
				resistanceAdds.push_back(splitted[1]);
			}
			else if (splitted[0] == "ROUNDDAMAGE")
			{
				damagePerRound = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "PAINMOD")
			{
				damageMod = std::stof(splitted[1]);
			}
			else if (splitted[0] == "ATTACKMOD")
			{
				attackMod = std::stof(splitted[1]);
			}
			else if (splitted[0] == "CRITDEF")
			{
				critdefenceMod = std::stof(splitted[1]);
			}
			else if (splitted[0] == "CRITATTK")
			{
				critattackMod == std::stof(splitted[1]);
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}


void ActorData::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;
	AIProfile = 1;
	maxHealth = 10;
	healthBar = 10;
	HealingHurts = false;
	mesh = "default";
	texture = "default";
	shader = "default";


	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "CONTROL")
			{
				AIProfile = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "MESH")
			{
				mesh = splitted[1];
			}
			else if (splitted[0] == "TEXTURE")
			{
				texture = splitted[1];
			}
			else if (splitted[0] == "SHADER")
			{
				shader = splitted[1];
			}
			else if (splitted[0] == "STARHP")
			{
				healthBar = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "MAXHP")
			{
				maxHealth = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "HEALHURTS")
			{
				HealingHurts = true;
			}
			else if (splitted[0] == "WEAPON")
			{
				weaponUsed = splitted[1];
			}
			else if (splitted[0] == "DEFENCE")
			{
				defenceUsed = splitted[1];
			}
			else if (splitted[0] == "STARTFX")
			{
				currentEffect = splitted[1];
				currentEffectPriority = std::stoi(splitted[2]);
				currentEffectTurns = std::stoi(splitted[3]);
			}
			else if (splitted[0] == "PULL")
			{
				rankedPulls.insert({ splitted[1], std::stoi(splitted[2]) });
			}
			else if (splitted[0] == "PULLEDBY")
			{
				PulledBy.insert({ splitted[1], std::stoi(splitted[2]) });
			}
			else if (splitted[0] == "LEVEL")
			{
				Level = std::stoi(splitted[1]);
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}

void Bounds::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;

	mesh = "default";
	texture = "default";
	shader = "default";

	centre = glm::vec3(0, 0, 0);
	bool UsePosition = false;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try
		{
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "POSITION")
			{
				centre = glm::vec3(std::stof(splitted[1]), std::stof(splitted[2]), std::stof(splitted[3]));
				UsePosition = true;
				width = 1;
				height = 1;
			}
			else if (splitted[0] == "DIMENSIONS")
			{
				UsePosition = true;
				width = std::stof(splitted[1]);
				height = std::stof(splitted[2]);
			}
			else if (splitted[0] == "LEFT")
			{
				if (!UsePosition)
					left = std::stof(splitted[1]);
			}
			else if (splitted[0] == "RIGHT")
			{
				if (!UsePosition)
					right = std::stof(splitted[1]);
			}
			else if (splitted[0] == "UP")
			{
				if (!UsePosition)
					up = std::stof(splitted[1]);
			}
			else if (splitted[0] == "DOWN")
			{
				if (!UsePosition)
					down = std::stof(splitted[1]);
			}
			else if (splitted[0] == "FLOOR")
			{
				Floor = std::stof(splitted[1]);
			}
			else if (splitted[0] == "YAW")
			{
				modelRot = std::stof(splitted[1]);
			}
			else if (splitted[0] == "SIZE")
			{
				modelScale == std::stof(splitted[1]);
			}
			else if (splitted[0] == "MESH")
			{
				mesh = splitted[1];
			}
			else if (splitted[0] == "TEXTURE")
			{
				texture = splitted[1];
			}
			else if (splitted[0] == "SHADER")
			{
				shader = splitted[1];
			}
			else if (splitted[0] == "TYPE")
			{
				type = splitted[1];
			}
			else if (splitted[0] == "ACTION")
			{
				action = splitted[1];
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}

	}
	if (UsePosition)
	{
		//work out lrud based on stuff

		left = centre.x - (width / 2);
		right = centre.x + (width / 2);
		up = centre.y + (height / 2);
		down = centre.y - (height / 2);


	}
	else
	{
		//work out centre and wh based on stuff

		centre.x = (left + right) / 2;
		centre.y = (up + down) / 2;

		width = right - left;
		height = up - down;


	}


}


void UIData::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "DIMENSIONS")
			{
				width = std::stoi(splitted[1]);
				height = std::stoi(splitted[2]);
			}
			else if (splitted[0] == "ELEMENT")
			{
				//repack into std::string for loading from 
				std::string elpacked;
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "**")
					{
						if (elpacked.size() > 0)
							elpacked.pop_back();
						i++;
						break;
					}
					elpacked += LoadData[i] + '\n';
				}
				//FIX THIS
				elements.push_back(UIElement(elpacked));

			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}


void BattleData::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;
	Team0Slot = 0;
	Team1Slot = -1;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "STARTFX")
			{
				startEff = splitted[1];
			}
			else if (splitted[0] == "TEAM")
			{
				if (splitted[1] == "0")
				{
					if (splitted[2] == "NPC")
					{
						Team0Slot = -1;
					}
					else if (splitted[2] == "0")
					{
						Team0Slot = 0;
					}
					else if (splitted[2] == "1")
					{
						Team0Slot = 1;
					}
					else if (splitted[2] == "PARTY")
					{
						if (Team0.size() < 4)
							Team0.push_back("PARTY " + splitted[3]);
					}
					else
					{
						if (Team0.size() < 4)
							Team0.push_back(splitted[2]);
					}
				}
				else
				{
					if (splitted[2] == "NPC")
					{
						Team1Slot = -1;
					}
					else if (splitted[2] == "0")
					{
						Team1Slot = 0;
					}
					else if (splitted[2] == "1")
					{
						Team1Slot = 1;
					}
					else if (splitted[2] == "PARTY")
					{
						if (Team1.size() < 4)
							Team1.push_back("PARTY" + splitted[3]);
					}
					else
					{
						if (Team1.size() < 4)
							Team1.push_back(splitted[2]);
					}
				}
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}

void SceneData::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;
	Limited = true;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "UI")
			{
				UILoad = splitted[1];
			}
			else if (splitted[0] == "LIMITS")
			{
				//create a special bounds constructor here?
				limits = Bounds(std::stof(splitted[1]), std::stof(splitted[2]), std::stof(splitted[3]), std::stof(splitted[4]));
			}
			else if (splitted[0] == "UNLIMITED")
			{
				Limited = false;
			}
			else if (splitted[0] == "BOUNDS")
			{
				//repack into std::string for loading from 
				std::string bpacked;
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "**")
					{
						if (bpacked.size() > 0)
							bpacked.pop_back();
						i++;
						break;
					}
					bpacked += LoadData[i] + '\n';
				}
				//FIX THIS
				Objects.push_back(Bounds(bpacked));
			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}


void PlayerData::Unpack(std::string data)
{
	name = "unnamed";
	ReadOnly = false;
	Altering = false;

	std::vector<std::string> LoadData = split(data, '\n');
	for (size_t i = 0; i < LoadData.size(); i++)
	{
		std::vector<std::string> splitted = split(LoadData[i], ' ');
		try {
			if (splitted[0] == "NAME")
			{
				name = splitted[1];
			}
			else if (splitted[0] == "READONLY")
			{
				ReadOnly = true;
			}
			else if (splitted[0] == "ALTERING")
			{
				Altering = true;
			}
			else if (splitted[0] == "PING")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				pingTag = SceneTag(std::stof(splitted[1]), remains);
			}
			else if (splitted[0] == "CODE:")
			{
				//stored as one line breaked std::string rather than a std::vector of strings, as that seems more clean.
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "*")
					{
						if (AttachedScript.size() > 0)
							AttachedScript.pop_back();
						i++;
						break;
					}
					AttachedScript += LoadData[i] + '\n';
				}

			}
			else if (splitted[0] == "SAVESLOT")
			{
				saveFileNom = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "SCENE")
			{
				CurrentScene = splitted[1];
			}
			else if (splitted[0] == "UI")
			{
				CurrentUI = splitted[1];
			}
			else if (splitted[0] == "DICE")
			{
				diceCount = std::stoi(splitted[1]);
			}
			else if (splitted[0] == "WEAPON")
			{
				Arsenal.push_back(splitted[1]);
			}
			else if (splitted[0] == "ARMOUR")
			{
				Armoury.push_back(splitted[1]);
			}
			else if (splitted[0] == "FRIENDVALUE")
			{
				friendship[std::stoi(splitted[1])] = std::stoi(splitted[2]);
			}
			else if (splitted[0] == "POSITION")
			{
				Position = glm::vec3(std::stof(splitted[1]), std::stof(splitted[2]), std::stof(splitted[3]));
			}
			else if (splitted[0] == "SAVEDTAG")
			{
				std::string remains;
				for (size_t a = 2; a < splitted.size(); a++)
				{
					remains += splitted[a];
					if (a + 1 < splitted.size())
						remains += " ";
				}
				SavedIndefiniteTags.push_back(SceneTag(std::stof(splitted[1]), remains));
			}
			else if (splitted[0] == "CHARACTER")
			{
				//repack into std::string for loading from 
				std::string elpacked;
				while (i < LoadData.size())
				{
					i++;
					if (LoadData[i] == "**")
					{
						if (elpacked.size() > 0)
							elpacked.pop_back();
						i++;
						break;
					}
					elpacked += LoadData[i] + '\n';
				}
				//FIX THIS
				Party.push_back(ActorData(elpacked));

			}
		}
		catch (std::exception e)
		{
			std::cout << "Error loading file at line " << LoadData[i] << '\n';
		}
	}


}


#endif // !DEFCONSTRUCTCPP
