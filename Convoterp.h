#pragma once

#include "Environment.h"
#include "RenderHelpers.h"

//List of functions that interpret convoscript instructions to display a conversation

//return true if new keyword is added
bool AddKeyword(Environment &environment, std::string kword)
{
	bool retBol = true;
	for (int i = 0; i < environment.CurrentSave.SavedIndefiniteTags.size(); i++)
	{
		if (kword == environment.CurrentSave.SavedIndefiniteTags[i].contents)
			retBol = false;
	}
	if (retBol)
		environment.CurrentSave.SavedIndefiniteTags.push_back(SceneTag(1, kword));
	return retBol;
}

//return true if keyword is already in list
bool CheckKeyword(Environment& environment, std::string kword)
{
	for (int i = 0; i < environment.CurrentSave.SavedIndefiniteTags.size(); i++)
	{
		if (kword == environment.CurrentSave.SavedIndefiniteTags[i].contents)
			return true;
	}
	return false;
}