#pragma once

#ifndef DEFRENDER
#define DEFRENDER "RENDERHELPER"


#include "Environment.h"

void DrawMesh(Environment &environment, Bounds b)
{
	//returns default if not present
	environment.GetMesh(b.mesh).Draw(environment.GetShader(b.shader), b.centre, b.modelRot, environment.globalProjection, environment.globalView);

}

void DrawMesh(Environment &environment, ActorData e, glm::vec3 p)
{

	//returns default if not present
	environment.GetMesh(e.mesh).Draw(environment.GetShader(e.shader), p, glm::half_pi<float>(), environment.globalProjection, environment.globalView);

}

void DrawText(Environment &environment, std::string text, std::string font, glm::vec3 loc, glm::vec3 scale, glm::vec4 color)
{
	environment.FontMesh.DrawFont(text, environment.GetFont(font), environment.FontShader, environment.UIOrtho, environment.globalView, loc, scale, color);
}


void DrawFB(Environment& environment, FrameBuffer buffer, std::string shader)
{
	glViewport(0, 0, environment.Wwidth, environment.Wheight);
	buffer.mesh.DrawFB(environment.GetShader(shader), environment.wRatioAdjust, environment.hRatioAdjust, environment.gameOrtho, environment.postView, buffer.id, 0, buffer.texID);
}

void DrawFB(Environment& environment, FrameBuffer& buffer, std::string shader, FrameBuffer& targetbuffer)
{
	glViewport(0, 0, targetbuffer.Width, targetbuffer.Height);
	buffer.mesh.DrawFB(environment.GetShader(shader), environment.wRatioAdjust, environment.hRatioAdjust, environment.gameOrtho, environment.postView, buffer.id, targetbuffer.id, buffer.texID);
}

void DrawBattle()
{
}
#endif // !DEFRENDER
