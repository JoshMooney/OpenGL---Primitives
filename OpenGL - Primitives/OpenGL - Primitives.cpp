// OpenGL - Primitives.cpp : Defines the entry point for the console application.
//

//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 

#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int SCR_WIDTH, SCR_HEIGHT;
	SCR_HEIGHT = SCR_WIDTH = 600;
	sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT, 32), "OpenGL - Primitives");

	float increment = .01f;
	float distBetween = .125f;

	sf::Vector2f beginningPos = sf::Vector2f(-1 + (2.0/SCR_WIDTH), -1 + (2.0/SCR_HEIGHT));
	//sf::Vector2f beginningPos = sf::Vector2f(-1 * (SCR_WIDTH/2.0), -1 * (SCR_HEIGHT/2.0));
	//sf::Vector2f beginningPos = sf::Vector2f(10, 10);
	double pixalSize = -1 * (2.0 / SCR_WIDTH);
	float squareSize = -30 * pixalSize;
	//float squareSize = .05f;
	bool changed = true;
	bool colourSwap = true;
	int count = 0;

	int rows, col;
	rows = col = 7;

	vector<sf::Vector2f> points;

	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	{ distBetween += increment; cout << "Distance Between Squares :" << distBetween << endl; changed = true; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	{ distBetween -= increment; cout << "Distance Between Squares :" << distBetween << endl; changed = true; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	{ squareSize += increment; cout << "Square Size :"<< squareSize << endl; changed = true; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	{ squareSize -= increment; cout << "Square Size :"<< squareSize << endl; changed = true; }
			
			if (changed)
			{
				points.clear();
				for (int i = 0; i <= rows; i++)
					for (int j = 0; j <= col; j++)
					{
						points.push_back(sf::Vector2f((beginningPos.x + (squareSize + distBetween * i)), (beginningPos.y + (squareSize + distBetween * j))));
						points.push_back(sf::Vector2f((beginningPos.x + (squareSize + distBetween * i)), (beginningPos.y + (squareSize + distBetween * j) + squareSize)));
						points.push_back(sf::Vector2f((beginningPos.x + (squareSize + distBetween * i)) + squareSize, (beginningPos.y + (squareSize + distBetween * j) + squareSize)));
						points.push_back(sf::Vector2f((beginningPos.x + (squareSize + distBetween * i)) + squareSize, (beginningPos.y + (squareSize + distBetween * j))));
					}
				changed = false;
			}
		}

		

		//Prepare Frame
		window.clear();
		window.setFramerateLimit(500);

		//Drawing done here

		glBegin(GL_QUADS);
		//for (int i = 0; i <= points.size() - 1; i++)
		for (int i = 0; i <= points.size() - 1; i++)
		{
			if (colourSwap)
				glColor3f(1, 0, 0);
			else
				glColor3f(0, 1, 0);
			glVertex2d(points[i].x, points[i].y); //specify a point
			count++;
			if (count == 4)
			{
				if (colourSwap)
					glColor3f(1, 0, 0);
				else
					glColor3f(0, 1, 0);
				count = 0;
			}

		}
		glEnd(); //Triangle finished

		window.display();
	}
	return EXIT_SUCCESS;
}

