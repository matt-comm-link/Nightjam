#pragma once

#include "Environment.h"
#include "RenderHelpers.h"

//List of functions that interpret convoscript instructions to display a conversation

//return true if new keyword is added
bool AddKeyword(Environment &environment, string kword)
{
	bool retBol = true;
	for (int i = 0; i < environment.CurrentSave.tagsAmassed.size(); i++)
	{
		if (kword == environment.CurrentSave.tagsAmassed[i])
			retBol = false;
	}
	if (retBol)
		environment.CurrentSave.tagsAmassed.push_back(kword);
	return retBol;
}

//return true if keyword is already in list
bool CheckKeyword(Environment& environment, string kword)
{
	for (int i = 0; i < environment.CurrentSave.tagsAmassed.size(); i++)
	{
		if (kword == environment.CurrentSave.tagsAmassed[i])
			return true;
	}
	return false;
}