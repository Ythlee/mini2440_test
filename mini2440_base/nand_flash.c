#include "mini2440.h"
#include "my_printf.h"

void nand_init(void)
{
#define  TACLS   0
#define  TWRPH0  1
#define  TWRPH1  0
    /*����NAND FLASH��ʱ��*/
    NFCONF = (TACLS << 12) | (TWRPH0 << 8) | (TWRPH1 << 4);
    /*ʹ��NAND FLASH������,��ʼ��ECC����ֹƬѡ*/
    NFCONT = (1 << 4) | (1 << 1) | (1 << 0);
}

void nand_select(void)
{
    /*ʹ��Ƭѡ*/
    NFCONT &= ~(1 << 1);
}

void nand_deselect(void)
{
    /*��ֹƬѡ*/
    NFCONT |= (1 << 1);
}

void nand_cmd(unsigned char cmd)
{
    volatile int i;
    NFCCMD = cmd;
    for(i = 0; i < 10; i++);
}

void nand_addr_byte(unsigned char addr)
{
    volatile int i;
    NFADDR = addr;
    for(i = 0; i < 10; i++);
}

unsigned char nand_data(void)
{
    return	NFDATA;
}

void nand_chip_id(void)
{
    unsigned char buf[5] = {0};

    nand_select();
    nand_cmd(0x90);
    nand_addr_byte(0x00);

    buf[0] = nand_data();
    buf[1] = nand_data();
    buf[2] = nand_data();
    buf[3] = nand_data();
    buf[4] = nand_data();
    nand_deselect();

    printf("maker   id  = 0x%x\n\r", buf[0]);
    printf("device  id  = 0x%x\n\r", buf[1]);
    printf("3rd byte    = 0x%x\n\r", buf[2]);
    printf("4th byte    = 0x%x\n\r", buf[3]);
    printf("5th byte    = 0x%x\n\r", buf[4]);
    printf("page  size  = %d kb\n\r", 1  <<  (buf[3] & 0x03));
    printf("block size  = %d kb\n\r", 64 << ((buf[3] >> 4) & 0x03));

}


//void nand_flash_test(void)
//{
//	char c;
//
//	while (1)
//	{
//		/* ��ӡ�˵�, ������ѡ��������� */
//		printf("[s] Scan nand flash\n\r");
//		printf("[e] Erase nand flash\n\r");
//		printf("[w] Write nand flash\n\r");
//		printf("[r] Read nand flash\n\r");
//		printf("[q] quit\n\r");
//		printf("Enter selection: ");
//
//		c = getchar();
//		printf("%c\n\r", c);
//
//		/* ��������:
//		 * 1. ʶ��nand flash
//		 * 2. ����nand flashĳ������
//		 * 3. ��дĳ����ַ
//		 * 4. ��ĳ����ַ
//		 */
//		switch (c)
//		{
//			case 'q':
//			case 'Q':
//				return;
//				break;
//
//			case 's':
//			case 'S':
//				nand_chip_id();
//				break;
//
//			case 'e':
//			case 'E':
//				break;
//
//			case 'w':
//			case 'W':
//				break;
//
//			case 'r':
//			case 'R':
//				break;
//			default:
//				break;
//		}
//	}
//}
//
void nand_flash_test(void)
{
    nand_chip_id();
}