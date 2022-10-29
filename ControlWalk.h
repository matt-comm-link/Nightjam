#pragma once
#include "Environment.h"
#include "RenderHelpers.h"



void Draw()
{

	if(!MovementPhysicsLocked)
		PhysicsStep(glm::vec3(InputWASD.x, 0, InputWASD.y));

	DrawMesh(CurrentScene.limits);
	for (uint i = 0; i < CurrentScene.Objects.size(); i++)
	{
		DrawMesh(CurrentScene.Objects[i]);
	}


}

glm::vec3 newpos;


void PhysicsStep(glm::vec3 input)
{ 
	if (MovementInputLocked)
		input = glm::vec3(0, 0, 0);
		

	glm::vec3 move = input * playerSpeed;
	glm::vec3 maxmove = move;
	newpos = PlayerPos + move;
	for (uint i = 0; i < CurrentScene.Objects.size(); i++)
	{
		while(AABBIntersectsPlayer(CurrentScene.Objects[i], newpos))
		{
			move -= maxmove * 0.1f;
			newpos = PlayerPos + move;

		}
	}
	
	//keep within level bounds
	if (newpos.y > CurrentScene.limits.up)
		newpos.y = CurrentScene.limits.up;
	else if (newpos.y < CurrentScene.limits.down)
		newpos.y = CurrentScene.limits.down;

	if (newpos.x > CurrentScene.limits.right)
		newpos.x = CurrentScene.limits.right;
	else if (newpos.x < CurrentScene.limits.left)
		newpos.x = CurrentScene.limits.left;

	PlayerPos = newpos;

}

bool AABBIntersectsPlayer(Bounds b, glm::vec3 pos)
{
	if (b.type == "passable")
		return;

	glm::vec3 dist = glm::vec3(pos.x - b.centre.x, 0, pos.y - b.centre.y);

	if (dist.x > (b.width / 2 + playerCollisionRadius))
		return false;
	if (dist.y > (b.height / 2 + playerCollisionRadius))
		return false;
	
	if (dist.x <= (b.width / 2))
		return true;
	if (dist.y <= (b.height / 2)) 
		return true;

	float cornerDistance_sq = pow((dist.x - b.width / 2),2) + pow((dist.y - b.height / 2), 2);

	return (cornerDistance_sq <= pow(playerCollisionRadius, 2));
}