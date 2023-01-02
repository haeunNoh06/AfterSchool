#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

using namespace sf;

const int row = 4;
const int CARD_W = 300;
const int CARD_H = 200;

struct Card {
	RectangleShape sprite;
	int id;
	int type;
	int is_clicked;// 눌렸는가
};

int main(void) {

	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");// 화면 크기, 제목
	window.setFramerateLimit(60);// 60초마다 한 번씩 돌아간다

	// f : 소수
	// Vector2i : 정수
	Vector2i mouse_pos;// 마우스 좌표
	int flipped_num = 0;// 현재 뒤집혀진 카드의 갯수

	Texture t[8 + 1];
	t[0].loadFromFile("./resources/images/ch0.png");
	t[1].loadFromFile("./resources/images/ch1.png");
	t[2].loadFromFile("./resources/images/ch2.png");
	t[3].loadFromFile("./resources/images/ch3.png");
	t[4].loadFromFile("./resources/images/ch4.png");
	t[5].loadFromFile("./resources/images/ch5.png");
	t[6].loadFromFile("./resources/images/ch6.png");
	t[7].loadFromFile("./resources/images/ch7.png");
	t[8].loadFromFile("./resources/images/ch8.png");

	Font font;
	font.loadFromFile("c:/Windows/Fonts/arial.ttf");

	// 텍스트
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);// 글자 크기
	text.setFillColor(Color::White);
	text.setPosition(0, 0);
	char info[40];

	struct Card cards[row][row];
	int n = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cards[i][j].sprite.setSize(Vector2f(CARD_W, CARD_H));
			cards[i][j].sprite.setPosition(j * CARD_W, i * CARD_H);// j가 커질수록 x값이 100증가, i가 커질수록 y값이 200증가
			cards[i][j].sprite.setTexture(&t[0]);// 뒤집는 그림이 0이기 때문에 1부터
			cards[i][j].type = 1 + n / 2;
			cards[i][j].id = n + 1;
			cards[i][j].is_clicked = 0;
			n++;
		}
	}

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
					flipped_num++;// 필요없는 코드
					for (int i = 0; i < row; i++)
					{
						for (int j = 0; j < row; j++)
						{
							// 마우스는 점이므로 충돌이 아닌 포함관계를 나타내야 함
							if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							{
								cards[i][j].is_clicked = 1;// true
							}
						}
					}
				}
			}
		}
		
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				// 클릭하면 카드 뒤집기
				if (cards[i][j].is_clicked)
				{
					// 그림이 있는 스프라이트로 변경
					cards[i][j].sprite.setTexture(&t[cards[i][j].type]);
				}
			}
		}

		sprintf(info, "(%d, %d) clicks %d\n", mouse_pos.x, mouse_pos.y, flipped_num);
		text.setString(info);
		
		window.clear(Color::Black);

		window.draw(text);
		
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < row; j++)
			{
				window.draw(cards[i][j].sprite);
			}
		}

		window.display();
		
	}
	return 0;
}