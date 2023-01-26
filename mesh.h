#pragma once


#ifndef DefMesh

#define DefMesh "MESH"



#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#ifndef FTBUILD
#define FTBUILD

#include <ft2build.h>
#include FT_FREETYPE_H    
#endif // !FTBUILD

#include <iostream>
#include <string>
#include <vector>
#include "shader.h"
#include <map>


#ifndef MAX_BONE_INFLUENCE
#define MAX_BONE_INFLUENCE 4

#endif // !MAX_BONE_INFLUENCE

#ifndef uint
#define uint unsigned int
#endif // !uint
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
	glm::vec4 Color;

	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];

	Vertex(float input[])
	{
		Position = glm::vec3(input[0], input[1], input[2]);
		Normal = glm::vec3(input[3], input[4], input[5]);
		UV = glm::vec2(input[6], input[7]);
		Color = glm::vec4(input[8], input[9], input[10], input[11]);

	}

	Vertex(glm::vec3 p, glm::vec2 uv, glm::vec4 c)
	{
		Position = p;
		Normal = glm::vec3(1, 1, 1);
		UV = uv;
		Color = c;

	}
	Vertex(glm::vec3 p, glm::vec2 uv)
	{
		Position = p;
		Normal = glm::vec3(1, 1, 1);
		UV = uv;
		Color = glm::vec4(1, 1, 1, 1);

	}

	Vertex()
	{
		Position = glm::vec3(0, 0, 0);
		Normal = glm::vec3(0, 0, 0);
		UV = glm::vec2(0, 0);
		Color = glm::vec4(0, 0, 0, 0);

	}
};


struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
	unsigned char* storedData;
	int swidth, sheight, schan;

	Texture()
	{
		id = -1;
	}

	Texture(std::string name, unsigned char* data, int width, int height, int nrChannels)
	{
		path = name;
		storedData = data;
		swidth = width;
		sheight = height;
		schan = nrChannels;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (!data)
			std::cout << "whoopsie" << '\n';

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture(std::string name, int width, int height, GLenum scalemode)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, scalemode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, scalemode);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture(std::string name, FT_Face &face)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	}

	Texture(int exid)
	{
		id = exid;
	}
};


struct Character
{
	Texture tex;
	glm::vec2 size;
	glm::vec2 bearing;
	uint advance;

	Character()
	{
		tex = Texture();
		size = glm::vec2(0, 0);
		bearing = glm::vec2(0, 0);
		advance = 0;
	}

	Character(Texture t, glm::vec2 s, glm::vec2 b, uint a)
	{
		tex = t;
		size = s;
		bearing = b;
		advance = a;
	}
};

class Mesh
{

private:
	uint VBO, EBO;

public:
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	Texture texture;

	//use default if not available
	std::string PreferredShader;

	GLenum usage = GL_STATIC_DRAW;
	uint VAO;

	glm::vec4 MapPosition = glm::vec4(0,0,1,1);

	bool unusable = false;

	bool built = false;


	Mesh(std::vector<Vertex> verts, std::vector<uint> inds, Texture &tex )
	{
		vertices = verts;
		indices = inds;
		texture = tex;

		BuildMesh();
	}

	Mesh(std::vector<Vertex> verts, std::vector<uint> inds, Texture& tex, GLenum usa)
	{
		vertices = verts;
		indices = inds;
		texture = tex;
		usage = usa;
		BuildMesh();
	}

	Mesh()
	{
		unusable = true;
		VAO = -1;
		EBO = -1;
		VBO = -1;
	}

	void SetMapPosition(float right, float left, float up, float down)
	{
		MapPosition = glm::vec4(right, left, up, down);
	}

	void SetMapPosition(Texture &t, float right, float left, float up, float down)
	{
		texture = t;
		MapPosition = glm::vec4(right, left, up, down);
	}


