#include "scene.h"
#include <obj\load.h>
#include <obj\draw.h>

//Create the scene for the models
void CreateScene(Scene* scene)
{
    load_model(&(scene->floor), "assets/models/chessFloor.obj");
    scene->floor_texture_id = load_texture("assets/textures/chessFloor.jpg");

    load_model(&(scene->walls), "assets/models/wall.obj");
    scene->walls_texture_id = load_texture("assets/textures/wall.jpg");

    load_model(&(scene->roof), "assets/models/woodRoof.obj");
    scene->roof_texture_id = load_texture("assets/textures/woodRoof.jpg");

    load_model(&(scene->Rook), "assets/models/rook.obj");
    scene->blackRook_texture_id = load_texture("assets/textures/blackRook.jpg");
    scene->blackRook_second_texture_id = load_texture("assets/textures/woodRook.jpg");

    scene->whiteRook_texture_id = load_texture("assets/textures/whiteRook.jpg");
    scene->whiteRook_second_texture_id = load_texture("assets/textures/darkwoodRook.jpg");

    load_model(&(scene->Pawn), "assets/models/Pawn.obj");
    scene->blackPawn_texture_id = load_texture("assets/textures/blackPawn.jpg");
    scene->blackPawn_second_texture_id = load_texture("assets/textures/woodPawn.jpg");

    scene->whitePawn_texture_id = load_texture("assets/textures/whitePawn.jpg");
    scene->whitePawn_second_texture_id = load_texture("assets/textures/darkwoodPawn.jpg");

    load_model(&(scene->blackKing), "assets/models/blackKing.obj");
    scene->blackKing_texture_id = load_texture("assets/textures/blackKing.jpg");
    scene->blackKing_second_texture_id = load_texture("assets/textures/woodKing.jpg");

    load_model(&(scene->blackKnight), "assets/models/knight.obj");
    scene->blackKnight_texture_id = load_texture("assets/textures/blackKnight.jpg");
    scene->blackKnight_second_texture_id = load_texture("assets/textures/woodKnight.jpg");

    load_model(&(scene->whiteQueen), "assets/models/whiteQueen.obj");
    scene->whiteQueen_texture_id = load_texture("assets/textures/whiteQueen.jpg");
    scene->whiteQueen_second_texture_id = load_texture("assets/textures/darkwoodQueen.jpg");

    scene->material.ambient.red = 0.8;
    scene->material.ambient.green = 0.8;
    scene->material.ambient.blue = 0.8;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

	scene->chess_material.ambient.red = 0.2;
    scene->chess_material.ambient.green = 0.2;
    scene->chess_material.ambient.blue = 0.2;

    scene->chess_material.diffuse.red = 1.0;
    scene->chess_material.diffuse.green = 1.0;
    scene->chess_material.diffuse.blue = 1.0;

    scene->chess_material.specular.red = 0.0;
    scene->chess_material.specular.green = 0.0;
    scene->chess_material.specular.blue = 0.0;

    scene->chess_material.shininess = 0.0;
	scene->redTone = 1.0;
	scene->greenTone = 1.0;
	scene->blueTone = 1.0;
	scene->light = 1.0;

	scene->helppanel_show=false;
	scene->helppanel=load_texture("assets/textures/helppanel.png");

	scene->whiteRook_pos.x = -0.8;
    scene->whiteRook_pos.y = -5.5;
    scene->whiteRook_pos.z = -0.1;

    scene->blackKnight_pos.x = 2;
    scene->blackKnight_pos.y = -10.2;
    scene->blackKnight_pos.z = 0;
    scene->blackKnight_angle.x = 0;
    scene->blackKnight_angle.y = 0;
    scene->blackKnight_angle.z = 1;
    scene->KnightAngle = 180;

    scene->blackRook_pos.x = 3.9;
    scene->blackRook_pos.y = 3.8;
    scene->blackRook_pos.z = -0.1;
    scene->blackRook_angle.x = 0;
    scene->blackRook_angle.y = 0;
    scene->blackRook_angle.z = 0;
    scene->RookAngle = 0;

    scene->blackPawn_pos.x = -3.9;
    scene->blackPawn_pos.y = 0.75;
    scene->blackPawn_pos.z = -0.1;

    scene->whitePawn_angle.x = 0;
    scene->whitePawn_angle.y = 0;
    scene->whitePawn_angle.z = 0;
    scene->PawnAngle = 0;

    scene->whitePawn_pos.x = -5.5;
    scene->whitePawn_pos.y = -0.6;
    scene->whitePawn_pos.z = -0.1;

    scene->whiteQueen_pos.x = 3.9;
    scene->whiteQueen_pos.y = -1.1;
    scene->whiteQueen_pos.z = 0.8;

}
void SetLights(Scene* scene)
{
    scene->ambient_light[0] = scene->redTone;
    scene->ambient_light[1] = scene->greenTone;
    scene->ambient_light[2] = scene->blueTone;
    scene->ambient_light[3] = 0.0f;

    scene->diffuse_light[0] = scene->redTone;
    scene->diffuse_light[1] = scene->greenTone;
    scene->diffuse_light[2] = scene->blueTone;
    scene->diffuse_light[3] = 0.0f;

    scene->specular_light[0] =  1.0f;
    scene->specular_light[1] =  1.0f;
    scene->specular_light[2] =  1.0f;
    scene->specular_light[3] =  0.0f;

    scene->position[0] =  0.0f;
    scene->position[1] =  0.0f;
    scene->position[2] =  4.0f;
    scene->position[3] =  0.0f;

    glLightfv(GL_LIGHT0, GL_AMBIENT, scene->ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, scene->diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, scene->specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, scene->position);
}

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
void UpdateScene(Scene* scene, double time)
{

    if(scene->whiteRook_pos.y < 4){
        scene->whiteRook_pos.y += 2 * time;
    }

    if(scene->whiteRook_pos.y > 3.8 && scene->KnightAngle > 80){
        scene->redTone = 1;
        scene->greenTone = 0;
        scene->blueTone = 0;

        scene->blackKnight_angle.x += 0.01;
        scene->blackKnight_angle.z -= 0.01;
        scene->KnightAngle -= 0.1;
    }

    if(scene->KnightAngle < 170){
        scene->redTone = scene->light;
        scene->greenTone = scene->light;
        scene->blueTone = scene->light;
    }

    if(scene->KnightAngle < 155 && scene->blackPawn_pos.x > -5.7 && scene->blackPawn_pos.y > -0.7){
        scene->blackPawn_pos.x -= 2 * time;
        scene->blackPawn_pos.y -= 2 * time;
    }

    if(scene->blackPawn_pos.y < -0.5){
        scene->redTone = 1;
        scene->greenTone = 0;
        scene->blueTone = 0;

        scene->whitePawn_angle.x -= 0.3;
        scene->whitePawn_angle.y += 0.3;

        scene->whitePawn_pos.z -= 0.01;
        scene->whitePawn_pos.y -= 0.02;
        scene->whitePawn_pos.x -= 0.02;

        scene->PawnAngle -= 1;
    }

    if(scene->PawnAngle < -70){
        scene->redTone = scene->light;
        scene->greenTone = scene->light;
        scene->blueTone = scene->light;
    }

    if(scene->PawnAngle < -200 && scene->whiteQueen_pos.y < 3.6){
        scene->whiteQueen_pos.y += 2 * time;
    }

    if(scene->whiteQueen_pos.y > 3.4){
        scene->redTone = 1;
        scene->greenTone = 0;
        scene->blueTone = 0;

        scene->blackRook_angle.x -= 0.03;
        scene->blackRook_pos.z -= 0.01;
        scene->blackRook_pos.y += 0.03;
        scene->RookAngle += 1;
    }

    if(scene->RookAngle > 75){
        scene->redTone = scene->light;
        scene->greenTone = scene->light;
        scene->blueTone = scene->light;
    }

}


