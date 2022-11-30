#pragma once
#include "mesh.h"

class FrameBuffer
{
public:
	uint id;
	uint texID;
	Mesh mesh;
	uint DSrbo;
	GLenum ScalingMode;
	int Width;
	int Height;

	FrameBuffer(int width, int height, GLenum scaleMode, Mesh &square);
	FrameBuffer();

	void Resize(int width, int height);
	void Use();
};

