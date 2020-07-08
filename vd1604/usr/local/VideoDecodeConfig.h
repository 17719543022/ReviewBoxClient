#ifndef VideoDecodeConfig_H
#define VideoDecodeConfig_H

#ifdef VIDEODECODE_EXPORTS
#define VIDEODECODE_API __declspec(dllexport)
#else
#define VIDEODECODE_API
#endif

#ifdef WIN32
#define CALLBACK __stdcall
#define WIN32_LEAN_AND_MEAN
#else
#define CALLBACK
#endif

#ifndef CXX11_PLUS
#if __cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
#define CXX11_PLUS 1
#else
#define CXX11_PLUS 0
#endif
#endif

typedef struct DecodeParam
{
  char *filePath;
} DecodeParam;

enum EnumImageFormat
{
  EnumImageFormat_NULL = 0,
  EnumImageFormat_BGR24,
  EnumImageFormat_YV12,
  EnumImageFormat_YUYV,
  EnumImageFormat_I420,
  EnumImageFormat_ARGB,
  EnumImageFormat_NV12,
  EnumImageFormat_NV21  
};

enum VideoDecodeType
{
  VideoDecodeType_DECODE,  // only decode video file, without shown, without
                           // frame delay.
  VideoDecodeType_NOSHOW,  // decode video with frame delay, without shown
                           // (shown by user).
  VideoDecodeType_PLAY  // decode video with frame delay and shown. normal play.
};

/**
  Returns TRUE if a specified RETURN_STATUS code is an error code.
  This function returns TRUE if StatusCode has the high bit set.  Otherwise,
FALSE is returned.
  @param  StatusCode    The status code value to evaluate.
  @retval TRUE          The high bit of StatusCode is set.
  @retval FALSE         The high bit of StatusCode is clear.
**/
#define VDC_ERROR(StatusCode) StatusCode >= 2001 && StatusCode <= 2008

#define VDC_SUCCESS 0
#define VDC_FAILED 2001
#define VDC_LOGIN_FAILED 2002
#define VDC_UNSUPPORTED 2003
#define VDC_OUT_OF_RESOURCES 2004
#define VDC_PARAMETER_ERROR 2005
#define VDC_NOT_READY 2006
#define VDC_UNSUPPORTED_DECODER 2007
#define VDC_NOT_FOUND_DECODER 2008

#if defined(__linux__)
typedef unsigned int DECODE_HWND;
#define DECODE_HWND_NULL 0
#else
typedef void* DECODE_HWND;
#define DECODE_HWND_NULL nullptr
#endif

typedef struct MediaSample
{
  DECODE_HWND handle;  // windows handle
  int type;            //媒体类型EnumImageFormat
  int width;           //图像高度
  int height;          //图像宽度
  unsigned char *data[3];
  int stride[3];
  unsigned int time;  //时间戳

  void *param;  //额外参数
} MediaSample;

// Video decode call back function, called every frame.
typedef void(CALLBACK *onImageData)(long frameIndex, char *data, int len,
                                    int format, void *userData);

// Video file ended call back function, only called when video decode ended,
// once .
typedef void(CALLBACK *FileEndCallBack)(void *userData);

#endif