//Rendering the objects on to the screen
void RenderScene(Scene* scene,int texture)
{
    SetMaterial(&(scene->material));
    SetLights(scene);

    glPushMatrix();
    SetMaterial(&(scene->material));
    glBindTexture(GL_TEXTURE_2D, scene->floor_texture_id);
    glTranslatef(0, 0, 0);
    draw_model(&(scene->floor));
    glPopMatrix();

    //frontwall
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->walls_texture_id);
    glRotatef(90, 0, 0, -1);
    glTranslatef(0, 7.2, 2);
    draw_model(&(scene->walls));
    glPopMatrix();

    //rightwall
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->walls_texture_id);
    glTranslatef(0, -12.2, 2);
    draw_model(&(scene->walls));
    glPopMatrix();

    //leftwall
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->walls_texture_id);
    glTranslatef(0, 7, 2);
    draw_model(&(scene->walls));
    glPopMatrix();

    //backwall
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->walls_texture_id);
    glRotatef(90, 0, 0, -1);
    glTranslatef(0, -12.3, 2);
    draw_model(&(scene->walls));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->roof_texture_id);
    glTranslatef(0, 0, 5);
    draw_model(&(scene->roof));
    glPopMatrix();

	SetMaterial(&(scene->chess_material));

	if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->blackRook_second_texture_id);
        glTranslatef(scene->blackRook_pos.x, scene->blackRook_pos.y, scene->blackRook_pos.z);
        glRotatef(scene->RookAngle, scene->blackRook_angle.x, scene->blackRook_angle.y, scene->blackRook_angle.z);
        draw_model(&(scene->Rook));
        glPopMatrix();
	}else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->blackRook_texture_id);
        glTranslatef(scene->blackRook_pos.x, scene->blackRook_pos.y, scene->blackRook_pos.z);
        glRotatef(scene->RookAngle, scene->blackRook_angle.x, scene->blackRook_angle.y, scene->blackRook_angle.z);
        draw_model(&(scene->Rook));
        glPopMatrix();
	}

    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->blackPawn_second_texture_id);
        glTranslatef(scene->blackPawn_pos.x, scene->blackPawn_pos.y, scene->blackPawn_pos.z);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->blackPawn_texture_id);
        glTranslatef(scene->blackPawn_pos.x, scene->blackPawn_pos.y, scene->blackPawn_pos.z);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }
    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->blackKing_second_texture_id);
        glTranslatef(3.9, 5.1, 0.8);
        draw_model(&(scene->blackKing));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->blackKing_texture_id);
        glTranslatef(3.9, 5.1, 0.8);
        draw_model(&(scene->blackKing));
        glPopMatrix();
    }

    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->blackKnight_second_texture_id);
        glScalef(0.4, 0.4, 0.4);
        glRotatef(scene->KnightAngle, scene->blackKnight_angle.x, scene->blackKnight_angle.y, scene->blackKnight_angle.z);
        glTranslatef(scene->blackKnight_pos.x, scene->blackKnight_pos.y, scene->blackKnight_pos.z);
        draw_model(&(scene->blackKnight));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->blackKnight_texture_id);
        glScalef(0.4, 0.4, 0.4);
        glRotatef(scene->KnightAngle, scene->blackKnight_angle.x, scene->blackKnight_angle.y, scene->blackKnight_angle.z);
        glTranslatef(scene->blackKnight_pos.x, scene->blackKnight_pos.y, scene->blackKnight_pos.z);
        draw_model(&(scene->blackKnight));
        glPopMatrix();
    }

    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whitePawn_second_texture_id);
        glTranslatef(scene->whitePawn_pos.x,  scene->whitePawn_pos.y,  scene->whitePawn_pos.z);
        glRotatef(scene->PawnAngle, scene->whitePawn_angle.x, scene->whitePawn_angle.y, scene->whitePawn_angle.z);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whitePawn_texture_id);
        glTranslatef(scene->whitePawn_pos.x,  scene->whitePawn_pos.y,  scene->whitePawn_pos.z);
        glRotatef(scene->PawnAngle, scene->whitePawn_angle.x, scene->whitePawn_angle.y, scene->whitePawn_angle.z);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }
    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whitePawn_second_texture_id);
        glTranslatef(-2.4, -3.9, -0.1);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whitePawn_texture_id);
        glTranslatef(-2.4, -3.9, -0.1);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }

    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whitePawn_second_texture_id);
        glTranslatef(0.8, -3.9, -0.1);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whitePawn_texture_id);
        glTranslatef(0.8, -3.9, -0.1);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }

    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whitePawn_second_texture_id);
        glTranslatef(2.3, -2.2, -0.1);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whitePawn_texture_id);
        glTranslatef(2.3, -2.2, -0.1);
        draw_model(&(scene->Pawn));
        glPopMatrix();
    }

    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whiteQueen_second_texture_id);
        glTranslatef(scene->whiteQueen_pos.x, scene->whiteQueen_pos.y, scene->whiteQueen_pos.z);
        draw_model(&(scene->whiteQueen));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whiteQueen_texture_id);
        glTranslatef(scene->whiteQueen_pos.x, scene->whiteQueen_pos.y, scene->whiteQueen_pos.z);
        draw_model(&(scene->whiteQueen));
        glPopMatrix();
    }

    if(texture == 1){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whiteRook_second_texture_id);
        glTranslatef(scene->whiteRook_pos.x,scene->whiteRook_pos.y, scene->whiteRook_pos.z);
        draw_model(&(scene->Rook));
        glPopMatrix();
    }else if(texture == 2){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->whiteRook_texture_id);
        glTranslatef(scene->whiteRook_pos.x,scene->whiteRook_pos.y, scene->whiteRook_pos.z);
        draw_model(&(scene->Rook));
        glPopMatrix();
    }
}
