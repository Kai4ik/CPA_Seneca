using namespace std;

#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "..\SOIL\src\SOIL.h"
#include <vector>
#include <iostream>


//Added on Nov. 21 2021 by: Alireza Moghaddam
enum GameObject_Type {
	PLAYER,
	ENEMY,
	BULLET,
	OBSTACLE,
};

// used to rotate the wheels
GLfloat rotation = 0.0;

class GameObject
{
public:
	glm::vec3 location_;
	glm::vec3 rotation_;
	glm::vec3 scale;
	glm::vec3 moving_direction;
	glm::vec3 target_direction;
	GLfloat velocity;
	GLfloat collider_dimension; //We use box as wrapper with radius = 0.9 * scale of the object Note: 0.9 is the original dimension of the boxes we generate
	int living_time;
	int life_span;		//In this code, the life span for obstacles is set to a negative value (Just so that they remain in the scene during the game)
	int type;
	bool isAlive;
	bool isCollided;
	//default constuctor
	std::vector<GameObject>children;
	GameObject(){
		location_ = glm::vec3(0, 0, 0);
		glm::vec3 rotation_ = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(0, 0, 0);
		glm::vec3 moving_direction = glm::vec3(0, 0, 0);
		living_time = 0;
		velocity = 0;
		isCollided = false;
		isAlive = true;
		life_span = -1;
		type = OBSTACLE;
	};
	//used to draw the tank 
	void draw(glm::vec3 scale, GLuint texture, GLenum mode, GLuint verticesStart, GLuint vecrticesEnd);
	//used to render tank on the world 
	void render();
};

class Tank : public GameObject
{
public:
	//Rationale: used to create wheels for tank object
	Tank() : GameObject()
	{
		glm::vec3 wheelsTransformations[4] = {
			glm::vec3(0.45,0.45,0.1),
			glm::vec3(-0.45, -0.45,0.1),
			glm::vec3(0.45, -0.45,0.1),
			glm::vec3(-0.45,0.45,0.1),
		};
		for (int k = 0; k < 4; k++)
		{
			GameObject wheel;
			wheel.location_ = wheelsTransformations[k];
			children.push_back(wheel);
		}
	};
};

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer};
enum Attrib_IDs { vPosition = 0 };

const GLint NumBuffers = 2;
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint location;
GLuint cam_mat_location;
GLuint proj_mat_location;
GLuint texture[5];	//Array of pointers to textrure data in VRAM. We use two textures in this example.


const GLuint NumVertices = 76;

//Height of camera (player) from the level
float height = 0.8f;

//Player motion speed for movement and pitch/yaw
float travel_speed = 300.0f;		//Motion speed
float mouse_sensitivity = 0.01f;	//Pitch/Yaw speed

//Used for tracking mouse cursor position on screen
int x0 = 0;	
int y_0 = 0;
 
//Transformation matrices and camera vectors
glm::mat4 model_view;
glm::vec3 unit_z_vector = glm::vec3(0, 0, 1);	//Assigning a meaningful name to (0,0,1) :-)
glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, height);
glm::vec3 forward_vector = glm::vec3(1, 1, 0);	//Forward vector is parallel to the level at all times (No pitch)

//The direction which the camera is looking, at any instance
glm::vec3 looking_dir_vector = glm::vec3(1, 1, 0);
glm::vec3 up_vector = unit_z_vector;
glm::vec3 side_vector = glm::cross(up_vector, forward_vector);


//Used to measure time between two frames
int oldTimeSinceStart = 0;
int deltaTime;

//used to check whether spawn time has come (we increase every time scene is updated)
int spawnTime = 0;
// used to end game (victory, loss)
bool gameOver = false;
int printResult = 0;
//used to count how many tanks were killed
int tanksKilled = 0;

//Creating and rendering bunch of objects on the scene to interact with
const int Num_Obstacles = 50;
float obstacle_data[Num_Obstacles][3];
std::vector<GameObject> sceneGraph;

//Helper function to generate a random float number within a range
float randomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

