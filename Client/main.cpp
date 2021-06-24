#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
	try {
		//하나의 io_service객체 가짐
		boost::asio::io_service i_s;
		//도메인 이름을 tcp종단점으로 바꾸기 위해 Resolver사용
		tcp::resolver resolver(i_s);
		//서버로는 로컬서버, 서비스는 Daytime 프로토콜 적기
		tcp::resolver::query query("localhost", "daytime");
		//dns를 거쳐 ip주소 및 포트번호 얻기
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		//소켓 객체를 초기화하여 서버에 연결
		tcp::socket socket(i_s);
		boost::asio::connect(socket, endpoint_iterator);
		while (1) {
			//버퍼 및 오류 처리 변수 선언
			boost::array<char, 128> buf;
			boost::system::error_code error;
			//버퍼를 사용해 서버로 부터 데이터 받기
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof) {
				break;
			}
			else if (error) {
				throw boost::system::system_error(error);
			}
			//버퍼에 담긴 데이터를 화면에 출력
			cout.write(buf.data(), len);
		}
	}
	catch (exception &e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}