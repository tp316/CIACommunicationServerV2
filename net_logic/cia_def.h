#ifndef CIA_DEF_H_INCLUDE_
#define CIA_DEF_H_INCLUDE_

#include <string>

using namespace std;

const string CIA_LOGIN_REQUEST("000101");
const string CIA_LOGIN_RESPONSE("000301");
const string CIA_LOGIN_SUCCESS("99");
const string CIA_LOGIN_FAIL("98");
const string CIA_HEART_REQUEST("000302");
const string CIA_HEART_RESPONSE("010103");
const string CIA_CALL_REQUEST("010103");
const string CIA_CALL_RESPONSE("010303");
const string CIA_CALL_SUCCESS("99");
const string CIA_CALL_FAIL("98");
const string CIA_CALL_GIVE_UP("01");
const string CIA_CALL_BUZY("02");

#endif // !CIA_DEF_H_INCLUDE_