	void Draw(shader& shader, glm::vec3 loc, float mr, glm::mat4 &projection, glm::mat4 &view)
	{
		if (unusable)
			return;
		shader.use();
		//std::cout << loc.x << " " << loc.y << " " << loc.z << '\n';

		glUniformMatrix4fv(shader.projection, 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(shader.view, 1, GL_FALSE, &view[0][0]);
		glm::mat4 mMat = glm::mat4(1.0f);
		mMat = glm::translate(mMat, loc);
		mMat = glm::rotate(mMat, mr, glm::vec3(0, 1, 0));
		glUniformMatrix4fv(shader.model, 1, GL_FALSE, &mMat[0][0]);

		glBindVertexArray(VAO);
		if (texture.id != -1) {
			glActiveTexture(GL_TEXTURE0 + 1);
			int u = glGetUniformLocation(shader.ID, "texture_diffuse1");
			glUniform1i(glGetUniformLocation(shader.ID, "texture_diffuse1"), 1);
			glBindTexture(GL_TEXTURE_2D, texture.id);
		}
		glDrawElements(GL_TRIANGLES, static_cast<uint>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);

	}


	void Draw(shader& shader, int amount)
	{
		if (unusable || texture.id == -1)
			return;
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(shader.ID, "texture_diffuse1" + 1), 0);
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glBindVertexArray(VAO);
		glDrawElementsInstanced(GL_TRIANGLES, static_cast<uint>(indices.size()), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
	}



	void DrawFont(std::string text, std::map<char, Character>& font, shader& shader, glm::mat4 &projection, glm::mat4& view, glm::vec3 loc, glm::vec3 scale, glm::vec4 color)
	{
		if (unusable || texture.id == -1 || usage == GL_STATIC_DRAW)
			return;
		shader.use();
		//std::cout << loc.x << " " << loc.y << " " << loc.z << '\n';

		glUniformMatrix4fv(shader.projection, 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(shader.view, 1, GL_FALSE, &view[0][0]);
		glActiveTexture(GL_TEXTURE0 + 1);
		glUniform1i(glGetUniformLocation(shader.ID, "text"), 1);
		glBindVertexArray(VAO);
		glm::mat4 mMat = glm::mat4(1.0f);
		glUniformMatrix4fv(shader.model, 1, GL_FALSE, &mMat[0][0]);



		std::string::const_iterator c;

		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = font[*c];
			float xpos = loc.x + ch.bearing.x * scale.x;
			float ypos = loc.y + (font['H'].bearing.y + ch.bearing.y) * scale.y;

			float w = ch.size.x * scale.x;
			float h = ch.size.y * scale.y;

			Vertex verts[4] =
			{
				Vertex(glm::vec3(xpos, ypos - h, 0), glm::vec2(0, 1), color),
				Vertex(glm::vec3(xpos + w, ypos - h, 0), glm::vec2(1, 1), color),
				Vertex(glm::vec3(xpos, ypos, 0), glm::vec2(0, 0), color),
				Vertex(glm::vec3(xpos + w, ypos, 0), glm::vec2(1, 0), color)

			};
			glBindTexture(GL_TEXTURE_2D, ch.tex.id);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawElements(GL_TRIANGLES, static_cast<uint>(indices.size()), GL_UNSIGNED_INT, 0);
			loc.x += (ch.advance >> 6) * scale.x;
		}

		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	//safely draw framebuffer and clean up after
	void DrawFB(shader& shader, float wRatio, float hRatio, glm::mat4& projection, glm::mat4& view, int buffer, int target, uint tID)
	{
		shader.use();
		glBindFramebuffer(GL_FRAMEBUFFER, target);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE1);
		glUniformMatrix4fv(shader.projection, 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(shader.view, 1, GL_FALSE, &view[0][0]);

		glm::mat4 mMat = glm::mat4(1.0f);
		mMat = glm::scale(mMat, glm::vec3(2/wRatio, 2/hRatio, 1));
		mMat = glm::translate(mMat, glm::vec3(-0.5, -0.5, 0));
		glUniformMatrix4fv(shader.model, 1, GL_FALSE, &mMat[0][0]);

		//std::cout <<"drawing framebuffer " << buffer << " to " << target << '\n';
		std::cout << "ratio " << wRatio << " " << hRatio << '\n';

		glBindVertexArray(VAO);
		glUniform1i(glGetUniformLocation(shader.ID, "buffer"), 1);
		glBindTexture(GL_TEXTURE_2D, tID);


		glDrawElements(GL_TRIANGLES, static_cast<uint>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0); 
		glEnable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, 0);


	}

private:

	void BuildMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], usage);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], usage);

		//point
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		//normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		//normal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

		//colour
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

		//boneIDs
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

		//boneIDs
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));


		//and get rid of all that
		glBindVertexArray(0);

		built = true;
	}
};

#endif // !DefMesh