// inititializing buffers, coordinates, setting up pipeline, etc.
void init(void)
{
	glEnable(GL_DEPTH_TEST);

	//Normalizing all vectors
	up_vector = glm::normalize(up_vector);
	forward_vector = glm::normalize(forward_vector);
	looking_dir_vector = glm::normalize(looking_dir_vector);
	side_vector = glm::normalize(side_vector);

	//Modified on Nov. 21 2021 by: Alireza Moghaddam

	//Randomizing the position and scale of obstacles
	//Creating obstacles and adding them to the GameScene
	for (int i = 0; i < Num_Obstacles; i++)
	{
		obstacle_data[i][0] = randomFloat(-50, 50); //X
		obstacle_data[i][1] = randomFloat(-50, 50); //Y
		obstacle_data[i][2] = randomFloat(0.1f, 10.0f); //Scale

		GameObject go;
		go.location_ = glm::vec3(obstacle_data[i][0], obstacle_data[i][1], 0);	//Let the object stay on the ground at the beginning
		go.scale = glm::vec3(obstacle_data[i][2], obstacle_data[i][2], obstacle_data[i][2]);
		go.collider_dimension = 0.9 * go.scale.x; //0.9 is the length of an endge of the box used for the obstacle
		sceneGraph.push_back(go);		
	}
	//End of modification

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);	//My Pipeline is set up


	//Since we use texture mapping, to simplify the task of texture mapping, 
	//and to clarify the demonstration of texture mapping, we consider 4 vertices per face.
	//Overall, we will have 24 vertices and we have 4 vertices to render the sky (a large square).
	//Therefore, we'll have 28 vertices in total.
	GLfloat vertices[NumVertices][3] = {
		
		{ -100.0, -100.0, 0.0 }, //Plane to walk on and a sky
		{ 100.0, -100.0, 0.0 },
		{ 100.0, 100.0, 0.0 },
		{ -100.0, 100.0, 0.0 },

		{ -0.45, -0.45 ,0.01 }, // bottom face
		{ 0.45, -0.45 ,0.01 },
		{ 0.45, 0.45 ,0.01 },
		{ -0.45, 0.45 ,0.01 },

		{ -0.45, -0.45 ,0.9 }, //top face
		{ 0.45, -0.45 ,0.9 },
		{ 0.45, 0.45 ,0.9 },
		{ -0.45, 0.45 ,0.9 },

		{ 0.45, -0.45 , 0.01 }, //left face
		{ 0.45, 0.45 , 0.01 },
		{ 0.45, 0.45 ,0.9 },
		{ 0.45, -0.45 ,0.9 },

		{ -0.45, -0.45, 0.01 }, //right face
		{ -0.45, 0.45 , 0.01 },
		{ -0.45, 0.45 ,0.9 },
		{ -0.45, -0.45 ,0.9 },

		{ -0.45, 0.45 , 0.01 }, //front face
		{ 0.45, 0.45 , 0.01 },
		{ 0.45, 0.45 ,0.9 },
		{ -0.45, 0.45 ,0.9 },
	
		{ -0.45, -0.45 , 0.01 }, //back face
		{ 0.45, -0.45 , 0.01 },
		{ 0.45, -0.45 ,0.9 },
		{ -0.45, -0.45 ,0.9 },


		// Whhel for tank - hexagon

		{ -0.45, -0.70 ,0.01 }, // bottom face
		{ 0.45, -0.70 ,0.01 },
		{ 0.45, 0.70 ,0.01 },
		{ -0.45, 0.70 ,0.01 },

		{ -0.45, -0.45 ,0.7 }, //top face 
		{ 0.45, -0.45 ,0.7 },
		{ 0.45, 0.45 ,0.7 },
		{ -0.45, 0.45 ,0.7 },

		{ 0.45, -0.70 , 0.01 }, //left face
		{ 0.45, 0.70 , 0.01 },
		{ 0.45, 0.45 ,0.7 },
		{ 0.45, -0.45 ,0.7 },

		{ -0.45, -0.70, 0.01 }, //right face
		{ -0.45, 0.70 , 0.01 },
		{ -0.45, 0.45 ,0.7 },
		{ -0.45, -0.45 ,0.7 },

		{ -0.45, 0.70 , 0.01 }, //front face 
		{ 0.45, 0.70 , 0.01 },
		{ 0.45, 0.45 ,0.7 },
		{ -0.45, 0.45 ,0.7 },

		{ -0.45, -0.70 , 0.01 }, //back face
		{ 0.45, -0.70, 0.01 },
		{ 0.45, -0.45 ,0.7 },
		{ -0.45, -0.45 ,0.7 },

		// Second half of the wheel
		{ 0.45, 0.70 ,-0.01 }, // bottom face
		{ -0.45, 0.70 ,-0.01 },
		{ -0.45, -0.70 ,-0.01 },
		{ 0.45, -0.70 ,-0.01 },

		{ -0.45, -0.45 ,-0.7 }, //top face 
		{ 0.45, -0.45 ,-0.7 },
		{ 0.45, 0.45 ,-0.7 },
		{ -0.45, 0.45 ,-0.7 },

		{ 0.45, -0.70 , -0.01 }, //left face
		{ 0.45, 0.70 , -0.01 },
		{ 0.45, 0.45 ,-0.7 },
		{ 0.45, -0.45 ,-0.7 },

		{ -0.45, -0.70, -0.01 }, //right face
		{ -0.45, 0.70 , -0.01 },
		{ -0.45, 0.45 ,-0.7 },
		{ -0.45, -0.45 ,-0.7 },

		{ -0.45, 0.70 , -0.01 }, //front face 
		{ 0.45, 0.70 , -0.01 },
		{ 0.45, 0.45 ,-0.7 },
		{ -0.45, 0.45 ,-0.7 },

		{ -0.45, -0.70 , -0.01 }, //back face
		{ 0.45, -0.70, -0.01 },
		{ 0.45, -0.45 ,-0.7 },
		{ -0.45, -0.45 ,-0.7 },
	};

	//These are the texture coordinates for the second texture
	GLfloat textureCoordinates[76][2] = {
		0.0f, 0.0f,
		200.0f, 0.0f,
		200.0f, 200.0f,
		0.0f, 200.0f,
		
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		// Wheel for tank
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
	};


	//Creating our texture:
	//This texture is loaded from file. To do this, we use the SOIL (Simple OpenGL Imaging Library) library.
	//When using the SOIL_load_image() function, make sure the you are using correct patrameters, or else, your image will NOT be loaded properly, or will not be loaded at all.
	GLint width1, height1;
	unsigned char* textureData1 = SOIL_load_image("grass.png", &width1, &height1, 0, SOIL_LOAD_RGB);

	GLint width2, height2;
	unsigned char* textureData2 = SOIL_load_image("hay.png", &width2, &height2, 0, SOIL_LOAD_RGB);

	//Final Exam code Added 
	//Rationale: used as a texutre for bullet 
	GLint width3, height3;
	unsigned char* textureData3 = SOIL_load_image("bullet.jpg", &width3, &height3, 0, SOIL_LOAD_RGB);

	GLint width4, height4;
	unsigned char* textureData4 = SOIL_load_image("ammo.png", &width4, &height4, 0, SOIL_LOAD_RGB);

	//Final Exam code Added 
	//Rationale: used as a texture for wheel
	GLint width5, height5;
	unsigned char* textureData5 = SOIL_load_image("wheel.jpg", &width5, &height5, 0, SOIL_LOAD_RGB);

	glGenBuffers(2, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindAttribLocation(program, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
	glBindAttribLocation(program, 1, "vTexCoord");
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);

	location = glGetUniformLocation(program, "model_matrix");
	cam_mat_location = glGetUniformLocation(program, "camera_matrix");
	proj_mat_location = glGetUniformLocation(program, "projection_matrix");

	///////////////////////TEXTURE SET UP////////////////////////
	
	//Allocating two buffers in VRAM
	glGenTextures(4, texture);

	//First Texture: 

	//Set the type of the allocated buffer as "TEXTURE_2D"
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	//Loading the second texture into the second allocated buffer:
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData1);

	//Setting up parameters for the texture that recently pushed into VRAM
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//And now, second texture: 

	//Set the type of the allocated buffer as "TEXTURE_2D"
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	//Loading the second texture into the second allocated buffer:
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData2);

	//Setting up parameters for the texture that recently pushed into VRAM
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Third texture
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData3);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Fourth texture
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width4, height4, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData4);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Fifth texture
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width5, height5, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData5);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

