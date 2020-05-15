// Name:  Brian Frempa-Dekyi
// Email: brian.dekyi@yahoo.com
// Program: PO2
// Title: SMFL
// Course: CMPS 2143
// Semester: Spring 2020
// Description: This is the main program to create the green circle

#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
