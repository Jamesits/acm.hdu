/* acm.hdu.edu.cn problem archive 1800
 * by James Swineson, 2014-12-26
 */

// 每次数组扩容时的增量
#define size_delta 16

#include <stdio.h>
#include <stdlib.h>

unsigned int *key;      // 存储 hash 后的数值
unsigned int *value;    // 存储每一个 hash 值出现的次数
unsigned int size;      // 当前 hash table 大小
unsigned int count;     // 实际字段数

/*
 *  计算字符串 CRC32 的函数。参考 http://stackoverflow.com/a/21001712/2646069
 */
unsigned int crc32(unsigned char *message)
{
    int i, j;
    unsigned int byte, crc, mask;

    i = 0;
    crc = 0xFFFFFFFF;
    while ( message[i] != 0 )
    {
        byte = message[i];
        crc = crc ^ byte;
        for ( j = 7; j >= 0; j-- )
        {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }

    return ~crc;
}

/*
 *  数组初始化
 */
void init_ptrs()
{
    if ( key != NULL ) free(key);
    if ( value != NULL ) free(value);
    key = NULL;
    value = NULL;
    size = 0;
    count = 0;
}

/*
 *  把一个新的值添加到 hash table
 */
void add_item(const unsigned int number)
{
    unsigned int i;

    for ( i = 0; i < count; i++ )
    {
        if ( key[i] == number )
        {
            value[i]++;

            return;
        }
    }
    if ( count == size )
    {
        size += size_delta;
        key = realloc( key, size * sizeof(unsigned int) );
        value = realloc( value, size * sizeof(unsigned int) );
    }
    key[count] = number;
    value[count] = 1;
    count++;
}

/*
 *  调试用：输出数组当前状态
 */
void print_all()
{
    unsigned int i;

    for ( i = 0; i < count; i++ )
    {
        printf("Offset %u, key %u count %u\n", i, key[i], value[i]);
    }
}

int main(void)
{
    unsigned int num;
    unsigned char a[31], *start;

    while ( scanf("%u", &num) != EOF )
    {
        // 初始化
        init_ptrs();
        // 输入，忽略删去前导 0
        while ( num-- > 0 )
        {
            scanf("%30s", a);
            for ( start = a; *start == '0'; start++ );
            add_item( crc32( start ) );
        }

        // 统计最大重复次数
        unsigned int max = 0;
        unsigned int i;

        for ( i = 0; i < count; i++ )
        {
            if ( value[i] > max ) max = value[i];
        }
        printf("%u\n", max);
    }

    return 0;
}