//Modified on Nov. 21 2021 by: Alireza Moghaddam
//Helper function to draw a cube
void drawObject(glm::vec3 scale, char type)
{
	model_view = glm::scale(model_view, scale);
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	glBindTexture(GL_TEXTURE_2D, type == 'o' ? texture[1] : texture[2]);
	glDrawArrays(GL_QUADS, 4, 24);
}
//End of Modification

// used to render tanks on the scene 
void drawTanks()
{
	for (int i = 0; i < sceneGraph.size(); i++)
	{
		if (sceneGraph[i].type == ENEMY)
			sceneGraph[i].render();
	}
}

//Added on Nov. 21 2021 by: Alireza Moghaddam
//This function takes in two game objects and finds out if they are colliding.
bool isColliding(GameObject one, GameObject two) {
	return glm::abs(one.location_.x - two.location_.x) < (one.collider_dimension/2 + two.collider_dimension/2) &&
				glm::abs(one.location_.y - two.location_.y) < (one.collider_dimension/2 + two.collider_dimension/2);
}

//This function iterates through the scene graph and checks the collision status between each and every two objects
//When collided, the .isCollided property of the game object is set to true
void checkCollisions() {
	spawnTime += deltaTime;
	// used to add new Tank object to the scene (it has random location and speed)
	if (spawnTime > 2000)
	{
		Tank go;
		go.location_ = glm::vec3(randomFloat(-50, 50), randomFloat(-50, 50), 0);
		go.scale = glm::vec3(3.0f, 3.0f, 3.0f);
		go.velocity = randomFloat(0.001, 0.004);
		go.collider_dimension = 0.9 * go.scale.x; //0.9 is the length of an endge of the box used for the obstacle
		go.type = ENEMY;
		go.moving_direction = glm::vec3(0, 0, 0) - go.location_;
		go.life_span = 100000;
		sceneGraph.push_back(go);
		spawnTime = 0;
	}

	// used to check whether two objects collided with each other 
	for (int i = 0; i < sceneGraph.size(); i++) {
		for (int j = 0; j < sceneGraph.size(); j++) {
			if (i != j && /*if i=j then it means that we are checking self-collilsion. We do NOT consider self-collision as a collision*/
				sceneGraph[i].isAlive && 
				sceneGraph[j].isAlive && 
				isColliding(sceneGraph[i], sceneGraph[j])) {				
				if(sceneGraph[i].type != OBSTACLE && sceneGraph[j].type != OBSTACLE)	//We ignore the collision between two obstacles :-)
				{
					// if enemy and bullet collided with each other, it means that player killed one tank
					if ((sceneGraph[i].type == ENEMY && sceneGraph[j].type == BULLET)
						|| (sceneGraph[j].type == ENEMY && sceneGraph[i].type == BULLET))
					{
						tanksKilled++;
					}
					// used to make object dead, so in the other function it can be erased from the scene
					sceneGraph[i].isCollided = true;
					sceneGraph[j].isCollided = true;
					sceneGraph[i].isAlive = false;
					sceneGraph[j].isAlive = false;
				}
			}
		}
	}

	// used to check collision between player and tank (enemy)
	for (int i = 0; i < sceneGraph.size(); i++)
	{
		if (sceneGraph[i].isAlive && sceneGraph[i].type == ENEMY)
		{
			glm::vec3 dirEnemy = sceneGraph[i].location_ - glm::vec3(0.005, 0.0041, 0.0041) * looking_dir_vector;
			dirEnemy.z = 0.0;
			sceneGraph[i].location_ = dirEnemy;
			GLfloat highX = cam_pos.x + 1, lowX = cam_pos.x - 1,
				highY = cam_pos.y + 1, lowY = cam_pos.y - 1,
				currentObjLocationX = sceneGraph[i].location_.x,
				currentObjLocationY = sceneGraph[i].location_.y;
			// if collision occured, game is over - player lost
			if (currentObjLocationX <= highX && currentObjLocationX >= lowX
				&& currentObjLocationY <= highY && currentObjLocationY >= lowY){
				gameOver = true;
			}
		}
	}
}

