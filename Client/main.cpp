#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
	try {
		//�ϳ��� io_service��ü ����
		boost::asio::io_service i_s;
		//������ �̸��� tcp���������� �ٲٱ� ���� Resolver���
		tcp::resolver resolver(i_s);
		//�����δ� ���ü���, ���񽺴� Daytime �������� ����
		tcp::resolver::query query("localhost", "daytime");
		//dns�� ���� ip�ּ� �� ��Ʈ��ȣ ���
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		//���� ��ü�� �ʱ�ȭ�Ͽ� ������ ����
		tcp::socket socket(i_s);
		boost::asio::connect(socket, endpoint_iterator);
		while (1) {
			//���� �� ���� ó�� ���� ����
			boost::array<char, 128> buf;
			boost::system::error_code error;
			//���۸� ����� ������ ���� ������ �ޱ�
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof) {
				break;
			}
			else if (error) {
				throw boost::system::system_error(error);
			}
			//���ۿ� ��� �����͸� ȭ�鿡 ���
			cout.write(buf.data(), len);
		}
	}
	catch (exception &e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}