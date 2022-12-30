#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

using namespace sf;

int main(void) {

	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");// 화면 크기, 제목
	window.setFramerateLimit(60);// 60초마다 한 번씩 돌아간다

	// f : 소수
	// Vector2i : 정수
	Vector2i mouse_pos;// 마우스 좌표
	int click_cnt = 0;// 마우스 누른 횟수

	// 폰트
	Font font;
	font.loadFromFile("c:/Windows/Fonts/arial.ttf");

	// 텍스트
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);// 글자 크기
	text.setFillColor(Color::White);
	text.setPosition(0, 0);
	char info[40];

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);// 마우스 좌표 실시간으로 받기

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			// 한 번 누르면 한 번만 적용
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					click_cnt++;
				}
			}
		}
		
		sprintf(info, "(%d, %d) clicks %d\n", mouse_pos.x, mouse_pos.y, click_cnt);
		text.setString(info);
		
		window.clear(Color::Black);

		window.draw(text);

		window.display();
		
	}
	return 0;
}