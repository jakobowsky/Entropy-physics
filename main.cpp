#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>


int main()
{
	
	
	int r;
	std::cout << "Input(r):  ";
	std::cin >> r;

	int R = 2*r+1;
	int P = r+(1-r%2);

	std::vector <long long> wykres;

	srand(time(NULL));
	//Particle Simulation
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Simulation");
	//window.setFramerateLimit(60);
	
	int **matrixPosition = new int *[R];
	for (int i = 0; i < R; i++)
		matrixPosition[i] = new int[R];
	for (int i = 0; i < R; i++)
		for (int j = 0; j < R; j++)
			matrixPosition[i][j] = 0;
			

	int **matrixMomentum = new int*[P];
	for (int i = 0; i < P; i++)
		matrixMomentum[i] = new int[P];
	for (int i = 0; i < P; i++)
		for (int j = 0; j < P; j++)
			matrixMomentum[i][j] = 0;

	//Point to chart
	sf::CircleShape point;
	point.setRadius(1.f);

	//Bar
	sf::RectangleShape bar;
	bar.setSize(sf::Vector2f(15, 600));
	bar.setFillColor(sf::Color::White);
	bar.setPosition(sf::Vector2f(500.f , 0.f));

	//timer
	int timer = 200;
	std::vector <int> times;
	std::vector <sf::Vector2f> positionOfTimes;
	sf::Text text;
	sf::Font font;
	font.loadFromFile("Fonts/Metropolian-Display.ttf");
	text.setFont(font);

	//Particles
	sf::CircleShape particle;
	particle.setRadius(5.f);
	particle.setOrigin(5.f, 5.f);
	std::vector<sf::CircleShape> particles;
	int numberOfParticles = pow(2, r);
	std::vector<sf::Vector2f> momentumOfParticles;
	std::vector<sf::Vector2f> directionOfParticles;
	float vx, vy;
	float x, y;
	for (int i = 0; i < numberOfParticles; i++)
	{
			particle.setPosition((rand() % int(window.getSize().x / 50 - particle.getRadius())), (rand() % int(window.getSize().y - particle.getRadius())));
			particles.push_back(sf::CircleShape(particle));
			vx = (float)(rand() % 600 - 1)/500.f + 0.1;
			vy = (float)(rand() % 600 - 1)/500.f+ 0.1;
			x = rand() % 2;
			y = rand() % 2;

			while (true)
			{
				vx = (float)(rand() % 600 - 1) / 500.f + 0.1;
				vy = (float)(rand() % 600 - 1) / 500.f + 0.1;
				if (vx != 0 && vy != 0) break;
			}
			momentumOfParticles.push_back(sf::Vector2f(vx, vy));
			directionOfParticles.push_back(sf::Vector2f(x, y));
	}
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		
		//Calculate


		//Position
		float x1, x2;
		int lenOfR = 500 / R;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < R; j++)
				matrixPosition[i][j] = 0;

		
		for (int i = 0; i < particles.size(); i++)
		{
			int a, b;
			a = particles[i].getPosition().x / (int)lenOfR;
			b = particles[i].getPosition().y / (int)lenOfR;
			if (a == R)
				a -= 1;
			if (b == R)
				b -= 1;
			matrixPosition[a][b]++;
		}


		

		////////////// Chart //////////////

		
		long long lnP = 0;
		for (int i = 0; i<R; i++)
		{
			for (int j = 0; j<R; j++)
			{
				if (matrixPosition[i][j]>0)
				{
					lnP -= matrixPosition[i][j] * log(float(matrixPosition[i][j])) - matrixPosition[i][j];
				}

			}
		}
		lnP += numberOfParticles*log(float(numberOfParticles)) - numberOfParticles;

		wykres.push_back(lnP);
		
		point.setPosition(520, 400);



		/*
		//Momentum
		float lenOfP = 500 / P;
		for (int i = 0; i < P; i++)
			for (int j = 0; j < P; j++)
				matrixMomentum[i][j] = 0;


		for (int i = 0; i < P; i++)
			for (int j = 0; j < P; j++)
			{
				x1 = lenOfP * i;
				x2 = lenOfP * i + lenOfP;
				int counterOfParticles = 0;
				for (int k = 0; k < particles.size(); k++)
				{
					if (((particles[k].getPosition().x + particles[k].getRadius() >= x1) && (particles[k].getPosition().x + particles[k].getRadius()< x2))
						&& ((particles[k].getPosition().y + particles[k].getRadius() >= x1) && (particles[k].getPosition().y + particles[k].getRadius()< x2)))
						matrixMomentum[i][j]++;
				}
			}

			*/


		//Update Particles
		for (int i = 0; i < particles.size(); i++) //checking collison
		{
			if (particles[i].getPosition().x <= 0)
				directionOfParticles[i].x = 1;
			else if(particles[i].getPosition().x + 2*particles[i].getRadius()>= bar.getPosition().x)
				directionOfParticles[i].x = 0;

			if (particles[i].getPosition().y <= 0)
				directionOfParticles[i].y = 1;
			else if (particles[i].getPosition().y + 2 * particles[i].getRadius() >= window.getSize().y)
				directionOfParticles[i].y = 0;

			if (directionOfParticles[i].x)
				momentumOfParticles[i].x = abs(momentumOfParticles[i].x);
			else
				momentumOfParticles[i].x = -abs(momentumOfParticles[i].x);

			if (directionOfParticles[i].y)
				momentumOfParticles[i].y = abs(momentumOfParticles[i].y);
			else
				momentumOfParticles[i].y = -abs(momentumOfParticles[i].y);
		}


		for (int i = 0; i < particles.size(); i++)
		{
			particles[i].move(momentumOfParticles[i]);
		}

		//Draw

		window.clear();


		for (int i = 0; i < particles.size(); i++)
		{
			window.draw(particles[i]);
		}
		
		window.draw(bar);




		//Drawing chart
		for (int i = 0; i<wykres.size(); i++)
		{
			
			point.setPosition(point.getPosition().x, 400 - wykres[i] / (float)(numberOfParticles/R)*2);
			window.draw(point);
			point.setPosition(point.getPosition().x + 0.3, point.getPosition().y);

		}

		if (timer >= 200)
		{
			
			times.push_back(lnP);
			positionOfTimes.push_back(sf::Vector2f(point.getPosition().x, point.getPosition().y - 40.5f));
			timer = 0;
		}	
		else timer++;

		for (int i = 0; i < times.size(); i++)
		{
			
			
			text.setCharacterSize(20);
			text.setFillColor(sf::Color::Magenta);
			text.setString(std::to_string(times[i]));
			text.setPosition(positionOfTimes[i]);
			
			
			window.draw(text);
			
		}
		

		window.display();
		

	}


	for (int i = 0; i < R; i++)
		delete[] matrixPosition[i];
	delete[] matrixPosition;


	for (int i = 0; i < P; i++)
		delete[] matrixMomentum[i];
	delete[] matrixMomentum;

	

	return 0;
}













