#ifndef CIA_DEF_H_INCLUDE_
#define CIA_DEF_H_INCLUDE_

#include <string>

const std::string CIA_LOGIN_REQUEST("000101");    // 登陆请求
const std::string CIA_LOGIN_RESPONSE("000301");   // 登陆响应
const std::string CIA_LOGIN_SUCCESS("99");        // 登陆成功
const std::string CIA_LOGIN_FAIL("98");           // 登陆失败
const std::string CIA_HEART_REQUEST("000302");    // 心跳请求
const std::string CIA_HEART_RESPONSE("000102");   // 心跳响应
const std::string CIA_CALL_REQUEST("010103");     // 呼叫请求
const std::string CIA_CALL_RESPONSE("010303");    // 呼叫回应
const std::string CIA_CALL_SUCCESS("99");         // 呼叫成功
const std::string CIA_CALL_FAIL("98");            // 呼叫失败
const std::string CIA_CALL_TIMEOUT("01");         // 呼叫请求超时

#endif // !CIA_DEF_H_INCLUDE_