//This function gets called every frame and updates the information written inside the sceneGraph.
void updateSceneGraph() {
	//Updating the collision status of all objects on the scene
	checkCollisions();		

	// used to check whether 10 tanks were killed - if so, game is over - player won
	if (tanksKilled == 10)
		gameOver = true;

	for (int i = 0; i < sceneGraph.size(); i++) {
		GameObject go = sceneGraph[i];
		if (go.life_span > 0 && go.isAlive && go.living_time > go.life_span)	//Check if the life of a Game Object is over
			go.isAlive = false;	
		// if tank reached to the center of the game - object shoul be erased from the scene
		if (go.location_.x == 0 && go.location_.y == 0)
			go.isAlive = false;
		if (go.life_span > 0 && go.isAlive && go.living_time < go.life_span) {	
			//If the Game Object is still alive and the object is not an obstacle
			//1 - Updating the location
			go.location_ += ((GLfloat) deltaTime) * go.velocity * glm::normalize(go.moving_direction);
			//2 - updating Time To Live
			go.living_time += deltaTime;
		}
		sceneGraph[i] = go;	//Overwriting the game object data back into the SceneGraph
	}
}

//Renders level
void draw_level()
{
	//Select the first texture (grass.png) when drawing the first geometry (floor)
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glDrawArrays(GL_QUADS, 0, 4);
	updateSceneGraph();
	for (int i = 0; i < sceneGraph.size(); i++){
		GameObject go = sceneGraph[i];
		//Processing each and every object in the Scene Graph
		if (go.isAlive) {
			//Render the object on the scene
			model_view = glm::translate(model_view, go.location_);
			model_view = glm::rotate(model_view, 0.0f, unit_z_vector);	//For now, we do not consider the rotation. 
			glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);			
			//You may use different texture/geometry based on the game object type
			if (go.type == OBSTACLE) 
				drawObject(go.scale, 'o');
			if (go.type == BULLET )
				drawObject(go.scale, 'b');
			
			model_view = glm::mat4(1.0);
			glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
		}	
		// if object is dead, we delete it from the scene
		else
			sceneGraph.erase(sceneGraph.begin() + i);
	}
}
//End of codes developed by Alireza Moghaddam Nov. 21

