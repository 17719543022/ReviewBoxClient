#ifndef HTTPSERVEREXP_H
#define HTTPSERVEREXP_H

#include "HTTPServerDef.h"

#ifdef WIN32

#ifdef HTTPSERVER_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

#else
#define DLLAPI
#endif


#ifdef __cplusplus
extern "C"{
#endif

	/* 功能：开启HTTP服务
	** 参数：nPort，[IN]，服务端口
	** pListener，[IN], 回调监听对象
	** 返回值：
	**       0，成功； 其他，错误码
	** 说明：无
	*/
	DLLAPI int StartHTTPServer(int nPort, RequstListener* pListener);

	/* 功能：停止HTTP服务
	** 参数：无
	** 返回值：
	**		0，成功； 其他，错误码
	** 说明：无
	*/
	DLLAPI int StopHTTPServer();

#ifdef __cplusplus
}
#endif

#endif