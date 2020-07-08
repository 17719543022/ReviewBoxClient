#ifndef HTTPSERVERDEF_H
#define HTTPSERVERDEF_H

#include <map>
#include <string>

#define HTTPSER_OK	0     //OK
#define HTTPSER_ERR_PARAM  5001//参数错误

typedef struct _DataInfo
{
	char* szBuf;
	int   nLen;

	_DataInfo():szBuf(nullptr), nLen(0){}
}DataInfo;

//请求事件监听抽象类
class RequstListener
{
public:
	RequstListener(){}
	virtual ~RequstListener(){}

	/* 功能：用于回调HTTP multipart/form-data请求；
	** 参数：uri, 请求uri
	**      mapDataInfo，从请求Json解析出的键值对；
	**	    strResponse，该请求的Response;
	** 返回值：无
	** 说明：无
	*/
	virtual void MultipartRequstListen(const std::string& uri, const std::map<std::string, DataInfo>& mapDataInfo, std::string& strResponse) = 0;

	/* 功能：用于回调HTTP其他Content-Type的请求
	** 参数：uri, 请求uri
	**      strRequstBody，HTTP请求内容
	**		strResponse，该请求的Response;
	** 返回值：无
	** 说明:无
	*/
	virtual void CommonRequstListen(const std::string& uri, const std::string& strRequstBody, std::string& strResponse) = 0;
};

#endif