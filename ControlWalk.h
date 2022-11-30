#pragma once
#include "Environment.h"
#include "RenderHelpers.h"



void Draw(Environment& environment)
{
	glm::vec3 plannedstep = glm::vec3(environment.InputWASD.x, 0, environment.InputWASD.y);
	if(!environment.MovementPhysicsLocked)
		PhysicsStep(environment, plannedstep);

	DrawMesh(environment, environment.CurrentScene.limits);
	for (uint i = 0; i < environment.CurrentScene.Objects.size(); i++)
	{
		DrawMesh(environment, environment.CurrentScene.Objects[i]);
	}


}

glm::vec3 newpos;


void PhysicsStep(Environment& environment, glm::vec3 input)
{ 
	if (environment.MovementInputLocked)
		input = glm::vec3(0, 0, 0);
		

	glm::vec3 move = input * environment.playerSpeed;
	glm::vec3 maxmove = move;
	newpos = environment.PlayerPos + move;
	for (uint i = 0; i < environment.CurrentScene.Objects.size(); i++)
	{
		while(AABBIntersectsPlayer(environment, environment.CurrentScene.Objects[i], newpos))
		{
			move -= maxmove * 0.1f;
			newpos = environment.PlayerPos + move;

		}
	}
	
	//keep within level bounds
	if (newpos.y > environment.CurrentScene.limits.up)
		newpos.y = environment.CurrentScene.limits.up;
	else if (newpos.y < environment.CurrentScene.limits.down)
		newpos.y = environment.CurrentScene.limits.down;

	if (newpos.x > environment.CurrentScene.limits.right)
		newpos.x = environment.CurrentScene.limits.right;
	else if (newpos.x < environment.CurrentScene.limits.left)
		newpos.x = environment.CurrentScene.limits.left;

	environment.PlayerPos = newpos;

}

bool AABBIntersectsPlayer(Environment& environment, Bounds b, glm::vec3 pos)
{
	if (b.type == "passable")
		return;

	glm::vec3 dist = glm::vec3(pos.x - b.centre.x, 0, pos.y - b.centre.y);

	if (dist.x > (b.width / 2 + environment.playerCollisionRadius))
		return false;
	if (dist.y > (b.height / 2 + environment.playerCollisionRadius))
		return false;
	
	if (dist.x <= (b.width / 2))
		return true;
	if (dist.y <= (b.height / 2)) 
		return true;

	float cornerDistance_sq = pow((dist.x - b.width / 2),2) + pow((dist.y - b.height / 2), 2);

	return (cornerDistance_sq <= pow(environment.playerCollisionRadius, 2));
}