#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

/*returns specific files as a texture vector. Only works for image files right now.
Requires SFML, previous use of archiveWriter, vector, fstream*/
 void archiveReader(std::vector<sf::Texture> &texture, std::vector<int> &getFiles) {
	char * memblock;
	sf::Texture sTexture;
	std::string container;
	long long container2;
	std::vector<std::streampos> sizeVec;
	std::vector<std::streampos> startVec;
	std::ifstream in;
	startVec.push_back(0);
	in.open("archivedata.txt");
	int s = 0;
	bool totalCheck = true;
	while(std::getline(in, container)) {
		container2 = std::stol(container);
		if (!totalCheck) {
			sizeVec.push_back(container2);
			startVec.push_back(container2 + startVec[s]);
			++s;
		}
		else
			totalCheck = false;
	}
	in.close();
	in.clear();
	std::ofstream out;
	in.open("nl.can", std::ios::in | std::ios::binary | std::ios::beg);
	int c = 0;
	int b = 0;
	for (int a = getFiles[b]; b < getFiles.size(); ++b) {
		a = getFiles[b];
		memblock = new char[sizeVec[a]];
		in.seekg(startVec[a]);
		in.read(memblock, sizeVec[a]);
		texture.push_back(sTexture);
		texture[c].loadFromMemory(memblock, sizeVec[a]);
		++c;
		delete[] memblock;
	}
	in.close();
	in.clear();
}

 int main() {
	 std::vector<int> getFiles{ 1, 3 };
	 std::vector<sf::Texture> texture;
	 archiveReader(texture, getFiles);
	 std::vector<sf::Sprite> sprite;
	 sf::Sprite sSprite;
	 for (int a = 0; a < texture.size(); ++a) {
		 sprite.push_back(sSprite);
		 sprite[a].setTexture(texture[a]);
	 }
	 int b = 0;
	 int c = 0;
	 for (int a = 0; a < sprite.size(); a++) {
		 sprite[a].setPosition(b, c);
		 if (a % 2 == 0)
			 b += 500;
		 else
			 c += 200;
	 }
	 sf::RenderWindow window(sf::VideoMode(1000, 1000), "test");
	 window.setFramerateLimit(60);
	 while (window.isOpen()) {
		 sf::Event event;
		 while (window.pollEvent(event)) {
			 if (event.type == sf::Event::Closed)
				 window.close();
		 }
		 window.clear();
		 for (int a = 0; a < sprite.size(); ++a) {
			 window.draw(sprite[a]);
		 }
		 window.display();
	 }
 }