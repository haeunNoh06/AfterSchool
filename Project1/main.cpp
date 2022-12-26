#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {

	//640 x 480 윈도우 화면 나옴
	//잠깐 떴다가 사라지는 건 return 0때문에 프로그램이 종료된 것
	RenderWindow window(VideoMode(640, 480), "AfterSchool");
	window.setFramerateLimit(60);//1초에 60장 보여준다. 플레이어가 빨리 가지 않도록 하기

	//네모 모양의 플레이어
	RectangleShape player;
	player.setSize(Vector2f(40, 40));//플레이어 사이즈
	player.setPosition(100, 100);//플레이어 시작 위치
	player.setFillColor(Color::Red);//플레이어 색상
	int player_speed = 5;//플레이어 속도


	RectangleShape enemy;//적
	enemy.setSize(Vector2f(70, 70));//적 사이즈
	enemy.setPosition(500, 300);//적 시작 위치
	enemy.setFillColor(Color::Yellow);//적 색상


	//유지 시키는 방법은? -> 무한 반복
	while (window.isOpen()) //윈도우창이 열려있는 동안 계속 반복
	{ 
		Event event;//이벤트 생성
		while (window.pollEvent(event)) //이벤트가 발생. 이벤트가 발생해야 event 초기화가 됨
		{
			switch (event.type)
			{
				//종료(x)버튼을 누르면 Event::Closed(0) 
			case Event::Closed ://정수임
				window.close();//윈도우창이 닫힘
			}
		}

		//모두 if로 해서 방향키 동시적용
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.move(-1*player_speed, 0);//왼쪽 이동
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.move(0, -1 * player_speed);//위쪽 이동
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.move(0, player_speed);//아래쪽 이동
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.move(player_speed, 0);//오른쪽 이동
		}

		//intersects : 플레이어와 적 사이에서 교집합이 있는가
		if (player.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		{
			printf("enemy와의 충돌\n");
		}

		window.clear(Color::Black);//플레이어 자체 제거 (배경 지우기)


		//화면이 열려져 있는 동안 계속 그려야 함
		//draw는 나중에 호출할수록 우선순위가 높아짐
		window.draw(enemy);//적 보여주기
		window.draw(player);//플레이어 보여주기(그려주기)

		window.display();
	}

	return 0;
}