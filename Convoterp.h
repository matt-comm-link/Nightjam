#pragma once

#include "Environment.h"
#include "RenderHelpers.h"

//List of functions that interpret convoscript instructions to display a conversation

//return true if new keyword is added
bool AddKeyword(string kword)
{
	bool retBol = true;
	for (int i = 0; i < CurrentSave.tagsAmassed.size(); i++)
	{
		if (kword == CurrentSave.tagsAmassed[i])
			retBol = false;
	}
	if (retBol)
		CurrentSave.tagsAmassed.push_back(kword);
	return retBol;
}

//return true if keyword is already in list
bool CheckKeyword(string kword)
{
	for (int i = 0; i < CurrentSave.tagsAmassed.size(); i++)
	{
		if (kword == CurrentSave.tagsAmassed[i])
			return true;
	}
	return false;
}