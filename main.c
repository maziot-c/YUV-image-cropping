#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG

#if defined(DEBUG)
#define debug printf
#else
#define debug
#endif

// typedef enum
// {
//     YUV422I_UYVY = 0x0000,
//     /**< YUV 422 Interleaved format - UYVY. */
//     YUV422I_YUYV = 0x0001,
//     /**< YUV 422 Interleaved format - YUYV. */
//     YUV422I_YVYU = 0x0002,
//     /**< YUV 422 Interleaved format - YVYU. */
//     YUV422I_VYUY = 0x0003,
//     /**< YUV 422 Interleaved format - VYUY. */
//     YUV422SP_UV = 0x0004,
//     /**< YUV 422 Semi-Planar - Y separate, UV interleaved. */
//     YUV422SP_VU = 0x0005,
//     /**< YUV 422 Semi-Planar - Y separate, VU interleaved. */
//     YUV422P = 0x0006,
//     /**< YUV 422 Planar - Y, U and V separate. */

//     YUV420SP_UV = 0x0007,
//     /**< YUV 420 Semi-Planar - Y separate, UV interleaved. */
//     YUV420SP_VU = 0x0008,
//     /**< YUV 420 Semi-Planar - Y separate, VU interleaved. */
//     YUV420P = 0x0009,
//     /**< YUV 420 Planar - Y, U and V separate. */

//     YUV444P = 0x000A,
//     /**< YUV 444 Planar - Y, U and V separate. */
//     YUV444I = 0x000B,
//     /**< YUV 444 interleaved - YUVYUV... */
//     INVALID,
//     /**< Invalid data format. Could be used to initialize variables. */
// } DataFormat;

// ./app fmt file iw ih ox oy ow oh

char fmt[16];
char file[16];
unsigned iw = 0;        // input_width
unsigned ih = 0;        // input_heght
unsigned ox = 0;        // output_x
unsigned oy = 0;        // output_y
unsigned ow = 0;        // output_width
unsigned oh = 0;        // output_height

int parsing_main_arguments(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
    parsing_main_arguments(argc, argv);

    debug("fmt = %s\n", fmt);
    debug("file = %s\n", file);
    debug("iw = %d\n", iw);
    debug("ih = %d\n", ih);
    debug("ox = %d\n", ox);
    debug("oy = %d\n", oy);
    debug("ow = %d\n", ow);
    debug("oh = %d\n", oh);

    return 0;
}

/**
 * @Description 解析命令行参数到全局变量，并验证参数的有效性
 */
int parsing_main_arguments(int argc, char const *argv[])
{
    /* 打印函数使用方法 */
    if(argc !=  9)
    {
        printf("usage: ./app fmt file iw ih ox oy ow oh\n");
        printf("eg   : ./app YUV420SP_VU pic.yuv420sp_vu 1920 1080 0 0 1280 960\n");
        printf("\n");
        return -1;
    }

    strcpy(fmt, argv[1]);
    strcpy(file, argv[2]);
    iw = (unsigned int)strtol(argv[3], NULL, 0);
    ih = (unsigned int)strtol(argv[4], NULL, 0);
    ox = (unsigned int)strtol(argv[5], NULL, 0);
    oy = (unsigned int)strtol(argv[6], NULL, 0);
    ow = (unsigned int)strtol(argv[7], NULL, 0);
    oh = (unsigned int)strtol(argv[8], NULL, 0);

    if(ox + ow > iw)
    {
        printf("err: invalid width");
        printf("iw = %d\n", iw);
        printf("ox = %d\n", ox);
        printf("ow = %d\n", ow);
        return -1;
    }

    if(oy + oh > ih)
    {
        printf("err: invalid height");
        printf("ih = %d\n", ih);
        printf("oy = %d\n", oy);
        printf("oh = %d\n", oh);
        return -1;
    }

    return 0;
}