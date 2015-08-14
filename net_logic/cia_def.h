#ifndef CIA_DEF_H_INCLUDE_
#define CIA_DEF_H_INCLUDE_

#include <string>

const std::string CIA_LOGIN_REQUEST("000101");
const std::string CIA_LOGIN_RESPONSE("000301");
const std::string CIA_LOGIN_SUCCESS("99");
const std::string CIA_LOGIN_FAIL("98");
const std::string CIA_HEART_REQUEST("000302");
const std::string CIA_HEART_RESPONSE("000102");
const std::string CIA_CALL_REQUEST("010103");
const std::string CIA_CALL_RESPONSE("010303");
const std::string CIA_CALL_SUCCESS("99");
const std::string CIA_CALL_FAIL("98");
const std::string CIA_CALL_GIVE_UP("01");
const std::string CIA_CALL_BUZY("02");

#endif // !CIA_DEF_H_INCLUDE_