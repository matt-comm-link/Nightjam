#include "framebuffering.h"

FrameBuffer::FrameBuffer(int width, int height, GLenum scaleMode, Mesh &square)
{
	
	Width = width;
	Height = height;
	
	ScalingMode = scaleMode;
	mesh = square;
	//mesh.texture = Texture(width, height, scaleMode);


	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		cout << "ERROR::OPENGL:: Opengl errors going into the fb: " << err << endl;
		cout << "WH: " << width << ", " << height << endl;
		cout << "render texture index: " << texID << endl;
	}
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ScalingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ScalingMode);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texID, 0);
	mesh.texture.id = texID;

	glGenRenderbuffers(1, &DSrbo);
	glBindRenderbuffer(GL_RENDERBUFFER, DSrbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, DSrbo);
	auto fbostatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	auto glerror = glGetError();
	
	if (fbostatus != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete! " << fbostatus << " " << glerror << endl;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		cout << "ERROR::OPENGL:: Opengl errors after the fb: " << err << " WH: " << width << ", " << height << endl;
	}


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

FrameBuffer::FrameBuffer()
{
	ScalingMode = GL_POINT;
	mesh = Mesh();
	mesh.texture = Texture();
}


void FrameBuffer::Resize(int width, int height)
{
	Width = width;
	Height = height;

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mesh.texture.id, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, DSrbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, DSrbo);

	auto fbostatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	auto glerror = glGetError();
	if (fbostatus != GL_FRAMEBUFFER_COMPLETE)
		cout << "RESIZE ERROR::FRAMEBUFFER:: Framebuffer is not complete! " << fbostatus << " " << glerror << endl;


}

void FrameBuffer::Use()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, Width, Height);

}