void display(void)
{
	// used to check whether game is over or not
	if (gameOver == true && tanksKilled < 10 && printResult == 0)
	{
		std::cout << "--------------------------------------------------------------" << std::endl;
		std::cout << "--------- Loss! You died after collision with tank -----------" << std::endl;
		std::cout << "--------------------------------------------------------------" << std::endl;
		printResult++;
	}
	if (gameOver == true && tanksKilled == 10 && printResult == 0)
	{
		std::cout << "--------------------------------------------------------------" << std::endl;
		std::cout << "-------- Victory! " << tanksKilled << " tanks were killed during " << oldTimeSinceStart << " ----------" << std::endl;
		std::cout << "--------------------------------------------------------------" << std::endl;
		printResult++;
	}

	if (gameOver == false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		model_view = glm::mat4(1.0);
		glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

		//The 3D point in space that the camera is looking
		glm::vec3 look_at = cam_pos + looking_dir_vector;

		glm::mat4 camera_matrix = glm::lookAt(cam_pos, look_at, up_vector);
		glUniformMatrix4fv(cam_mat_location, 1, GL_FALSE, &camera_matrix[0][0]);

		glm::mat4 proj_matrix = glm::frustum(-0.01f, +0.01f, -0.01f, +0.01f, 0.01f, 100.0f);
		glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, &proj_matrix[0][0]);

		draw_level();
		drawTanks();
		glFlush();
	}
}


