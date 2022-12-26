#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {

	//640 x 480 윈도우 화면 나옴
	//잠깐 떴다가 사라지는 건 return 0때문에 프로그램이 종료된 것
	RenderWindow window(VideoMode(640, 480), "AfterSchool");

	//유지 시키는 방법은? -> 무한 반복
	while (window.isOpen()) { //윈도우창이 열려있는 동안 계속 반복
		
		Event event;//이벤트 생성
		while (window.pollEvent(event)) {//이벤트가 발생. 이벤트가 발생해야 event 초기화가 됨
			//종료(x)버튼을 누르면
			if (event.type == Event::Closed)//Event::Closed라는 이벤트가 발생하면
				window.close();//윈도우창이 닫힘
		}

	}

	printf("Hello World");

	return 0;
}