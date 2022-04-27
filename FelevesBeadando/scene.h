#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "camera.h"
#include "texture.h"
#include <obj/model.h>

typedef struct Scene
{

    Model floor;
    Model walls;
    Model roof;

    Model blackRook;
    Model blackKing;
    Model blackPawn;
    Model blackKnight;

    Model whitePawn;
    Model whiteQueen;
    Model whiteRook;

    Material material;
	Material chess_material;

    GLuint floor_texture_id;
    GLuint walls_texture_id;
    GLuint roof_texture_id;

    GLuint blackRook_texture_id;
    GLuint blackPawn_texture_id;
    GLuint blackKing_texture_id;
    GLuint blackKnight_texture_id;

    GLuint whitePawn_texture_id;
    GLuint whiteQueen_texture_id;
    GLuint whiteRook_texture_id;

    float ambient_light[4];
    float diffuse_light[4];
    float specular_light[4];
    float position[4];
	float light;
	bool helppanel_show;
	GLuint helppanel;

	vec3 blackKnight_pos;
	vec3 blackPawn_pos;
	vec3 blackRook_pos;


	vec3 blackKnight_angle;
	float KnightAngle;

	vec3 blackRook_angle;
	float RookAngle;

	vec3 whiteRook_pos;
    vec3 whiteQueen_pos;

	vec3 whitePawn_pos;
	vec3 whitePawn_angle;
	float PawnAngle;

} Scene;

void CreateScene(Scene* scene);

void SetMaterial(const Material* material);

void UpdateScene(Scene* scene);

void RenderScene(Scene* scene);

#endif // SCENE_H_INCLUDED
