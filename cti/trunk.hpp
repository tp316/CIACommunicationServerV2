#ifndef CTI_TRUNK_HPP_INCLUDED
#define CTI_TRUNK_HPP_INCLUDED

#include "../net_logic/base_client.hpp"

#include <string>
#include <atomic>
#include <memory>

#include <boost/timer.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost;

/**
 * 语音卡通道状态描述
 *
 * @author LYL QQ-331461049
 * @date 2015/07/16 18:28
 */
enum trunk_state {
	TRK_IDLE,	                            //空闲
	TRK_WAIT_CONNECT,	                    //被占用, 等待连接
	TRK_CALLOUT_DAIL,	                    //已拨号
	TRK_CHEK_BARGEIN	                    //检测铃音
};

/**
 * 依据不同号段， 会有不同的挂断延迟策略， 防止主叫方已经有响铃， 但是被叫方还没有收到来电， 导致提前挂机， 被叫方无来电记录的情况
 *
 * @author LYL QQ-331461049
 * @date 2015/07/16 18:22
 */
struct hungup_strategy
{
	string m_phone_number_head;	                    //手机号码前N位， 按不同号段的实际测试情况设置, 可以是186， 也可以是1860434， 用来指定号段
	int    m_warning_elapse;	                    //触发策略的呼叫响应间隔时间。 发起呼叫后， 如果在设定的时间内触发响铃， 则属于“超前”响铃时间， 需要延迟挂机
	int    m_sleeping_elapse;	                    //触发策略后， 延迟多长时间挂机

	hungup_strategy() = default;

	/**
	 * 创建一个新的号码挂断延迟策略
	 *
	 * @param phone_number_head 手机号码前N位， 按不同号段的实际测试情况设置, 可以是186， 也可以是1860434， 用来指定号段
	 * @param warning_elapse 触发策略的呼叫响应间隔时间。 发起呼叫后， 如果在设定的时间内触发响铃， 则属于“超前”响铃时间， 需要延迟挂机
	 * @param sleeping_elapse 触发策略后， 延迟多长时间挂机
	 */
	hungup_strategy(const string& phone_number_head, int warning_elapse, int sleeping_elapse) : m_phone_number_head(phone_number_head)
	{
		m_warning_elapse = warning_elapse;
		m_sleeping_elapse = sleeping_elapse;
	}

	/**
	 * 比较号码是否符合延迟策略， 指定的策略是手机号码的前几位， 就比较被叫号码的前几位
	 *
	 * @param full_phone_number 被叫手机号码
	 * @return true 被叫手机号码符合此策略 false 被叫号码不符合此策略
	 */
	bool equals(string& full_phone_number){
		int strategy_phone_number_size = m_phone_number_head.length();
		if (full_phone_number.at(0) == '0')
			return full_phone_number.substr(1, strategy_phone_number_size) == m_phone_number_head;
		else
			return full_phone_number.substr(0, strategy_phone_number_size) == m_phone_number_head;
	}
};

/**
 * 每个语音卡， 都会有 （中继线数量 * 30） 个通道， 每次呼叫都会占用一个通道
 * 此类保存每次呼叫时， 语音卡通道的相关信息
 *
 * @author LYL QQ-331461049
 * @date 2015/07/16 18:35
 */
class trunk
{
public:
	trunk_state          m_step;	                        //当前通道的状态
	string               m_caller_id;	                    //主叫号码
	string               m_called_id;	                    //被叫号码
	string               m_transId;	                        //业务流水号
	boost::timer                m_callTime;	                    //发起呼叫的时间
	hungup_strategy*     m_hungup_strategy;                 //依据不同号段， 会有不同的挂断延迟策略
	bool                 m_hungup_by_echo_tone;             //是否响一声挂机, false 非响一声挂机情况仅限于测试用, 生产环境设置为 true, 保证响一声立即挂机
	boost::mutex                m_trunk_mutex;	                    //通道状态锁
	boost::shared_ptr<base_client>   m_client_socket;	            //每次呼叫时，需要配合其他组件保存的信息

	trunk()
	{
		m_step = TRK_IDLE;
		m_hungup_strategy = nullptr;
	}

	/**
	 * 每次呼叫完毕， 需要重置相关资源
	 *
	 */
	void realseTrunk()
	{
		m_step = TRK_IDLE;
		m_caller_id.clear();
		m_called_id.clear();
		m_transId.clear();
		m_callTime.restart();
		m_hungup_strategy = nullptr;
		m_hungup_by_echo_tone = true;
		m_client_socket.reset();
	}
};

#endif