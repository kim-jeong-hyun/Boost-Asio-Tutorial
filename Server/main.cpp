#define _CRT_SECURE_NO_WARNINGS
#include <ctime> //���� �ð� �ҷ��������ϱ� ����
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

//���� ��ǻ���� ��¥ �� �ð� ���� ��ȯ
string make_daytime_string() {
	time_t now = time(0); //�ð����� �ʱ�ȭ
	return ctime(&now);
}

int main() {
	try {
		cout<<"[BOOST ASIO SERVER Ver0.2]\n"
		//80�� ��Ʈ : HTTP�������� / 13�� ��Ʈ : DAY_TIME ��������
		//�⺻������ Boost Asio ���α׷� -> �ϳ��� IO Service ��ü ����
		boost::asio::io_service i_s;
		//tcp���������� 13�� ��Ʈ�� ������ �޴� ���� ���� ����
		tcp::acceptor acceptor(i_s, tcp::endpoint(tcp::v4(), 13));
		//��� Ŭ���̾�Ʈ�� ���� ������ �ݺ� ����
		while (1) {
			//���� ��ü�� ������ ���� ��ٸ�
			tcp::socket socket(i_s);
			acceptor.accept(socket);
			//������ �Ϸ�Ǹ� �ش� Ŭ���̾�Ʈ���� ���� �޽��� ����
			string msg = make_daytime_string();
			//�ش� Ŭ���̾�Ʈ���� �޽����� ��� ����
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
		}
	}
	catch (exception &e) {
		cerr << e.what() << '\n';
	}
	return 0;
}
