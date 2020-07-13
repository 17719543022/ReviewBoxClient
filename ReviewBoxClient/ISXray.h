#ifndef ISXray_H
#define ISXray_H

#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///创建X光机检测通道，以后相关操作作为参数传入
	///@param
	///@return
	///-1 失败，0...N 成功
int ISCreateXrayChannel();

///@brief
///创建X光机检测通道，以后相关操作作为参数传入
///@param
///@return
///-1 失败，0...N 成功
int ISDestroyXrayChannel(int channel);

	///@brief
	///分析X光图像
	///@param
	/*input*/
	///channel-创建的通道号
	///imgData-X光机图像的data数据
	///imgWidth-图像的宽度
	///imgHeight-图像的高度
	///imgChannel-图像的通道数
	/*output*/
	///result-数组前4位依次为框的左、上、右、下坐标;第5位位框的运动方向,1代表 传送带正常运行方向，0 代表 传动带暂停， -1代表传动带反转;
	///第6位为box_id，if(box_id<0),说明当前图像不是检测到的最优图像，否则为最优的完整框图像
    ///boxNum框的数量
	///box_str-框上标记的字符串（预留）
	///@return
	///0 成功，其他 失败
int ISAnaXrayBoxRgb(int channel, char *imgData, int imgWidth, int imgHeight, int imgChannel, int *boxNum, int result[][6], char *boxStr[]);

	///@brief
	///返回当前SDK能够创建的x光机检测器最大通道数
int ISGetMaxXrayChannel();

	///@brief
	///返回当前SDK  X光机检测器信息
const char* ISGetXrayVersionInfo();


#if defined (__cplusplus)
}
#endif


#endif


