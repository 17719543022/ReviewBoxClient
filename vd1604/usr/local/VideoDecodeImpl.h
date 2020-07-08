#ifndef VideoDecodeImpl_H
#define VideoDecodeImpl_H

#include "VideoDecodeConfig.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define VERSION "2.0.0"

/**
  Start video decode, including following step: Search the correct decoding
  library,open video file, read video information and other video operation.

  @param[in]  sourceType  input source type.
  @param[in]  param       video full file name, it must be char*.
  @param[in]  wndHandle   window handle for display video.
  @param[in]  decodeType  reference to enum VideoDecodeType.
  @param[out] videoId     video Id, input parameter for other funciton.

  @retval VDC_SUCCESS  decode success.
  @retval other do not find decoder.
**/
VIDEODECODE_API int videoDecodeStart(const char* sourceType, const char* param,
                                     DECODE_HWND wndHandle, int decodeType,
                                     int* videoId);

/**
  OverWritting function for video start with call back function added before
  video start to decode.

  @param[in]  sourceType  input source type.
  @param[in]  param       video full file name, it must be char*.
  @param[in]  wndHandle   window handle for display video.
  @param[in]  decodeType  reference to enum VideoDecodeType.
  @param[in]  cb          decode call back function, will be called every frame
                          decoded.
  @param[in]  userData    transfer user data to call back function.
  @param[out] videoId     video Id, input parameter for other funciton.

  @retval VDC_SUCCESS  decode success.
  @retval other do not find decoder.
**/
VIDEODECODE_API int videoDecodeStart2(const char* sourceType, const char* param,
                                      DECODE_HWND, int decodeType,
                                      onImageData cb, void* userData,
                                      int* videoId);

/**
  Stop video decode

  @param[in] id video id from videoDecodeStart or videoDecodeStart2

  @retval VDC_SUCCESS stop decode successful.
  @retval other stop decode failed.
**/
VIDEODECODE_API int videoDecodeStop(int id);

/**
  Play video

  @param[in] id video id from videoDecodeStart or videoDecodeStart2

  @retval VDC_SUCCESS play video successful.
  @retval other play video failed.
**/
VIDEODECODE_API int videoDecodePlay(int id);

/**
  Pause video

  @param[in] id video id from videoDecodeStart or videoDecodeStart2

  @retval VDC_SUCCESS pause video successful.
  @retval other pause video failed.
**/
VIDEODECODE_API int videoDecodePause(int id);

/**
  Set Decode speed

  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[in] speed the speed to decode

  @retval VDC_SUCCESS set speed successful.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other set speed failed.
**/
VIDEODECODE_API int videoDecodeSetSpeed(int id, double speed);

/**
  Seed to frame

  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[in] frameIndex the frame to seek

  @retval VDC_SUCCESS seek successful.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other seek failed.
**/
VIDEODECODE_API int videoDecodeSeekToFrame(int id, long frameIndex);

/**
  Push data to decode

  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[in] data data pointer to push
  @param[in] len data length.

  @retval VDC_SUCCESS push data successful.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other push data failed.
**/
VIDEODECODE_API int videoDecodePushData(int id, char* data, int len);

/**
  get current frame jpeg

  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[in,out] outData jpeg output data pointer.
  @param[in] bufLen output outData input bufer length.
  @param[out] outDataLen jpeg output data output length pointer.

  @retval VDC_SUCCESS push data successful.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other get jpeg failed.
**/
VIDEODECODE_API int videoDecodeGetJpeg(int id, char* outData, int bufLen,
                                       int* outDataLen);

/**
  Add image data callback

  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[in] cb callback data.
  @param[in] userData user data pointer.

  @retval VDC_SUCCESS push data successful.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other add callback failed.
**/
VIDEODECODE_API int videoDecodeAddImageDataCallback(int id, onImageData cb,
                                                     void* userData);

/**
  Remove image data callback

  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[in] cb callback data.

  @retval VDC_SUCCESS push data successful.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other remove callback failed.
**/
VIDEODECODE_API int videoDecodeRemoveImageDataCallback(int id, onImageData cb);

/**
  Add file ends call back function, fileEndCB only be called when decoding is
  finished.
  
  @param[in] id  video id from videoDecodeStart or videoDecodeStart2
  @param[in] fileEndCB file end process function pointer
  @param[in] userData  user data pointer.
  
  @retval VDC_SUCCESS add file end callback success.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other add callback failed.
 **/
VIDEODECODE_API int videoDecodeAddFileEndCallBack(int id,
                                                   FileEndCallBack fileEndCB,
                                                   void* userData);

/**
  Get video duration(ms), frame rate(frames per second), width and height.
  
  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[out] duration duration pointer not null.
  @param[out] frameRate frameRate pointer not null.
  @param[out] width frameRate pointer not null.
  @param[out] height frameRate pointer not null.
  
  @retval VDC_SUCCESS get video info success.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other get video info failed.
**/
VIDEODECODE_API int videoDecodeGetVideoInfo(int id, long* duration,
                                            double* frameRate, int* width,
                                            int* height);

/**
  Get current position.


  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[out] frameIndex frameIndex pointer not null.


  @retval VDC_SUCCESS get video info success.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other get current position failed.
**/
VIDEODECODE_API int videoDecodeGetCurrentPosition(int id, long* frameIndex);

/**
  Get video current rate.


  @param[in] id video id from videoDecodeStart or videoDecodeStart2
  @param[out] rate rate pointer not null.

  @retval VDC_SUCCESS get current rate success.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other get current rate failed.
**/
VIDEODECODE_API int videoDecodeGetCurrentRate(int id, double* rate);

/**
  play next one frame.

  @param[in] id video id from videoDecodeStart or videoDecodeStart2

  @retval VDC_SUCCESS  play next one frame success.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other  play next one frame failed.
**/
VIDEODECODE_API int videoDecodePlayNextOneFrame(int id);

/**
  play back one frame.

  @param[in] id video id from videoDecodeStart or videoDecodeStart2

  @retval VDC_SUCCESS  play back one frame success.
  @retval VDC_UNSUPPORTED decoder not support this action.
  @retval other  play back one frame failed.
**/
VIDEODECODE_API int videoDecodePlayBackOneFrame(int id);

/**
  get decode version.

  @retval version string.
**/
VIDEODECODE_API const char* videoDecodeGetVersion();

#if defined(__cplusplus)
}
#endif

#endif
