/*#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include "font.h"
#include "overhead.h"
#include "texture.h"
#include <iostream>

void render(Overhead &overhead, SDL_Rect *clip, Texture &texture, double angle, SDL_Point *centre, SDL_RendererFlip flip) {
	SDL_Rect render = { texture.textData.x, texture.textData.y, texture.textData.w, texture.textData.h };
	SDL_RenderCopyEx(overhead.renderer, texture.texture, clip, &render, angle, centre, flip);
}

void close(Overhead &overhead, Font &font) {
	TTF_CloseFont(font.font);
	font.font = NULL;
	overhead.closeOverhead();
}

int main(int argc, char* args[]) {
	sf::Packet packet;
	sf::TcpSocket peer;
	sf::TcpListener listener;
	unsigned short port;
	std::string ip;
	sf::IpAddress ipaddress;
	char host;
	std::cout << "host (y/n): ";
	std::cin >> host;
	if (host == 'y') {
		std::cout << "port number to listen on: ";
		std::cin >> port;
		std::cout << "IP Address for local connection: " << sf::IpAddress::getLocalAddress() << std::endl;
		std::cout << "IP Address for remote connection: " << sf::IpAddress::getPublicAddress() << std::endl;
		if (listener.listen(port) != sf::Socket::Done)
			std::cout << "listener error" << std::endl;
		if (listener.accept(peer) == sf::Socket::Done) {
			std::cout << "connection successful" << peer.getRemoteAddress() << std::endl;
			std::cout << "socket number: " << peer.getLocalPort() << std::endl;
			std::cout << "remote port " << peer.getRemotePort() << std::endl;
		}
	}
	else {
		std::cout << "port number to connect to: ";
		std::cin >> port;
		std::cout << peer.getLocalPort();
		std::cout << "you chose port number " << port << std::endl;
		std::cout << "ip address to connect to: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cin >> ip;
		ipaddress = ip;
		std::cout << "you chose ip address " << ipaddress;
		sf::Socket::Status status = peer.connect(ipaddress, port);
		if (status != sf::Socket::Done) {
			std::cout << "cannot connect" << std::endl;
			std::cout << "error number: " << status;
		}
		else if (status == sf::Socket::Done) {
			std::cout << "connection successful" << std::endl;
			std::cout << "local port " << peer.getLocalPort() << std::endl;
			std::cout << "remote port " << peer.getRemotePort() << std::endl;
		}
	}
	std::string receive;
	bool run = true;
	SDL_Event event;
	int screenW = 800; int screenH = 600;
	Overhead overhead(screenW, screenH);
	bool textureUsed[5] = { false, false, false, false, false };
	bool isSent[4] = { false, false, false, false };
	std::string message[5];
	Texture texture[5];
	Font font;
	font.font = NULL;
	font.font = TTF_OpenFont("Roboto-Condensed.ttf", 18);
	SDL_Color black = { 0,0,0 };
	SDL_Color red = { 255, 0, 0 };
	for (int a = 0; a < 5; ++a) {
		texture[a].setIsText(true);
		texture[a].setFontIndex(0);
		texture[a].color = black;
	}
	char input = '\0';
	bool stringDone = false;
	bool backspace = false;
	std::string finalMessage;
	int y;
	finalMessage = ">";
	texture[4].setupTexture(overhead, finalMessage, texture[4].color, 0, 200, font);
	textureUsed[4] = true;
	while (run) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				run = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_a:
					input = 'a';
					break;
				case SDLK_b:
					input = 'b';
					break;
				case SDLK_c:
					input = 'c';
					break;
				case SDLK_d:
					input = 'd';
					break;
				case SDLK_e:
					input = 'e';
					break;
				case SDLK_f:
					input = 'f';
					break;
				case SDLK_g:
					input = 'g';
					break;
				case SDLK_h:
					input = 'h';
					break;
				case SDLK_i:
					input = 'i';
					break;
				case SDLK_j:
					input = 'j';
					break;
				case SDLK_k:
					input = 'k';
					break;
				case SDLK_l:
					input = 'l';
					break;
				case SDLK_m:
					input = 'm';
					break;
				case SDLK_n:
					input = 'n';
					break;
				case SDLK_o:
					input = 'o';
					break;
				case SDLK_p:
					input = 'p';
					break;
				case SDLK_q:
					input = 'q';
					break;
				case SDLK_r:
					input = 'r';
					break;
				case SDLK_s:
					input = 's';
					break;
				case SDLK_t:
					input = 't';
					break;
				case SDLK_u:
					input = 'u';
					break;
				case SDLK_v:
					input = 'v';
					break;
				case SDLK_w:
					input = 'w';
					break;
				case SDLK_x:
					input = 'x';
					break;
				case SDLK_y:
					input = 'y';
					break;
				case SDLK_z:
					input = 'z';
					break;
				case SDLK_0:
					input = '0';
				case SDLK_1:
					input = '1';
				case SDLK_2:
					input = '2';
				case SDLK_3:
					input = '3';
				case SDLK_4:
					input = '4';
				case SDLK_5:
					input = '5';
				case SDLK_6:
					input = '6';
				case SDLK_7:
					input = '7';
				case SDLK_8:
					input = '8';
				case SDLK_9:
					input = '9';
				case SDLK_RETURN:
					stringDone = true;
					break;
				case SDLK_BACKSPACE:
					backspace = true;
					break;
				}
			}
		}
		peer.setBlocking(false);
		if (peer.receive(packet) == sf::Socket::Done) {
			packet >> receive;
			for (int a = 0; a < 4; ++a) {
				y = 50 * a;
				if (a != 3 && message[a+1].length() > 0) {
					if (textureUsed[a])
						texture[a].removeTexture();
					message[a] = message[a + 1];
					texture[a].color = texture[a + 1].color;
					texture[a].setupTexture(overhead, message[a], texture[a].color, 0, y, font);
					textureUsed[a] = true;
				}
				if (a == 3) {
					message[a] = receive;
					texture[a].removeTexture();
					texture[a].color = red;
					texture[a].setupTexture(overhead, message[a], texture[a].color, 0, y, font);
					textureUsed[a] = true;
				}
			}
		}
		if (input != '\0' && message[4].length() < 30) {
			message[4] += input;
			finalMessage = ">" + message[4];
			texture[4].removeTexture();
			texture[4].setupTexture(overhead, finalMessage, texture[4].color, 0, 200, font);
			input = '\0';
		}
		else if (backspace && message[4].length() > 0) {
			message[4].pop_back();
			finalMessage = ">" + message[4];
			texture[4].removeTexture();
			texture[4].setupTexture(overhead, finalMessage, texture[4].color, 0, 200, font);
			backspace = false;
		}
		else if (backspace)
			backspace = false;
		if (input != '\0')
			input = '\0';
		if (stringDone && message[4].length() > 0) {
			packet << message[4];
			peer.setBlocking(true);
			peer.send(packet);
			for (int a = 0; a < 5; ++a) {
				if (a == 3)
					texture[a].color = black;
				if (a != 4 && textureUsed[a + 1]) {
					message[a] = message[a + 1];
					texture[a].color = texture[a + 1].color;
					if (textureUsed[a]) {
						texture[a].removeTexture();
					}
					y = 50 * a;
					texture[a].setupTexture(overhead, message[a], texture[a].color, 0, y, font);
					textureUsed[a] = true;
				}
				else if (a == 4) {
					message[a].clear();
					texture[4].removeTexture();
					finalMessage = ">";
					texture[4].setupTexture(overhead, finalMessage, texture[4].color, 0, 200, font);
				}
			}
			stringDone = false;
		}
		SDL_RenderClear(overhead.renderer);
		for (int a = 0; a < 5; ++a) {
			if(textureUsed[a])
				render(overhead, NULL, texture[a], 0.0, NULL, SDL_FLIP_NONE);
		}
		SDL_RenderPresent(overhead.renderer);
	}
	for (int a = 0; a < 5; ++a) {
		if (textureUsed[a])
			texture[a].removeTexture();
	}
	peer.disconnect();
	if (host == 'y')
		listener.close();
	close(overhead, font);
	return 0;
}*/