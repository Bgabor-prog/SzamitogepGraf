#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "camera.h"
#include "texture.h"
#include <obj/model.h>

typedef struct Scene
{

    Model floor;
    Model backwall;
    Model frontwall;
    Model rightwall;
    Model leftwall;
    Model roof;
    Model blackRook;
    Model blackKing;
    Model blackPawn;

    Model whitePawn;

    Material material;


    GLuint floor_texture_id;
    GLuint backwall_texture_id;
    GLuint frontwall_texture_id;
    GLuint rightwall_texture_id;
    GLuint leftwall_texture_id;
    GLuint roof_texture_id;

    GLuint blackRook_texture_id;
    GLuint blackPawn_texture_id;
    GLuint blackKing_texture_id;

    GLuint whitePawn_texture_id;


} Scene;

void CreateScene(Scene* scene);

void SetMaterial(const Material* material);

void UpdateScene(Scene* scene);

void RenderScene(const Scene* scene);

#endif // SCENE_H_INCLUDED
