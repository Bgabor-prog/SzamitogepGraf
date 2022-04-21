#include "scene.h"
#include <obj\load.h>
#include <obj\draw.h>

//Create the scene for the models
void CreateScene(Scene* scene)
{

    load_model(&(scene->floor), "assets/models/chessFloor.obj");
    scene->floor_texture_id = load_texture("assets/textures/chessFloor.jpg");

    load_model(&(scene->rightwall), "assets/models/wall.obj");
    scene->rightwall_texture_id = load_texture("assets/textures/wall.jpg");

    load_model(&(scene->frontwall), "assets/models/wall1.obj");
    scene->frontwall_texture_id = load_texture("assets/textures/wall1.jpg");

    load_model(&(scene->leftwall), "assets/models/wall2.obj");
    scene->leftwall_texture_id = load_texture("assets/textures/wall2.jpg");

    load_model(&(scene->backwall), "assets/models/wall3.obj");
    scene->backwall_texture_id = load_texture("assets/textures/wall3.jpg");

    load_model(&(scene->roof), "assets/models/woodRoof.obj");
    scene->roof_texture_id = load_texture("assets/textures/woodRoof.jpg");

    load_model(&(scene->blackRook), "assets/models/blackRook.obj");
    scene->blackRook_texture_id = load_texture("assets/textures/blackRook.jpg");

    load_model(&(scene->blackPawn), "assets/models/Pawn.obj");
    scene->blackPawn_texture_id = load_texture("assets/textures/blackPawn.jpg");

    load_model(&(scene->blackKing), "assets/models/blackKing.obj");
    scene->blackKing_texture_id = load_texture("assets/textures/blackKing.jpg");

    load_model(&(scene->whitePawn), "assets/models/Pawn.obj");
    scene->whitePawn_texture_id = load_texture("assets/textures/whitePawn.jpg");


    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 0.0;
}

/*void SetLights()
{
    float ambient_light[] = { 0.5f, 0.5f, 0.5f, 0.0f };
    float diffuse_light[] = { 0.5f, 0.5f, 0.0, 0.0f };
    float specular_light[] = { 0.5f, 0.5f, 0.5f, 0.2f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}
*/
void SetMaterial(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

//Updating the scene in real time
void UpdateScene(Scene* scene)
{

}
//Rendering the objects on to the screen
void RenderScene(const Scene* scene)
{
    SetMaterial(&(scene->material));
    //SetLights();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->floor_texture_id);
    draw_model(&(scene->floor));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->frontwall_texture_id);
    glTranslatef(10, 0, -0.3);
    draw_model(&(scene->frontwall));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->rightwall_texture_id);
    glTranslatef(0, 7.2, 2);
    draw_model(&(scene->rightwall));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->leftwall_texture_id);
    glTranslatef(0, -10.2, -0.3);
    draw_model(&(scene->leftwall));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->backwall_texture_id);
    glTranslatef(-10, 0, -0.3);
    draw_model(&(scene->backwall));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->roof_texture_id);
    glTranslatef(0, 0, 5);
    draw_model(&(scene->roof));
    glPopMatrix();


    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->blackRook_texture_id);
    glTranslatef(0.75, 2.3, -0.1);
    draw_model(&(scene->blackRook));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->blackPawn_texture_id);
    glTranslatef(0.75, 0.75, -0.1);
    draw_model(&(scene->blackPawn));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->blackKing_texture_id);
    glTranslatef(3.9, 5.1, 0.8);
    draw_model(&(scene->blackKing));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->whitePawn_texture_id);
    glTranslatef(-0.75, -0.75, -0.1);
    draw_model(&(scene->whitePawn));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->whitePawn_texture_id);
    glTranslatef(2.3, -3.8, -0.1);
    draw_model(&(scene->whitePawn));
    glPopMatrix();

}
