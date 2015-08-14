#ifndef ZOO_KEEPER_HPP_INCLUDE_
#define ZOO_KEEPER_HPP_INCLUDE_
#include "../system/include_sys.h"
#include "boost_log.hpp"
#include <zookeeper.h>
#include <string>
#include <boost/thread.hpp>

const int buffer_len = 4069; // zookeeper 取值字符串缓冲区大小

/**
 * \brief zookeeper 处理类, 封装设值 和 取值 等操作
 *
 * \author LYL QQ-331461049
 * \date 2015/08/12 13:31
 */
class zoo_keeper
{
public:
	zoo_keeper(std::string hostPort);
	~zoo_keeper();

	std::string get_data(std::string node);
	bool set_data(std::string node, std::string value);

private:
	zhandle_t *zh;	        // 指向zookeeper集群的指针
	clientid_t myid;        // 保存当前连接zookeeper集群的客户端ID
	std::string m_hostPort; // zookeeper集群的 IP:端口 标识
};

/**
 * \brief
 *
 * \param host 逗号分隔的 IP:端口 标识, 每个关联一个 zk 服务端, 如:"127.0.0.1:3000,127.0.0.1:3001,127.0.0.1:3002"
 */
zoo_keeper::zoo_keeper(std::string hostPort)
{
	zh = zookeeper_init(hostPort.c_str(), NULL, 30000, &myid, 0, 0);
	if (!zh) {
		BOOST_LOG_SEV(cia_g_logger, Critical) << "无法连接zookeeper服务器";
		throw std::exception("无法连接zookeeper服务器");
	}
	while (zoo_state(zh) != ZOO_CONNECTED_STATE)
	{
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	}
	BOOST_LOG_SEV(cia_g_logger, RuntimeInfo) << "zookeeper已经初始化完毕";
}

zoo_keeper::~zoo_keeper()
{
	zookeeper_close(zh);
	BOOST_LOG_SEV(cia_g_logger, RuntimeInfo) << "zookeeper析构完毕";
}

/**
 * \brief 通过zookeeper路径地址获取对应的值
 *
 * \param node 路径节点, 注意需以/开头
 * \return 节点对应的值, 由于zookeeper的特性, 所有节点值均为字符串类型
 */
std::string zoo_keeper::get_data(std::string node)
{
	BOOST_LOG_SEV(cia_g_logger, Debug) << "zookeeper:待取值节点为" << node;
	if (node.at(0) != '/')
	{
		BOOST_LOG_SEV(cia_g_logger, Debug) << "zookeeper:get_data 入参非法, 节点信息必须以 / 开头, 传入的参数为" << node;
		return "";
	}
	char buffer[4069];             // 缓存获取到的节点值
	int re_value_len = buffer_len; // 节点值的长度, 注意此变量同时起到两个作用, 1:入参, 告诉zookeeper缓冲区长度, 2:出参, 告诉函数调用者节点值的长度
	int rc;
	rc = zoo_get(zh, node.c_str(), 0, buffer, &re_value_len, NULL);
	switch (rc)
	{
	case ZOK:
		return std::string(buffer, re_value_len);
		break;
	case ZNONODE:
		BOOST_LOG_SEV(cia_g_logger, Critical) << "zookeeper:zoo_aget 函数待获取节点不存在";
		break;
	case ZNOAUTH:
		BOOST_LOG_SEV(cia_g_logger, Critical) << "zookeeper:zoo_aget 函数, 当前客户端不具备此节点权限";
		break;
	case ZBADARGUMENTS:
		BOOST_LOG_SEV(cia_g_logger, Critical) << "zookeeper:zoo_aget 函数入参非法";
		break;
	case ZINVALIDSTATE:
		BOOST_LOG_SEV(cia_g_logger, Critical) << "zookeeper:zhandle 的状态为 ZOO_SESSION_EXPIRED_STATE 或 ZOO_AUTH_FAILED_STATE";
		break;
	case ZMARSHALLINGERROR:
		BOOST_LOG_SEV(cia_g_logger, Critical) << "zookeeper:请求失败, 可能内存已经溢出";
		break;
	default:
		break;
	}
	return "";
}

/**
 * \brief 通过zookeeper路径地址设置对应的值
 *
 * \param node 路径节点, 注意需以/开头
 * \param value 欲设置的值
 * \return true 设置成功 false 设置失败
 */
bool zoo_keeper::set_data(std::string node, std::string value)
{
	if (node.at(0) != '/')
	{
		BOOST_LOG_SEV(cia_g_logger, Debug) << "zookeeper:get_data 入参非法, 节点信息必须以 / 开头, 传入的参数为" << node;
		return false;
	}
	int rc = zoo_set(zh, node.c_str(), value.c_str(), value.size(), -1);
	if (rc == ZOK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif // !ZOO_KEEPER_HPP_INCLUDE_