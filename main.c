#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #define DEBUG

#if defined(DEBUG)
#define debug printf
#else
#define debug
#endif

char fmt[16];           // foramt
char src_file_name[16]; // src file name
char dst_file_name[16]; // dst file name
unsigned int iw = 0;    // input_width
unsigned int ih = 0;    // input_heght
unsigned int ox = 0;    // output_x
unsigned int oy = 0;    // output_y
unsigned int ow = 0;    // output_width
unsigned int oh = 0;    // output_height

unsigned int ip = 0;    // input_pitch
unsigned int op = 0;    // output_pitch

unsigned char *src_buf = NULL;
unsigned char *dst_buf = NULL;
unsigned char *src_buf_bak = NULL;
unsigned char *dst_buf_bak = NULL;
unsigned int src_buf_len = 0;
unsigned int dst_buf_len = 0;
FILE *src_file = NULL;
FILE *dst_file = NULL;

int parsing_main_arguments(int argc, char const *argv[]);
int yuv420sp_uv_crop(void);

int main(int argc, char const *argv[])
{
    parsing_main_arguments(argc, argv);

    if (0 == strcmp(fmt, "YUV420SP_UV"))
    {
        yuv420sp_uv_crop();
    }

    return 0;
}

/**
 * @Description 解析命令行参数到全局变量，并验证参数的有效性
 */
int parsing_main_arguments(int argc, char const *argv[])
{
    /* 打印函数使用方法 */
    if (argc != 10)
    {
        printf("usage: ./app fmt file iw ih ox oy ow oh\n");
        printf("eg   : ./app YUV420SP_UV xxx.yuv420sp_uv out.yuv420sp_uv 1920 1080 0 0 1280 960\n");
        printf("\n");
        return -1;
    }

    strcpy(fmt, argv[1]);
    strcpy(src_file_name, argv[2]);
    strcpy(dst_file_name, argv[3]);
    iw = (unsigned int)strtol(argv[4], NULL, 0);
    ih = (unsigned int)strtol(argv[5], NULL, 0);
    ox = (unsigned int)strtol(argv[6], NULL, 0);
    oy = (unsigned int)strtol(argv[7], NULL, 0);
    ow = (unsigned int)strtol(argv[8], NULL, 0);
    oh = (unsigned int)strtol(argv[9], NULL, 0);

    if (ox + ow > iw)
    {
        printf("err: invalid width");
        printf("iw = %d\n", iw);
        printf("ox = %d\n", ox);
        printf("ow = %d\n", ow);
        return -1;
    }

    if (oy + oh > ih)
    {
        printf("err: invalid height");
        printf("ih = %d\n", ih);
        printf("oy = %d\n", oy);
        printf("oh = %d\n", oh);
        return -1;
    }

    /* 打印解析到的参数 */
    debug("fmt = %s\n", fmt);
    debug("src_file_name = %s\n", src_file_name);
    debug("iw = %d\n", iw);
    debug("ih = %d\n", ih);
    debug("ox = %d\n", ox);
    debug("oy = %d\n", oy);
    debug("ow = %d\n", ow);
    debug("oh = %d\n", oh);

    return 0;
}

int yuv420sp_uv_crop(void)
{
    int row = 0;        // 行计数
    int col = 0;        // 列计数
    ip = iw;
    op = ow;
    unsigned char* pSrc = NULL;
    unsigned char* pDst = NULL;

    /* 计算存储图像 buf 的大小 */
    src_buf_len = iw * ih * 3 / 2;
    dst_buf_len = ow * oh * 3 / 2;
    debug("src_buf_len = %u\n", src_buf_len);
    debug("dst_buf_len = %u\n", dst_buf_len);

    /* 申请图像 buffer，并清空 buffer 数据 */
    src_buf = (unsigned char *)malloc(src_buf_len);
    if (src_buf == NULL)
    {
        printf("err: src_buf malloc failed\n");
        return -1;
    }

    dst_buf = (unsigned char *)malloc(dst_buf_len);
    if (dst_buf == NULL)
    {
        printf("err: dst_buf malloc failed\n");
        return -1;
    }

    memset(src_buf, 0, src_buf_len);
    memset(dst_buf, 0, dst_buf_len);

    /* 对申请内存的指针进行备份，因为 free 的时候需要用到 */
    src_buf_bak = src_buf;
    dst_buf_bak = dst_buf;

    /* 打开文件读取原始图像数据 */
    src_file = fopen(src_file_name, "r");
    fread(src_buf, 1, src_buf_len, src_file);

    pSrc = src_buf + oy * ip + ox;
    pDst = dst_buf;

    /* 拷贝 Y 分量 */
    for (row = 0; row < oh; row++)
    {
        memcpy(pDst, pSrc, op);
        pSrc = pSrc + ip;
        pDst = pDst + op;
    }

    pSrc = src_buf + oy / 2 * ip + ox + iw * ih;

    /* 拷贝 UV 分量 */
    for (row = 0; row < (oh / 2); row++)
    {
        memcpy(pDst, pSrc, op);
        pSrc = pSrc + ip;
        pDst = pDst + op;
    }

    dst_file = fopen(dst_file_name, "wb");
    fwrite(dst_buf, 1, dst_buf_len, dst_file);

    fclose(src_file);
    fclose(dst_file);

    free(src_buf_bak);
    free(dst_buf_bak);

    return 0;
}
