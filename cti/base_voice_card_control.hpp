#ifndef BASE_VOICE_CARD_CONTROL_INCLUDE_
#define BASE_VOICE_CARD_CONTROL_INCLUDE_
#include "../system/include_sys.h"
#include "../net_logic/base_client.hpp"
#include "../tools/boost_log.hpp"

#include <memory>

#include <string>
class base_voice_card_control
{
public:
	virtual int cti_callout(boost::shared_ptr<base_client> base_client, std::string transId, std::string authCode, std::string pn, bool hungup_by_echo_tone = true){
		BOOST_LOG_SEV(cia_g_logger, RuntimeInfo) << "模拟发送呼叫请求";
		ciaMessage msg;
		msg.set_type(CIA_CALL_RESPONSE);
		msg.set_transid(transId);
		msg.set_status(CIA_CALL_SUCCESS);
		base_client->do_write(chat_message(msg));
		return 0;
	};
	virtual std::size_t get_idel_channel_number(){
		return 20;
	}
protected:
private:
};

#endif // !BASE_VOICE_CARD_CONTROL_INCLUDE_