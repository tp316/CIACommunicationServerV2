#ifndef BASE_VOICE_CARD_CONTROL_INCLUDE_
#define BASE_VOICE_CARD_CONTROL_INCLUDE_

#include "../net_logic/base_client.hpp"
#include "../tools/boost_log.hpp"

#include <memory>

#include <string>
class base_voice_card_control
{
public:
	virtual int cti_callout(boost::shared_ptr<base_client> CTRUNC_ATTACHMENT, std::string transId, std::string authCode, std::string pn, bool hungup_by_echo_tone = true){
		BOOST_LOG_SEV(cia_g_logger, RuntimeInfo) << "模拟发送呼叫请求";
		return 0;
	};
protected:
private:
};

#endif // !BASE_VOICE_CARD_CONTROL_INCLUDE_