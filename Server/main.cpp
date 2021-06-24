#define _CRT_SECURE_NO_WARNINGS
#include <ctime> //현재 시간 불러오도록하기 위함
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

//서버 컴퓨터의 날짜 및 시간 정보 반환
string make_daytime_string() {
	time_t now = time(0); //시간정보 초기화
	return ctime(&now);
}

int main() {
	try {
		cout<<"[BOOST ASIO SERVER Ver0.2]\n"
		//80번 포트 : HTTP프로토콜 / 13번 포트 : DAY_TIME 프로토콜
		//기본적으로 Boost Asio 프로그램 -> 하나의 IO Service 객체 가짐
		boost::asio::io_service i_s;
		//tcp프로토콜의 13번 포트로 연결을 받는 수동 소켓 생성
		tcp::acceptor acceptor(i_s, tcp::endpoint(tcp::v4(), 13));
		//모든 클라이언트에 대해 무한정 반복 수행
		while (1) {
			//소켓 객체를 생성해 연결 기다림
			tcp::socket socket(i_s);
			acceptor.accept(socket);
			//연결이 완료되면 해당 클라이언트에게 보낼 메시지 생성
			string msg = make_daytime_string();
			//해당 클라이언트에게 메시지를 담아 전송
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
		}
	}
	catch (exception &e) {
		cerr << e.what() << '\n';
	}
	return 0;
}
