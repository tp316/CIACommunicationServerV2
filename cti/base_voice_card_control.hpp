#ifndef BASE_VOICE_CARD_CONTROL_INCLUDE_
#define BASE_VOICE_CARD_CONTROL_INCLUDE_

#include "../net_logic/base_client.hpp"

#include <memory>

#include <string>
class base_voice_card_control
{
public:
	virtual int cti_callout(boost::shared_ptr<base_client> CTRUNC_ATTACHMENT, std::string transId, std::string authCode, std::string pn, bool hungup_by_echo_tone = true){
		return 0;
	};
protected:
private:
};

#endif // !BASE_VOICE_CARD_CONTROL_INCLUDE_