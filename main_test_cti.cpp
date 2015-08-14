//#include "tools/boost_log.hpp"
//#include "net_logic/base_client.hpp"
//#include "cti/voice_card_control.hpp"
//#include "system/include_sys.h"
//
//
//#include <stdlib.h>
//#include <exception>
//#include <iostream>
//void testNetLogic();
//void testCTI();
//void test_all();
//
//int main(int argc, char* argv[]) {
//	try{
//		init_log();
//	}
//	catch (std::exception& e){
//		std::cout << e.what() << std::endl;
//		return -1;
//	}
//	//testNetLogic();
//	testCTI();
//	//test_all();
//	::system("pause");
//}
//
//void testCTI()
//{
//	try
//	{
//		// 78  服务器 86051200 86051882 86051822
//		// 145 服务器 86057405 86057408 86057410	86057415 86057423 86057428
//		//           86057431 86057435 86057437 86057459 86057501 86057851 86057861
//		std::string callerNum = "86051200";
//		// 李禹霖 018072710179 018515663997
//		// 马超   018611967787
//		std::string calledNum = "018515663997";
//		voice_card_control vcc(30, 15, true);
//		size_t trans_id = 100;
//		boost::shared_ptr<base_client> client_ptr = boost::make_shared<base_client>();
//		BOOST_LOG_SEV(cia_g_logger, Critical) << ">>>>>--------------------------------------------------------------------第一波检测, 测试10次呼叫, 响一声挂断--------------------------------------------------------------------<<<<<";
//		for (size_t i = 0; i < 10; i++)
//		{
//			vcc.cti_callout(client_ptr, std::to_string(trans_id++), callerNum, calledNum);
//			boost::this_thread::sleep_for(boost::chrono::seconds(10));
//		}
//		//callerNum = "86051882";
//		//BOOST_LOG_SEV(g_logger, Critical) << ">>>>>--------------------------------------------------------------------第二波检测, 测试10次呼叫, 响一声不挂断, 等待超时15秒后, 由超时检测线程挂断--------------------------------------------------------------------<<<<<";
//		//for (size_t i = 0; i < 10; i++)
//		//{
//		//	vcc.cti_callout(p, to_string(trans_id++), callerNum, calledNum, false);
//		//	boost::this_thread::sleep_for(boost::chrono::seconds(20));
//		//}
//	}
//	catch (std::exception &e)
//	{
//		std::cout << "程序异常:" << e.what() << std::endl;
//	}
//}
