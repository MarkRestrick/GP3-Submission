#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


//#include <windows.h>
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cColours.h"
#include "cShapes.h"
#include "cPyramid.h"
#include "cCube.h"
#include "cSphere.h"
#include "cMaterial.h"
#include "cLight.h"
#include "cStarfield.h"
#include "cFontMgr.h"
#include "cCamera.h"
#include "BoxCollider.h"
#include "Cuboid.h"
#include <list>
#include <vector>
#include <Mmsystem.h>
#include <mciapi.h>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{
	//PlaySound(TEXT("footstep.wav"), NULL, SND_SYNC);
    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;

	int score = 0;

    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

    //The example OpenGL code
    windowOGL theOGLWnd;

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Sphere
	//cSphere theSun(4, 40, 40);
	//cSphere theEarth(3,30,30);
	//cSphere theMoon(1, 20, 20);

	Cuboid thePlayer;
	Cuboid grassBlock[30];
	Cuboid floorPanel[50];
	
	std::list<BoxCollider> colliderList;
	std::list<BoxCollider>::iterator it;
	it = colliderList.begin();


	cSphere collectable[9];
	BoxCollider collectableCollider[9];
	for (int z = 0; z < 9; z++)
	{
		collectable[z].setup(4, 40, 40);
	}
	

	//Collision
	//BoxCollider sunCollider;
	//sunCollider.setup(4.5, 4.5, 4.5, glm::vec3(0, 0, 40));
	//colliderList.insert(it, sunCollider);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Play BGM
	PlaySound(TEXT("theme.wav"), NULL, SND_ASYNC | SND_LOOP);
	// Create Texture map
	
	cTexture earthTexture;
	earthTexture.createTexture("Images/Earth.png");
	/*
	cTexture moonTexture;
	moonTexture.createTexture("Images/Moon.png");
	cTexture sunTexture;
	sunTexture.createTexture("Images/Sun.png");
	*/
	cTexture starTexture;
	starTexture.createTexture("Images/star.png");
	
	cTexture goldTexture;
	goldTexture.createTexture("Images/goldTest.png");

	// the starfield
	cStarfield theStarField(starTexture.getTexture(), glm::vec3(50.0f, 50.0f, 50.0f));

	
	//theSun.initialise(sunTexture.getTexture(), glm::vec3(0, 0, 40), glm::vec3(0, 0, 0));
	//////////////////////////////////////////////////////////////////////////////////////////
	// COLLECTABLES
	//////////////////////////////////////////////////////////////////////////////////////////
	collectable[0].initialise(goldTexture.getTexture(), glm::vec3(175, 0, 1), glm::vec3(0, 0, 0));
	collectable[1].initialise(goldTexture.getTexture(), glm::vec3(4, 0, 26), glm::vec3(0, 0, 0));
	collectable[2].initialise(goldTexture.getTexture(), glm::vec3(37, 0, 38), glm::vec3(0, 0, 0));
	collectable[3].initialise(goldTexture.getTexture(), glm::vec3(182, 0, 19), glm::vec3(0, 0, 0));
	collectable[4].initialise(goldTexture.getTexture(), glm::vec3(61, 0, 36), glm::vec3(0, 0, 0));
	collectable[5].initialise(goldTexture.getTexture(), glm::vec3(130, 0, 70), glm::vec3(0, 0, 0));
	collectable[6].initialise(goldTexture.getTexture(), glm::vec3(115, 15, 72), glm::vec3(0, 0, 0));
	collectable[7].initialise(goldTexture.getTexture(), glm::vec3(130, 20, 70), glm::vec3(0, 0, 0));
	collectable[8].initialise(goldTexture.getTexture(), glm::vec3(50, 20, 65), glm::vec3(0, 0, 0));

	for (int b = 0; b < 9; b++)
	{
		collectableCollider[b].setup(10, 10, 10, collectable[b].getPosition());
	}
	//////////////////////////////////////////////////////////////////////////////////////////
	// COLLIDERS
	//////////////////////////////////////////////////////////////////////////////////////////
	//sunCollider.setTransform(theSun.getPosition());
	BoxCollider grassCollider;
	grassCollider.setup(220, 40, 1, glm::vec3(90, 0, -12));
	colliderList.insert(it, grassCollider);

	BoxCollider grassCollider2;
	grassCollider2.setup(200, 40, 1, glm::vec3(90, 0, 92));
	colliderList.insert(it, grassCollider2);

	BoxCollider grassCollider3;
	grassCollider3.setup(1, 40, 130, glm::vec3(-12, 0, 45));
	colliderList.insert(it, grassCollider3);

	BoxCollider grassCollider4;
	grassCollider4.setup(1, 40, 130, glm::vec3(192, 0, 45));
	colliderList.insert(it, grassCollider4);

	BoxCollider grassCollider5;
	grassCollider5.setup(100, 20, 1, glm::vec3(40, 0, 12));
	colliderList.insert(it, grassCollider5);

	BoxCollider grassCollider6;
	grassCollider6.setup(100, 20, 1, glm::vec3(150, 0, 12));
	colliderList.insert(it, grassCollider6);

	BoxCollider grassCollider7;
	grassCollider7.setup(10, 5, 35, glm::vec3(150, -2, -6));
	colliderList.insert(it, grassCollider7);

	BoxCollider grassCollider8;
	grassCollider8.setup(50, 20, 1, glm::vec3(0, 0, 45));
	colliderList.insert(it, grassCollider8);

	BoxCollider grassCollider9;
	grassCollider9.setup(1, 20, 33, glm::vec3(25, 0, 29));
	colliderList.insert(it, grassCollider9);

	BoxCollider grassCollider10;
	grassCollider10.setup(25, 20, 1, glm::vec3(37.5, 0, 45));
	colliderList.insert(it, grassCollider10);

	BoxCollider grassCollider11;
	grassCollider11.setup(1, 20, 17, glm::vec3(50, 0, 37));
	colliderList.insert(it, grassCollider11);

	BoxCollider grassCollider12;
	grassCollider12.setup(115, 20, 1, glm::vec3(108, 0, 29));
	colliderList.insert(it, grassCollider12);

	BoxCollider grassCollider13;
	grassCollider13.setup(115, 20, 1, glm::vec3(108, 0, 45));
	colliderList.insert(it, grassCollider13);

	BoxCollider grassCollider14;
	grassCollider14.setup(1, 20, 35, glm::vec3(98, 0, 63));
	colliderList.insert(it, grassCollider14);
	/////////////////////////////////////////////////////////////////////////////////////////

	//theEarth.initialise(earthTexture.getTexture(), glm::vec3(10, 0, 20), glm::vec3(0, 0, 0));
	//float earthRotSpeed = 3.0f;
	//GLfloat earthOrbit = 0.0f;

	//theMoon.initialise(moonTexture.getTexture(), glm::vec3(10, 5, 8), glm::vec3(0, 0, 0));
	//float moonRotSpeed = 5.0f;
	//GLfloat moonOrbit = 0.0f;

	

 	// Create Materials for lights
	cMaterial sunMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);
	cMaterial earthMaterial(lightColour4(0.2f, 0.2f, 0.2f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 50.0f);
	cMaterial moonMaterial(lightColour4(0.1f, 0.1f, 0.1f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0.2f, 0.2f, 0.2f, 1.0f), lightColour4(0, 0, 0, 1.0f), 10.0f);
	// Create Light
	cLight sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 20, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	//Define Ambient light for scene
	GLfloat g_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);

	glClearColor(0.3, 0.5, 0.75, 1); //SetThe background colour to be blue-ish instead of black

	// load game fonts
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	// Create a camera
	cCamera theCamera;
	theCamera.setTheCameraPos(glm::vec3(0.0f, 0.0f, 0.0f));
	theCamera.setTheCameraRot(glm::vec3(0.0f, 0.0f, 0.0f));
	theCamera.setTheCameraLookAt(glm::vec3( 1.0f, 0.0f, 0.0f));

	theCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	theCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	theCamera.setTheProjectionMatrix(45.0f, theCamera.getTheCameraAspectRatio(), 0.1f, 1000.0f);
	//theCamera.update();

	//GLfloat cameraRotRadius = 80.0f;
	//GLfloat cameraRotationAngle = 0.0f;
	bool moving = false;
   //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

		
		if (soundToggledThisFrame)
		{
			soundToggledThisFrame = false;
			if (soundToggle)
			{
				//Play BGM
				PlaySound(TEXT("theme.wav"), NULL, SND_ASYNC | SND_LOOP);
			}
			else
			{
				PlaySound(NULL, 0, 0);
			}
		}

		if (camJump)
		{
			theCamera.jump();
		}

		//theCamera.setGrounded(sunCollider.checkCollision(theCamera.getTheCameraPos()));

		for (int c = 0; c < 9; c++)
		{
			if (!collectableCollider[c].getCollected())
			{
				bool collectCollision = collectableCollider[c].checkCollision(theCamera.getTheCameraPos());
				if (collectCollision)
				{
					collectableCollider[c].setCollected(true);
					score++;
				}
			}

		}
		
		if (camFor || camBack || camLeft || camRight)
		{
			if (!moving)
			{
				//PlaySound(TEXT("footstep.wav"), NULL, SND_ASYNC | SND_LOOP);
				//moving = true;
			}
			
			bool canMove = true;
			for (it = colliderList.begin(); it != colliderList.end(); ++it)
			{
				bool collided = it->checkCollision(theCamera.getTheCameraPos());
				if (collided)
				{
					canMove = false;
				}
			}

			

			if (canMove)
			{
				
				
				if (camFor)
				{
					theCamera.move("forward");
				}
				if (camBack)
				{
					theCamera.move("back");
				}
				if (camLeft)
				{
					theCamera.move("left");
				}
				if (camRight)
				{
					theCamera.move("right");
				}
				
			}
			else
			{
				if (camFor)
				{
					theCamera.move("back");
				}
				if (camBack)
				{
					theCamera.move("forward");
				}
				if (camLeft)
				{
					theCamera.move("right");
				}
				if (camRight)
				{
					theCamera.move("left");
				}
			}
			

		
			//CheckCollisions(theCamera.getTheCameraPos());
		}
		else
		{
			//If not moving stop playing moving sound
			//PlaySound(NULL, 0, 0);
			//moving = false;
		}


		camFor = false;
		camBack = false;
		camLeft = false;
		camRight = false;
		camJump = false;
		
		if (mouseMove)
		{
			theCamera.mouseRotation();
			mouseMove = false;
		}
		

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();
		
		// Lab code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL(windowWidth,windowHeight);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (camToggle)
		{
			glLoadMatrixf((GLfloat*)&theCamera.getTheViewMatrix());
		}
		else
		{
			glLoadMatrixf((GLfloat*)&theCamera.getTheViewMatrix2());
		}
		

		//Far wall on z axis
		grassBlock[0].initialise(earthTexture.getTexture(), glm::vec3(90, 0, -12), 220, 40, 1, 0, 0.5, 0);
		//near wall on z axis
		grassBlock[1].initialise(earthTexture.getTexture(), glm::vec3(90, 0, 92), 200, 40, 1, 0, 0.4, 0);
		//close wall on x axis
		grassBlock[2].initialise(earthTexture.getTexture(), glm::vec3(-12, 0, 45), 1, 40, 130, 0, 0.3, 0);
		//far wall on x axis
		grassBlock[3].initialise(earthTexture.getTexture(), glm::vec3(192, 0, 45), 1, 40, 130, 0, 0.3, 0);
		//The above 4 walls enclose the arena, next we'll create a series of walls within the arena to create a series of corridors for the player to navigate
		//Straight corridor with obstacle at end
		//Corridor 1 wall 1
		grassBlock[4].initialise(earthTexture.getTexture(), glm::vec3(40, 0, 12), 100, 20, 1, 0.2, 0.5, 0.4);
		//Corridor 1 wall 2
		grassBlock[5].initialise(earthTexture.getTexture(), glm::vec3(150, 0, 12), 100, 20, 1, 0.2, 0.5, 0.5);
		//Corridor 1 obstacle
		grassBlock[6].initialise(earthTexture.getTexture(), glm::vec3(150, -2, -6), 10, 5, 35, 0.2, 0.2, 0.8);
		//Hidden square room over the wall from the spawn location
		//Hidden room wall 1
		grassBlock[7].initialise(earthTexture.getTexture(), glm::vec3(0, 0, 45), 50, 20, 1, 0.6, 0.2, 0.2);
		//Hidden room wall 2
		grassBlock[8].initialise(earthTexture.getTexture(), glm::vec3(25, 0, 29), 1, 20, 33, 0.6, 0.2, 0.2);
		//L shaped corridor connected to first corridor
		//Corridor 2 wall 1
		grassBlock[9].initialise(earthTexture.getTexture(), glm::vec3(37.5, 0, 45), 25, 20, 1, 0.3, 0.2, 0.1);
		//Corridor 2 wall 2
		grassBlock[10].initialise(earthTexture.getTexture(), glm::vec3(50, 0, 37), 1, 20, 17, 0.35, 0.21, 0.09);
		//Corridor 2 wall 3
		grassBlock[11].initialise(earthTexture.getTexture(), glm::vec3(108, 0, 29), 115, 20, 1, 0.3, 0.2, 0.1);
		//Straight corridor
		grassBlock[12].initialise(earthTexture.getTexture(), glm::vec3(108, 0, 45), 115, 20, 1, 0.3, 0.2, 0.1);
		//Open room
		grassBlock[13].initialise(earthTexture.getTexture(), glm::vec3(98, 0, 63), 1, 20, 35, 0.35, 0.21, 0.09);

		//Represent the player as a white cube if using area camera
		if (!camToggle)
		{
			thePlayer.initialise(earthTexture.getTexture(), theCamera.getTheCameraPos(), 2, 2, 2, 1, 1, 1);
		}
		
		
		for (int p = 0; p < 50; p++)
		{
			float zPos;
			if (p <= 9)
			{
				zPos = 0;
			}
			else if(p > 9 && p <=19)
			{
				zPos = 20;
			}
			else if (p > 19 && p <= 29)
			{
				zPos = 40;
			}
			else if (p > 29 && p <= 39)
			{
				zPos = 60;
			}
			else if (p > 39 && p <= 49)
			{
				zPos = 80;
			}

			float xPos;
			if (p <= 9)
			{
				xPos = p *20;
			}
			else if (p > 9 && p <= 19)
			{
				xPos = (p - 10) * 20;
			}
			else if (p > 19 && p <= 29)
			{
				xPos = (p - 20) * 20;
			}
			else if (p > 29 && p <= 39)
			{
				xPos = (p - 30) * 20;
			}
			else if (p > 39 && p <= 49)
			{
				xPos = (p - 40) * 20;
			}

			floorPanel[p].initialise(earthTexture.getTexture(), glm::vec3(xPos, -5, zPos), 20, 1, 20, 0.5/(p/8), 0.5/(p/8), 0.5/(p/8));
		}
		
		

		glPushMatrix();
		theStarField.render(0.0f);

		//theSun.prepare(0.0f);
		sunMaterial.useMaterial();
		sunLight.lightOn();
		//theSun.render(theSun.getRotAngle());

		for (int a = 0; a < 9; a++)
		{
			if (!collectableCollider[a].getCollected())
			{
				collectable[a].render(collectable[a].getRotAngle());
			}
			
		}
		
		
		// Earth's orbit
		//glPushMatrix();
		//theEarth.setRotAngle(theEarth.getRotAngle() + (earthRotSpeed*elapsedTime));
		//theEarth.prepare(theEarth.getRotAngle()); //Do any pre-rendering logic
		//earthMaterial.useMaterial();				// Set the material for use
		//theEarth.render(theEarth.getRotAngle()); //Render the scene
		// Moon's orbit
		//glPushMatrix();
		//theMoon.setRotAngle(theMoon.getRotAngle() + (moonRotSpeed*elapsedTime));
		//theMoon.prepare(rotationAngle);
		//moonMaterial.useMaterial();
		//theMoon.render(theMoon.getRotAngle());
		//glPopMatrix();
		//glPopMatrix();
		//glPopMatrix();

		//glPushMatrix();
		theOGLWnd.setOrtho2D(windowWidth, windowHeight);

		///////////////////////////////////////////////////////////////////////////////////////////////
		// DEBUG TEXT
		///////////////////////////////////////////////////////////////////////////////////////////////

		//CameraPos
		theFontMgr->getFont("Space")->printText((std::to_string(theCamera.getTheCameraPos().x)).c_str(), FTPoint(10, 15, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(theCamera.getTheCameraPos().y)).c_str(), FTPoint(10, 30, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(theCamera.getTheCameraPos().z)).c_str(), FTPoint(10, 45, 0.0f));
		theFontMgr->getFont("Space")->printText("Score: ", FTPoint(10, 60, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(score)).c_str(), FTPoint(130, 60, 0.0f));
		theFontMgr->getFont("Space")->printText("/9", FTPoint(150, 60, 0.0f));


		/*
		//SunPos
		theFontMgr->getFont("Space")->printText((std::to_string(theSun.getPosition().x)).c_str(), FTPoint(500, 15, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(theSun.getPosition().y)).c_str(), FTPoint(500, 30, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(theSun.getPosition().z)).c_str(), FTPoint(500, 45, 0.0f));

		//SunColliderPos
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPosition().x)).c_str(), FTPoint(500, 60, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPosition().y)).c_str(), FTPoint(500, 75, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPosition().z)).c_str(), FTPoint(500, 90, 0.0f));

		//SunColliderPosHigh
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPositionHigh().x)).c_str(), FTPoint(500, 110, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPositionHigh().y)).c_str(), FTPoint(500, 125, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPositionHigh().z)).c_str(), FTPoint(500, 140, 0.0f));

		//SunColliderPosLow
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPositionLow().x)).c_str(), FTPoint(500, 160, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPositionLow().y)).c_str(), FTPoint(500, 175, 0.0f));
		theFontMgr->getFont("Space")->printText((std::to_string(sunCollider.getPositionLow().z)).c_str(), FTPoint(500, 190, 0.0f));
		*/

		glPopMatrix();

		pgmWNDMgr->swapBuffers();

		glm::vec3 currentCameraPos = theCamera.getTheCameraPos();
		//GLfloat posX = (glm::sin(glm::radians(cameraRotationAngle)) * cameraRotRadius); // *elapsedTime;
		//GLfloat posZ = (glm::cos(glm::radians(cameraRotationAngle)) * cameraRotRadius); // *elapsedTime;
		//theCamera.setTheCameraPos(glm::vec3(posX, 0.0f, posZ));
		theCamera.update();

		//cameraRotationAngle -= (5.0f * elapsedTime);
	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}

void CheckCollisions(glm::vec3 position)
{

}