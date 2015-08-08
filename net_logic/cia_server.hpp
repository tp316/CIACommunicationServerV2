#ifndef CIA_SERVER_HPP_INCLUDE_
#define CIA_SERVER_HPP_INCLUDE_

#include "cia_client.hpp"
#include "../tools/boost_log.hpp"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
using namespace boost::asio;

class cia_server
{
public:
	cia_server(std::size_t io_comppletions_thread_number, std::size_t server_port);
	~cia_server();
protected:
	void handle_accept(cia_client::ptr client, const boost::system::error_code & err);
private:
	io_service m_io_service_;
	ip::tcp::acceptor m_acceptor_;
	boost::thread_group m_io_comppletions_thread_;
	io_service::work m_io_worker;
};

cia_server::cia_server(std::size_t io_comppletions_thread_number, std::size_t server_port) :
m_io_service_(), m_acceptor_(m_io_service_, ip::tcp::endpoint(ip::tcp::v4(), server_port)), m_io_worker(m_io_service_)
{
	cia_client::ptr client = cia_client::new_(m_io_service_, 10, 0);
	BOOST_LOG_SEV(cia_g_logger, Debug) << "服务器开始准备接收新的连接";
	m_acceptor_.async_accept(client->sock(), boost::bind(&cia_server::handle_accept,this, client, _1));
	BOOST_LOG_SEV(cia_g_logger, Debug) << "服务器开始创建异步IO处理线程";
	while (io_comppletions_thread_number--)
	{
		m_io_comppletions_thread_.create_thread([this](){
			m_io_service_.run();
		});
	}
}

void cia_server::handle_accept(cia_client::ptr client, const boost::system::error_code & err)
{
	BOOST_LOG_SEV(cia_g_logger, Debug) << "服务器接收到新的客户端连接";
	client->start();
	cia_client::ptr new_client = cia_client::new_(m_io_service_, 10, 0);
	BOOST_LOG_SEV(cia_g_logger, Debug) << "服务器开始准备接收新的连接";
	m_acceptor_.async_accept(new_client->sock(), boost::bind(&cia_server::handle_accept, this, new_client, _1));
}

cia_server::~cia_server()
{
	BOOST_LOG_SEV(cia_g_logger, Debug) << "服务器析构";
}

#endif	// !CIA_SERVER_HPP_INCLUDE_