void keyboard(unsigned char key, int x, int y)
{
	// when game is over, player cannot move anymore
	if (gameOver == false)
	{
		if (key == 'a')
			cam_pos += side_vector * travel_speed * ((float)deltaTime) / 1000.0f;
		if (key == 'd')
			cam_pos -= side_vector * travel_speed * ((float)deltaTime) / 1000.0f;
		if (key == 'w')
			cam_pos += forward_vector * travel_speed * ((float)deltaTime) / 1000.0f;
		if (key == 's')
			cam_pos -= forward_vector * travel_speed * ((float)deltaTime) / 1000.0f;
		//Added on Nov. 21 2021 by: Alireza Moghaddam
		if (key == 'f')
		{
			//Create a bullet and place it inside the GameScene
			GameObject go;
			//The bullet will spawn with an offset from the location of the player
			go.location_ = cam_pos;	
			go.scale = glm::vec3(0.03, 0.03, 0.03);
			go.velocity = 0.004;
			go.type = BULLET;
			go.moving_direction = looking_dir_vector;
			go.collider_dimension = 0.9 * go.scale.x; 
			//Each bullet lives for 2 seconds
			go.life_span = 2000;	
			sceneGraph.push_back(go);
		}
	}
	//End of codes Added 
}

//Controlling Pitch with vertical mouse movement
void mouse(int x, int y)
{
	// when game is over, player cannot move anymore
	if (gameOver == false)
	{
		//Controlling Yaw with horizontal mouse movement
		int delta_x = x - x0;

		//The following vectors must get updated during a yaw movement
		forward_vector = glm::rotate(forward_vector, -delta_x * mouse_sensitivity, unit_z_vector);
		looking_dir_vector = glm::rotate(looking_dir_vector, -delta_x * mouse_sensitivity, unit_z_vector);
		side_vector = glm::rotate(side_vector, -delta_x * mouse_sensitivity, unit_z_vector);
		up_vector = glm::rotate(up_vector, -delta_x * mouse_sensitivity, unit_z_vector);
		x0 = x;

		//The following vectors must get updated during a pitch movement
		int delta_y = y - y_0;
		glm::vec3 tmp_up_vec = glm::rotate(up_vector, delta_y * mouse_sensitivity, side_vector);
		glm::vec3 tmp_looking_dir = glm::rotate(looking_dir_vector, delta_y * mouse_sensitivity, side_vector);

		//The dot product is used to prevent the user from over-pitch (pitching 360 degrees)
		//The dot product is equal to cos(theta), where theta is the angle between looking_dir and forward vector
		GLfloat dot_product = glm::dot(tmp_looking_dir, forward_vector);

		//If the angle between looking_dir and forward vector is between (-90 and 90) degress 
		if (dot_product > 0)
		{
			up_vector = glm::rotate(up_vector, delta_y * mouse_sensitivity, side_vector);
			looking_dir_vector = glm::rotate(looking_dir_vector, delta_y * mouse_sensitivity, side_vector);
		}
		y_0 = y;
	}
}

void idle()
{
	//Calculating the delta time between two frames
	//We will use this delta time when moving forward (in keyboard function)
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	rotation += 0.04;
	glutPostRedisplay();
}

//---------------------------------------------------------------------
//
// main
//
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(1024, 1024);
	glutCreateWindow("Camera and Projection");
	glewInit();	//Initializes the glew and prepares the drawing pipeline.
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mouse);
	glutMainLoop();
}

void GameObject::draw(glm::vec3 scale, GLuint textureToUse, GLenum mode, GLuint verticesStart, GLuint verticesEnd)
{
	model_view = glm::scale(model_view, scale);
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	glBindTexture(GL_TEXTURE_2D, textureToUse);
	glDrawArrays(mode, verticesStart, verticesEnd);
	for (int k = 0; k < children.size(); k++)
	{
		glm::mat4 backup_tankWheel = model_view;
		model_view = glm::translate(model_view, children[k].location_);
		model_view = glm::rotate(model_view, rotation, glm::vec3(1, 0, 0));
		children[k].draw(glm::vec3(0.2f, 0.2f, 0.2f), texture[4], GL_QUADS, 28, 76);
		model_view = backup_tankWheel;
	}
}

void GameObject::render()
{
	glm::mat4 backup_tankBody = model_view;
	model_view = glm::translate(model_view, this->location_);
	draw(glm::vec3(1.5f, 1.5f, 1.5f), texture[3], GL_QUADS, 4, 24);
	model_view = backup_tankBody;
}

