#pragma once
#include "framebuffering.h"

FrameBuffer::FrameBuffer(int width, int height, GLenum scaleMode, Mesh square)
{
	ScalingMode = scaleMode;
	mesh = Mesh(square);
	mesh.texture = Texture(width, height, scaleMode);

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mesh.texture.id, 0);

	glGenRenderbuffers(1, &DSrbo);
	glBindRenderbuffer(GL_RENDERBUFFER, DSrbo);
	glNamedRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, DSrbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::FrameBuffer()
{
	ScalingMode = GL_POINT;
	mesh = Mesh();
	mesh.texture = Texture(640, 480, GL_POINT);
}

void FrameBuffer::Resize(int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, mesh.texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, DSrbo);
	glNamedRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);



}

void FrameBuffer::Use()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}