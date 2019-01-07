### 程序说明

实现 YUV 格式图像的裁剪。

### 目前状态

命令格式：`./app <format> <ifn> <ofn> <iw> <ih> <ox> <oy> <ow> <oh>`  

    format: 输入图像的格式
    ifn： input file name 原始图像文件名
    ofn： output file name 输出图像文件名
    iw, ih: input width， input height 原始图像宽高
    ox, oy: output x, output y 从原始图像 (x, y) 位置开始裁剪
    ow, oh: output w, output h 裁剪的宽高，也是输出图像的宽高

计划支持以下 YUV 图像格式：

    typedef enum
    {
        YUV422I_UYVY = 0x0000,
        /**< YUV 422 Interleaved format - UYVY. */
        YUV422I_YUYV = 0x0001,
        /**< YUV 422 Interleaved format - YUYV. */
        YUV422I_YVYU = 0x0002,
        /**< YUV 422 Interleaved format - YVYU. */
        YUV422I_VYUY = 0x0003,
        /**< YUV 422 Interleaved format - VYUY. */
        YUV422SP_UV = 0x0004,
        /**< YUV 422 Semi-Planar - Y separate, UV interleaved. */
        YUV422SP_VU = 0x0005,
        /**< YUV 422 Semi-Planar - Y separate, VU interleaved. */
        YUV422P = 0x0006,
        /**< YUV 422 Planar - Y, U and V separate. */

        YUV420SP_UV = 0x0007,
        /**< YUV 420 Semi-Planar - Y separate, UV interleaved. */
        YUV420SP_VU = 0x0008,
        /**< YUV 420 Semi-Planar - Y separate, VU interleaved. */
        YUV420P = 0x0009,
        /**< YUV 420 Planar - Y, U and V separate. */

        YUV444P = 0x000A,
        /**< YUV 444 Planar - Y, U and V separate. */
        YUV444I = 0x000B,
        /**< YUV 444 interleaved - YUVYUV... */
        INVALID,
        /**< Invalid data format. Could be used to initialize variables. */
    } DataFormat;

目前支持的格式有：

- YUV420SP_UV

### 编译执行

    user@ubuntu:~/work/c-study/YUV-image-cropping$ make
    gcc -o app main.c
    user@ubuntu:~/work/c-study/YUV-image-cropping$ ./app 
    usage: ./app fmt file iw ih ox oy ow oh
    eg   : ./app YUV420SP_UV xxx.yuv420sp_uv out.yuv420sp_uv 1920 1080 0 0 1280 960
    
    user@ubuntu:~/work/c-study/YUV-image-cropping$ ./app YUV420SP_UV xxx.yuv420sp_uv out.yuv420sp_uv 1920 1080 960 540 480 270
