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

    Model Rook;
    Model Pawn;

    Model blackKing;
    Model blackKnight;

    Model whiteQueen;

    GLuint floor_texture_id;
    GLuint walls_texture_id;
    GLuint roof_texture_id;

    GLuint blackRook_texture_id;
    GLuint blackPawn_texture_id;
    GLuint blackKing_texture_id;
    GLuint blackKnight_texture_id;
    GLuint blackRook_second_texture_id;
    GLuint blackPawn_second_texture_id;
    GLuint blackKing_second_texture_id;
    GLuint blackKnight_second_texture_id;

    GLuint whitePawn_texture_id;
    GLuint whiteQueen_texture_id;
    GLuint whiteRook_texture_id;
    GLuint whitePawn_second_texture_id;
    GLuint whiteQueen_second_texture_id;
    GLuint whiteRook_second_texture_id;

    //light prop.
    float ambient_light[4];
    float diffuse_light[4];
    float specular_light[4];
    float position[4];

    float redTone;
    float greenTone;
    float blueTone;
    float light;

    Material material;
    Material chess_material;

    //black prop.
	vec3 blackKnight_pos;
	vec3 blackPawn_pos;
	vec3 blackRook_pos;
	vec3 blackKnight_angle;
    vec3 blackRook_angle;

	float KnightAngle;
	float RookAngle;

    //white prop.
	vec3 whiteRook_pos;
    vec3 whiteQueen_pos;
	vec3 whitePawn_pos;
	vec3 whitePawn_angle;

	float PawnAngle;

    //helppanel prop.
    bool helppanel_show;
    GLuint helppanel;

} Scene;

void CreateScene(Scene* scene);

void SetMaterial(const Material* material);

void UpdateScene(Scene* scene, double time);

void RenderScene(Scene* scene,int texture);

#endif // SCENE_H_INCLUDED
