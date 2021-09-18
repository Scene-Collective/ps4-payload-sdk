#pragma once

#ifndef FW_DEFINES_H
#define FW_DEFINES_H

// clang-format off

// Used in every payload that uses jailbreak();
#define K300_XFAST_SYSCALL         0x0
#define K310_XFAST_SYSCALL         0x0
#define K311_XFAST_SYSCALL         0x0
#define K315_XFAST_SYSCALL         0x0
#define K350_XFAST_SYSCALL         0x003A1AD0
#define K355_XFAST_SYSCALL         0x003A1F10
#define K370_XFAST_SYSCALL         0x003A2000
#define K400_XFAST_SYSCALL         0x0030EA00
#define K401_XFAST_SYSCALL         0x0030EA00
#define K405_XFAST_SYSCALL         0x0030EB30
#define K406_XFAST_SYSCALL         0x0030EB40
#define K407_XFAST_SYSCALL         0x0030EB40
#define K450_XFAST_SYSCALL         0x003095D0
#define K455_XFAST_SYSCALL         0x003095D0
#define K470_XFAST_SYSCALL         0x0030B840
#define K471_XFAST_SYSCALL         0x0030B7D0
#define K472_XFAST_SYSCALL         0x0030B7D0
#define K473_XFAST_SYSCALL         0x0030B7D0
#define K474_XFAST_SYSCALL         0x0030B7D0
#define K500_XFAST_SYSCALL         0x000001C0
#define K501_XFAST_SYSCALL         0x000001C0
#define K503_XFAST_SYSCALL         0x000001C0
#define K505_XFAST_SYSCALL         0x000001C0
#define K507_XFAST_SYSCALL         0x000001C0
#define K550_XFAST_SYSCALL         0x000001C0
#define K553_XFAST_SYSCALL         0x000001C0
#define K555_XFAST_SYSCALL         0x000001C0
#define K556_XFAST_SYSCALL         0x000001C0
#define K600_XFAST_SYSCALL         0x000001C0
#define K602_XFAST_SYSCALL         0x000001C0
#define K620_XFAST_SYSCALL         0x000001C0
#define K650_XFAST_SYSCALL         0x000001C0
#define K651_XFAST_SYSCALL         0x000001C0
#define K670_XFAST_SYSCALL         0x000001C0
#define K671_XFAST_SYSCALL         0x000001C0
#define K672_XFAST_SYSCALL         0x000001C0
#define K700_XFAST_SYSCALL         0x000001C0
#define K701_XFAST_SYSCALL         0x000001C0
#define K702_XFAST_SYSCALL         0x000001C0
#define K750_XFAST_SYSCALL         0x000001C0
#define K751_XFAST_SYSCALL         0x000001C0
#define K755_XFAST_SYSCALL         0x000001C0
#define K800_XFAST_SYSCALL         0x000001C0
#define K801_XFAST_SYSCALL         0x000001C0
#define K803_XFAST_SYSCALL         0x000001C0
#define K850_XFAST_SYSCALL         0x000001C0
#define K852_XFAST_SYSCALL         0x000001C0
#define K900_XFAST_SYSCALL         0x000001C0

// Used in every payload that uses jailbreak();
#define K300_PRISON_0              0x0
#define K310_PRISON_0              0x0
#define K311_PRISON_0              0x0
#define K315_PRISON_0              0x0
#define K350_PRISON_0              0x00EF5A00
#define K355_PRISON_0              0x00EF5A00
#define K370_PRISON_0              0x00EFEF10
#define K400_PRISON_0              0x00F26010
#define K401_PRISON_0              0x00F26010
#define K405_PRISON_0              0x00F26010
#define K406_PRISON_0              0x00F26010
#define K407_PRISON_0              0x00F2A010
#define K450_PRISON_0              0x010399B0
#define K455_PRISON_0              0x010399B0
#define K470_PRISON_0              0x01042AB0
#define K471_PRISON_0              0x01042AB0
#define K472_PRISON_0              0x01042AB0
#define K473_PRISON_0              0x01042AB0
#define K474_PRISON_0              0x01042AB0
#define K500_PRISON_0              0x010986A0
#define K501_PRISON_0              0x010986A0
#define K503_PRISON_0              0x010986A0
#define K505_PRISON_0              0x010986A0
#define K507_PRISON_0              0x010986A0
#define K550_PRISON_0              0x01134180
#define K553_PRISON_0              0x01134180
#define K555_PRISON_0              0x01139180
#define K556_PRISON_0              0x01139180
#define K600_PRISON_0              0x01139458
#define K602_PRISON_0              0x01139458
#define K620_PRISON_0              0x0113D458
#define K650_PRISON_0              0x0113D4F8
#define K651_PRISON_0              0x0113D4F8
#define K670_PRISON_0              0x0113E518
#define K671_PRISON_0              0x0113E518
#define K672_PRISON_0              0x0113E518
#define K700_PRISON_0              0x0113E398
#define K701_PRISON_0              0x0113E398
#define K702_PRISON_0              0x0113E398
#define K750_PRISON_0              0x0113B728
#define K751_PRISON_0              0x0113B728
#define K755_PRISON_0              0x0113B728
#define K800_PRISON_0              0x0111A7D0
#define K801_PRISON_0              0x0111A7D0
#define K803_PRISON_0              0x0111A7D0
#define K850_PRISON_0              0x0111A8F0
#define K852_PRISON_0              0x0111A8F0
#define K900_PRISON_0              0x0111F870

// Used in every payload that uses jailbreak();
#define K300_ROOTVNODE             0x0
#define K310_ROOTVNODE             0x0
#define K311_ROOTVNODE             0x0
#define K315_ROOTVNODE             0x0
#define K350_ROOTVNODE             0x01963000
#define K355_ROOTVNODE             0x01963040
#define K370_ROOTVNODE             0x0196F040
#define K400_ROOTVNODE             0x0206D250
#define K401_ROOTVNODE             0x0206D250
#define K405_ROOTVNODE             0x0206D250
#define K406_ROOTVNODE             0x0206D250
#define K407_ROOTVNODE             0x02071250
#define K450_ROOTVNODE             0x021AFA30
#define K455_ROOTVNODE             0x021AFA30
#define K470_ROOTVNODE             0x021B89E0
#define K471_ROOTVNODE             0x021B89E0
#define K472_ROOTVNODE             0x021B89E0
#define K473_ROOTVNODE             0x021B89E0
#define K474_ROOTVNODE             0x021B89E0
#define K500_ROOTVNODE             0x022C19F0
#define K501_ROOTVNODE             0x022C19F0
#define K503_ROOTVNODE             0x022C1A70
#define K505_ROOTVNODE             0x022C1A70
#define K507_ROOTVNODE             0x022C1A70
#define K550_ROOTVNODE             0x022EF570
#define K553_ROOTVNODE             0x022EF570
#define K555_ROOTVNODE             0x022F3570
#define K556_ROOTVNODE             0x022F3570
#define K600_ROOTVNODE             0x021BFAC0
#define K602_ROOTVNODE             0x021BFAC0
#define K620_ROOTVNODE             0x021C3AC0
#define K650_ROOTVNODE             0x02300320
#define K651_ROOTVNODE             0x02300320
#define K670_ROOTVNODE             0x02300320
#define K671_ROOTVNODE             0x02300320
#define K672_ROOTVNODE             0x02300320
#define K700_ROOTVNODE             0x022C5750
#define K701_ROOTVNODE             0x022C5750
#define K702_ROOTVNODE             0x022C5750
#define K750_ROOTVNODE             0x01B463E0
#define K751_ROOTVNODE             0x01B463E0
#define K755_ROOTVNODE             0x01B463E0
#define K800_ROOTVNODE             0x01B8C730
#define K801_ROOTVNODE             0x01B8C730
#define K803_ROOTVNODE             0x01B8C730
#define K850_ROOTVNODE             0x01C66150
#define K852_ROOTVNODE             0x01C66150
#define K900_ROOTVNODE             0x021EFF20

// Used in Kernel Dumper
#define K300_COPYOUT               0x0
#define K310_COPYOUT               0x0
#define K311_COPYOUT               0x0
#define K315_COPYOUT               0x00480BB0
#define K350_COPYOUT               0x003B9220
#define K355_COPYOUT               0x003B9660
#define K370_COPYOUT               0x003B9750
#define K400_COPYOUT               0x00286C40
#define K401_COPYOUT               0x00286C40
#define K405_COPYOUT               0x00286D70
#define K406_COPYOUT               0x00286D70
#define K407_COPYOUT               0x00286D70
#define K450_COPYOUT               0x0014A7B0
#define K455_COPYOUT               0x0014A7B0
#define K470_COPYOUT               0x00149E40
#define K471_COPYOUT               0x00149E40
#define K472_COPYOUT               0x00149E40
#define K473_COPYOUT               0x00149E40
#define K474_COPYOUT               0x00149E40
#define K500_COPYOUT               0x001EA520
#define K501_COPYOUT               0x001EA520
#define K503_COPYOUT               0x001EA630
#define K505_COPYOUT               0x001EA630
#define K507_COPYOUT               0x001EA630
#define K550_COPYOUT               0x00405AC0
#define K553_COPYOUT               0x004059C0
#define K555_COPYOUT               0x00405D80
#define K556_COPYOUT               0x00405D80
#define K600_COPYOUT               0x00114800
#define K602_COPYOUT               0x00114800
#define K620_COPYOUT               0x00114800
#define K650_COPYOUT               0x003C1300
#define K651_COPYOUT               0x003C1300
#define K670_COPYOUT               0x003C16B0
#define K671_COPYOUT               0x003C16B0
#define K672_COPYOUT               0x003C16B0
#define K700_COPYOUT               0x0002F140
#define K701_COPYOUT               0x0002F140
#define K702_COPYOUT               0x0002F140
#define K750_COPYOUT               0x0028F900
#define K751_COPYOUT               0x0028F900
#define K755_COPYOUT               0x0028F900
#define K800_COPYOUT               0x0025E2C0
#define K801_COPYOUT               0x0025E2C0
#define K803_COPYOUT               0x0025E2C0
#define K850_COPYOUT               0x003A41F0
#define K852_COPYOUT               0x003A41F0
#define K900_COPYOUT               0x002715B0

// Used in Dumper, FTP, and Module Dumper
#define K300_MMAP_SELF_1           0x0
#define K310_MMAP_SELF_1           0x0
#define K311_MMAP_SELF_1           0x0
#define K315_MMAP_SELF_1           0x0045C240
#define K350_MMAP_SELF_1           0x00394BF0
#define K355_MMAP_SELF_1           0x00395020
#define K370_MMAP_SELF_1           0x003950F0
#define K400_MMAP_SELF_1           0x003604C0
#define K401_MMAP_SELF_1           0x003604C0
#define K405_MMAP_SELF_1           0x003605F0
#define K406_MMAP_SELF_1           0x00360600
#define K407_MMAP_SELF_1           0x00360600
#define K450_MMAP_SELF_1           0x0016A5B0
#define K455_MMAP_SELF_1           0x0016A5B0
#define K470_MMAP_SELF_1           0x00169810
#define K471_MMAP_SELF_1           0x00169810
#define K472_MMAP_SELF_1           0x00169810
#define K473_MMAP_SELF_1           0x00169810
#define K474_MMAP_SELF_1           0x00169810
#define K500_MMAP_SELF_1           0x000117B0
#define K501_MMAP_SELF_1           0x000117B0
#define K503_MMAP_SELF_1           0x000117B0
#define K505_MMAP_SELF_1           0x000117B0
#define K507_MMAP_SELF_1           0x000117B0
#define K550_MMAP_SELF_1           0x001B4990
#define K553_MMAP_SELF_1           0x001B4890
#define K555_MMAP_SELF_1           0x001B4C00
#define K556_MMAP_SELF_1           0x001B4C00
#define K600_MMAP_SELF_1           0x00459490
#define K602_MMAP_SELF_1           0x00459490
#define K620_MMAP_SELF_1           0x004594B0
#define K650_MMAP_SELF_1           0x00233890
#define K651_MMAP_SELF_1           0x00233890
#define K670_MMAP_SELF_1           0x00233C40
#define K671_MMAP_SELF_1           0x00233C40
#define K672_MMAP_SELF_1           0x00233C40
#define K700_MMAP_SELF_1           0x001CB8F0
#define K701_MMAP_SELF_1           0x001CB8F0
#define K702_MMAP_SELF_1           0x001CB8F0
#define K750_MMAP_SELF_1           0x00364D40
#define K751_MMAP_SELF_1           0x00364D40
#define K755_MMAP_SELF_1           0x00364D40
#define K800_MMAP_SELF_1           0x001D5780
#define K801_MMAP_SELF_1           0x001D5780
#define K803_MMAP_SELF_1           0x001D5780
#define K850_MMAP_SELF_1           0x00293650
#define K852_MMAP_SELF_1           0x00293650
#define K900_MMAP_SELF_1           0x0008BC90

// Used in Dumper, FTP, and Module Dumper
#define K300_MMAP_SELF_2           0x0
#define K310_MMAP_SELF_2           0x0
#define K311_MMAP_SELF_2           0x0
#define K315_MMAP_SELF_2           0x0045C250
#define K350_MMAP_SELF_2           0x00394C00
#define K355_MMAP_SELF_2           0x00395030
#define K370_MMAP_SELF_2           0x00395100
#define K400_MMAP_SELF_2           0x003604D0
#define K401_MMAP_SELF_2           0x003604D0
#define K405_MMAP_SELF_2           0x00360600
#define K406_MMAP_SELF_2           0x00360610
#define K407_MMAP_SELF_2           0x00360610
#define K450_MMAP_SELF_2           0x0016A5C0
#define K455_MMAP_SELF_2           0x0016A5C0
#define K470_MMAP_SELF_2           0x00169820
#define K471_MMAP_SELF_2           0x00169820
#define K472_MMAP_SELF_2           0x00169820
#define K473_MMAP_SELF_2           0x00169820
#define K474_MMAP_SELF_2           0x00169820
#define K500_MMAP_SELF_2           0x000117C0
#define K501_MMAP_SELF_2           0x000117C0
#define K503_MMAP_SELF_2           0x000117C0
#define K505_MMAP_SELF_2           0x000117C0
#define K507_MMAP_SELF_2           0x000117C0
#define K550_MMAP_SELF_2           0x001B49A0
#define K553_MMAP_SELF_2           0x001B48A0
#define K555_MMAP_SELF_2           0x001B4C10
#define K556_MMAP_SELF_2           0x001B4C10
#define K600_MMAP_SELF_2           0x004594A0
#define K602_MMAP_SELF_2           0x004594A0
#define K620_MMAP_SELF_2           0x004594C0
#define K650_MMAP_SELF_2           0x002338A0
#define K651_MMAP_SELF_2           0x002338A0
#define K670_MMAP_SELF_2           0x00233C50
#define K671_MMAP_SELF_2           0x00233C50
#define K672_MMAP_SELF_2           0x00233C50
#define K700_MMAP_SELF_2           0x001CB910
#define K701_MMAP_SELF_2           0x001CB910
#define K702_MMAP_SELF_2           0x001CB910
#define K750_MMAP_SELF_2           0x00364D60
#define K751_MMAP_SELF_2           0x00364D60
#define K755_MMAP_SELF_2           0x00364D60
#define K800_MMAP_SELF_2           0x001D57A0
#define K801_MMAP_SELF_2           0x001D57A0
#define K803_MMAP_SELF_2           0x001D57A0
#define K850_MMAP_SELF_2           0x00293670
#define K852_MMAP_SELF_2           0x00293670
#define K900_MMAP_SELF_2           0x0008BCB0

// Used in Module Dumper, App Dumper, and FTP
#define K300_MMAP_SELF_3           0x0
#define K310_MMAP_SELF_3           0x0
#define K311_MMAP_SELF_3           0x0
#define K315_MMAP_SELF_3           0x00414165
#define K350_MMAP_SELF_3           0x0034AF55
#define K355_MMAP_SELF_3           0x0034B385
#define K370_MMAP_SELF_3           0x0034B455
#define K400_MMAP_SELF_3           0x0031ED07
#define K401_MMAP_SELF_3           0x0031ED07
#define K405_MMAP_SELF_3           0x0031EE37
#define K406_MMAP_SELF_3           0x0031EE47
#define K407_MMAP_SELF_3           0x0031EE47
#define K450_MMAP_SELF_3           0x00143BE7
#define K455_MMAP_SELF_3           0x00143BE7
#define K470_MMAP_SELF_3           0x00143277
#define K471_MMAP_SELF_3           0x00143277
#define K472_MMAP_SELF_3           0x00143277
#define K473_MMAP_SELF_3           0x00143277
#define K474_MMAP_SELF_3           0x00143277
#define K500_MMAP_SELF_3           0x0013EF2F
#define K501_MMAP_SELF_3           0x0013EF2F
#define K503_MMAP_SELF_3           0x0013F03F
#define K505_MMAP_SELF_3           0x0013F03F
#define K507_MMAP_SELF_3           0x0013F03F
#define K550_MMAP_SELF_3           0x003C3FBD
#define K553_MMAP_SELF_3           0x003C3EBD
#define K555_MMAP_SELF_3           0x003C427D
#define K556_MMAP_SELF_3           0x003C427D
#define K600_MMAP_SELF_3           0x002420A7
#define K602_MMAP_SELF_3           0x002420A7
#define K620_MMAP_SELF_3           0x002420A7
#define K650_MMAP_SELF_3           0x000AD2E4
#define K651_MMAP_SELF_3           0x000AD2E4
#define K670_MMAP_SELF_3           0x000AD2E4
#define K671_MMAP_SELF_3           0x000AD2E4
#define K672_MMAP_SELF_3           0x000AD2E4
#define K700_MMAP_SELF_3           0x001D40BB
#define K701_MMAP_SELF_3           0x001D40BB
#define K702_MMAP_SELF_3           0x001D40BB
#define K750_MMAP_SELF_3           0x000DCED1
#define K751_MMAP_SELF_3           0x000DCED1
#define K755_MMAP_SELF_3           0x000DCED1
#define K800_MMAP_SELF_3           0x000FED61
#define K801_MMAP_SELF_3           0x000FED61
#define K803_MMAP_SELF_3           0x000FED61
#define K850_MMAP_SELF_3           0x00084411
#define K852_MMAP_SELF_3           0x00084411
#define K900_MMAP_SELF_3           0x00168051

// Used in Disable ASLR
// May also require changes to the `kpayload_aslr` function in `payload_utils.c`
#define K300_DISABLE_ASLR          0x0
#define K310_DISABLE_ASLR          0x0
#define K311_DISABLE_ASLR          0x0
#define K315_DISABLE_ASLR          0x0
#define K350_DISABLE_ASLR          0x00406942
#define K355_DISABLE_ASLR          0x00406E82
#define K370_DISABLE_ASLR          0x00407242
#define K400_DISABLE_ASLR          0x002861A6
#define K401_DISABLE_ASLR          0x002861A6
#define K405_DISABLE_ASLR          0x002862D6
#define K406_DISABLE_ASLR          0x002862D6
#define K407_DISABLE_ASLR          0x002862D6
#define K450_DISABLE_ASLR          0x001BA559
#define K455_DISABLE_ASLR          0x001BA559
#define K470_DISABLE_ASLR          0x001BC769
#define K471_DISABLE_ASLR          0x001BC769
#define K472_DISABLE_ASLR          0x001BC769
#define K473_DISABLE_ASLR          0x001BC769
#define K474_DISABLE_ASLR          0x001BC769
#define K500_DISABLE_ASLR          0x00194765
#define K501_DISABLE_ASLR          0x00194765
#define K503_DISABLE_ASLR          0x00194875
#define K505_DISABLE_ASLR          0x00194875
#define K507_DISABLE_ASLR          0x00194875
#define K550_DISABLE_ASLR          0x0007A123
#define K553_DISABLE_ASLR          0x0007A123
#define K555_DISABLE_ASLR          0x0007A123
#define K556_DISABLE_ASLR          0x0007A123
#define K600_DISABLE_ASLR          0x0021D745
#define K602_DISABLE_ASLR          0x0021D745
#define K620_DISABLE_ASLR          0x0021D745
#define K650_DISABLE_ASLR          0x003CE931
#define K651_DISABLE_ASLR          0x003CE931
#define K670_DISABLE_ASLR          0x003CECE1
#define K671_DISABLE_ASLR          0x003CECE1
#define K672_DISABLE_ASLR          0x003CEC8A
#define K700_DISABLE_ASLR          0x000C1F9A
#define K701_DISABLE_ASLR          0x000C1F9A
#define K702_DISABLE_ASLR          0x000C1F9A
#define K750_DISABLE_ASLR          0x00218AF4
#define K751_DISABLE_ASLR          0x00218AF4
#define K755_DISABLE_ASLR          0x00218AF4
#define K800_DISABLE_ASLR          0x002856F4
#define K801_DISABLE_ASLR          0x002856F4
#define K803_DISABLE_ASLR          0x002856F4
#define K850_DISABLE_ASLR          0x00215154
#define K852_DISABLE_ASLR          0x00215154
#define K900_DISABLE_ASLR          0x0005F824

// Used in Enable Browser
#define K300_REG_MGR_SET_INT       0x0
#define K310_REG_MGR_SET_INT       0x0
#define K311_REG_MGR_SET_INT       0x0
#define K315_REG_MGR_SET_INT       0x0
#define K350_REG_MGR_SET_INT       0x004750E0
#define K355_REG_MGR_SET_INT       0x00475620
#define K370_REG_MGR_SET_INT       0x004759C0
#define K400_REG_MGR_SET_INT       0x004CE900
#define K401_REG_MGR_SET_INT       0x004CE880
#define K405_REG_MGR_SET_INT       0x004CEAB0
#define K406_REG_MGR_SET_INT       0x004CEBD0
#define K407_REG_MGR_SET_INT       0x004CED10
#define K450_REG_MGR_SET_INT       0x004D6F40
#define K455_REG_MGR_SET_INT       0x004D6F00
#define K470_REG_MGR_SET_INT       0x004D84D0
#define K471_REG_MGR_SET_INT       0x004D8460
#define K472_REG_MGR_SET_INT       0x004D8460
#define K473_REG_MGR_SET_INT       0x004D8460
#define K474_REG_MGR_SET_INT       0x004D8580
#define K500_REG_MGR_SET_INT       0x004F8940
#define K501_REG_MGR_SET_INT       0x004F8940
#define K503_REG_MGR_SET_INT       0x004F8CD0
#define K505_REG_MGR_SET_INT       0x004F8D10
#define K507_REG_MGR_SET_INT       0x004F8D10
#define K550_REG_MGR_SET_INT       0x00509260
#define K553_REG_MGR_SET_INT       0x00509160
#define K555_REG_MGR_SET_INT       0x00509520
#define K556_REG_MGR_SET_INT       0x00509520
#define K600_REG_MGR_SET_INT       0x00502210
#define K602_REG_MGR_SET_INT       0x00502210
#define K620_REG_MGR_SET_INT       0x00502230
#define K650_REG_MGR_SET_INT       0x00507420
#define K651_REG_MGR_SET_INT       0x00507420
#define K670_REG_MGR_SET_INT       0x005077D0
#define K671_REG_MGR_SET_INT       0x005077D0
#define K672_REG_MGR_SET_INT       0x005077D0
#define K700_REG_MGR_SET_INT       0x005013B0
#define K701_REG_MGR_SET_INT       0x005013B0
#define K702_REG_MGR_SET_INT       0x005013B0
#define K750_REG_MGR_SET_INT       0x004FEFC0
#define K751_REG_MGR_SET_INT       0x004FEFC0
#define K755_REG_MGR_SET_INT       0x004FEFC0
#define K800_REG_MGR_SET_INT       0x004E42A0
#define K801_REG_MGR_SET_INT       0x004E42A0
#define K803_REG_MGR_SET_INT       0x004E42A0
#define K850_REG_MGR_SET_INT       0x004E9DC0
#define K852_REG_MGR_SET_INT       0x004E9DC0
#define K900_REG_MGR_SET_INT       0x004E8B10

// Used in Kernel Clock
#define K300_SET_TIME              0x0
#define K310_SET_TIME              0x0
#define K311_SET_TIME              0x0
#define K315_SET_TIME              0x0
#define K350_SET_TIME              0x005CF410 // Needs Verified
#define K355_SET_TIME              0x005CFB80 // Needs Verified
#define K370_SET_TIME              0x005D3630 // Needs Verified
#define K400_SET_TIME              0x00609770 // Needs Verified
#define K401_SET_TIME              0x006096F0 // Needs Verified
#define K405_SET_TIME              0x00609920 // Needs Verified
#define K406_SET_TIME              0x00609A90 // Needs Verified
#define K407_SET_TIME              0x00609BD0 // Needs Verified
#define K450_SET_TIME              0x006175D0
#define K455_SET_TIME              0x00617570
#define K470_SET_TIME              0x0061A8C0
#define K471_SET_TIME              0x0061A840
#define K472_SET_TIME              0x0061A840
#define K473_SET_TIME              0x0061A840
#define K474_SET_TIME              0x0061A960
#define K500_SET_TIME              0x00633CB0
#define K501_SET_TIME              0x00633CB0
#define K503_SET_TIME              0x00634050
#define K505_SET_TIME              0x00634090
#define K507_SET_TIME              0x00634090
#define K550_SET_TIME              0x0064C1C0
#define K553_SET_TIME              0x0064C0C0
#define K555_SET_TIME              0x0064C600
#define K556_SET_TIME              0x0064C600
#define K600_SET_TIME              0x0064F2D0
#define K602_SET_TIME              0x0064F2D0
#define K620_SET_TIME              0x0064F790
#define K650_SET_TIME              0x00650750
#define K651_SET_TIME              0x00650750
#define K670_SET_TIME              0x006512E0
#define K671_SET_TIME              0x006512E0
#define K672_SET_TIME              0x006512E0
#define K700_SET_TIME              0x0064DA90 // Needs Verified
#define K701_SET_TIME              0x0064DA90 // Needs Verified
#define K702_SET_TIME              0x0064DA90 // Needs Verified
#define K750_SET_TIME              0x0064CE20 // Needs Verified
#define K751_SET_TIME              0x0064CE20 // Needs Verified
#define K755_SET_TIME              0x0064CE20 // Needs Verified
#define K800_SET_TIME              0x00630C20 // Needs Verified
#define K801_SET_TIME              0x00630C20 // Needs Verified
#define K803_SET_TIME              0x00630C20 // Needs Verified
#define K850_SET_TIME              0x006320C0 // Needs Verified
#define K852_SET_TIME              0x006320C0 // Needs Verified
#define K900_SET_TIME              0x00634450 // Needs Verified

// Used in Kernel Clock
#define K300_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K310_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K311_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K315_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K350_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K355_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K370_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K400_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K401_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K405_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K406_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K407_CLEAR_TIME_DIFFERENCE 0x00000000 // Needs Verified
#define K450_CLEAR_TIME_DIFFERENCE 0x00617BB0
#define K455_CLEAR_TIME_DIFFERENCE 0x00617B50
#define K470_CLEAR_TIME_DIFFERENCE 0x0061AEA0
#define K471_CLEAR_TIME_DIFFERENCE 0x0061AE20
#define K472_CLEAR_TIME_DIFFERENCE 0x0061AE20
#define K473_CLEAR_TIME_DIFFERENCE 0x0061AE20
#define K474_CLEAR_TIME_DIFFERENCE 0x0061AF40
#define K500_CLEAR_TIME_DIFFERENCE 0x006342B0
#define K501_CLEAR_TIME_DIFFERENCE 0x006342B0
#define K503_CLEAR_TIME_DIFFERENCE 0x00634650
#define K505_CLEAR_TIME_DIFFERENCE 0x00634690
#define K507_CLEAR_TIME_DIFFERENCE 0x00634690
#define K550_CLEAR_TIME_DIFFERENCE 0x0064C7C0
#define K553_CLEAR_TIME_DIFFERENCE 0x0064C6C0
#define K555_CLEAR_TIME_DIFFERENCE 0x0064CC00
#define K556_CLEAR_TIME_DIFFERENCE 0x0064CC00
#define K600_CLEAR_TIME_DIFFERENCE 0x0064EAE0
#define K602_CLEAR_TIME_DIFFERENCE 0x0064EAE0
#define K620_CLEAR_TIME_DIFFERENCE 0x0064EFA0
#define K650_CLEAR_TIME_DIFFERENCE 0x0064FF60
#define K651_CLEAR_TIME_DIFFERENCE 0x0064FF60
#define K670_CLEAR_TIME_DIFFERENCE 0x006507D0
#define K671_CLEAR_TIME_DIFFERENCE 0x006507D0
#define K672_CLEAR_TIME_DIFFERENCE 0x006507D0
#define K700_CLEAR_TIME_DIFFERENCE 0x0064CF70
#define K701_CLEAR_TIME_DIFFERENCE 0x0064CF70
#define K702_CLEAR_TIME_DIFFERENCE 0x0064CF70
#define K750_CLEAR_TIME_DIFFERENCE 0x0064C300
#define K751_CLEAR_TIME_DIFFERENCE 0x0064C300
#define K755_CLEAR_TIME_DIFFERENCE 0x0064C300
#define K800_CLEAR_TIME_DIFFERENCE 0x00630100
#define K801_CLEAR_TIME_DIFFERENCE 0x00630100
#define K803_CLEAR_TIME_DIFFERENCE 0x00630100
#define K850_CLEAR_TIME_DIFFERENCE 0x006315A0
#define K852_CLEAR_TIME_DIFFERENCE 0x006315A0
#define K900_CLEAR_TIME_DIFFERENCE 0x00633930

// Used in ToDex
#define K300_TARGET_ID             0x0
#define K310_TARGET_ID             0x0
#define K311_TARGET_ID             0x0
#define K315_TARGET_ID             0x0
#define K350_TARGET_ID             0x0
#define K355_TARGET_ID             0x0
#define K370_TARGET_ID             0x0
#define K400_TARGET_ID             0x0200151D
#define K401_TARGET_ID             0x0200151D
#define K405_TARGET_ID             0x0200151D
#define K406_TARGET_ID             0x0200151D
#define K407_TARGET_ID             0x0200551D
#define K450_TARGET_ID             0x01B6D08D
#define K455_TARGET_ID             0x01B6D08D
#define K470_TARGET_ID             0x01B7D08D
#define K471_TARGET_ID             0x01B7D08D
#define K472_TARGET_ID             0x01B7D08D
#define K473_TARGET_ID             0x01B7D08D
#define K474_TARGET_ID             0x01B7D08D
#define K500_TARGET_ID             0x01CD068D
#define K501_TARGET_ID             0x01CD068D
#define K503_TARGET_ID             0x01CD068D
#define K505_TARGET_ID             0x01CD068D
#define K507_TARGET_ID             0x01CD068D
#define K550_TARGET_ID             0x022BBF8D
#define K553_TARGET_ID             0x022BBF8D
#define K555_TARGET_ID             0x022BFF8D
#define K556_TARGET_ID             0x022BFF8D
#define K600_TARGET_ID             0x02159B8D
#define K602_TARGET_ID             0x02159B8D
#define K620_TARGET_ID             0x0215DB8D
#define K650_TARGET_ID             0x01BD800D
#define K651_TARGET_ID             0x01BD800D
#define K670_TARGET_ID             0x01BD800D
#define K671_TARGET_ID             0x01BD800D
#define K672_TARGET_ID             0x01BD800D
#define K700_TARGET_ID             0x022FED8D
#define K701_TARGET_ID             0x022FED8D
#define K702_TARGET_ID             0x022FED8D
#define K750_TARGET_ID             0x022287CD
#define K751_TARGET_ID             0x022287CD
#define K755_TARGET_ID             0x022287CD
#define K800_TARGET_ID             0x0
#define K801_TARGET_ID             0x0
#define K803_TARGET_ID             0x0
#define K850_TARGET_ID             0x0
#define K852_TARGET_ID             0x0
#define K900_TARGET_ID             0x0

// Used in Perm UART
#define K300_ICC_NVS_WRITE         0x0
#define K310_ICC_NVS_WRITE         0x0
#define K311_ICC_NVS_WRITE         0x0
#define K315_ICC_NVS_WRITE         0x0
#define K350_ICC_NVS_WRITE         0x003EED70
#define K355_ICC_NVS_WRITE         0x003EF1E0
#define K370_ICC_NVS_WRITE         0x003EF570
#define K400_ICC_NVS_WRITE         0x003C8270
#define K401_ICC_NVS_WRITE         0x003C8270
#define K405_ICC_NVS_WRITE         0x003C83A0
#define K406_ICC_NVS_WRITE         0x003C83E0
#define K407_ICC_NVS_WRITE         0x003C83E0
#define K450_ICC_NVS_WRITE         0x0001B770
#define K455_ICC_NVS_WRITE         0x0001B770
#define K470_ICC_NVS_WRITE         0x0001B770
#define K471_ICC_NVS_WRITE         0x0001B770
#define K472_ICC_NVS_WRITE         0x0001B770
#define K473_ICC_NVS_WRITE         0x0001B770
#define K474_ICC_NVS_WRITE         0x0001B770
#define K500_ICC_NVS_WRITE         0x003952A0
#define K501_ICC_NVS_WRITE         0x003952A0
#define K503_ICC_NVS_WRITE         0x00395630
#define K505_ICC_NVS_WRITE         0x00395670
#define K507_ICC_NVS_WRITE         0x00395670
#define K550_ICC_NVS_WRITE         0x004213F0
#define K553_ICC_NVS_WRITE         0x004212F0
#define K555_ICC_NVS_WRITE         0x004216B0
#define K556_ICC_NVS_WRITE         0x004216B0
#define K600_ICC_NVS_WRITE         0x00462160
#define K602_ICC_NVS_WRITE         0x00462160
#define K620_ICC_NVS_WRITE         0x00462180
#define K650_ICC_NVS_WRITE         0x00463EE0
#define K651_ICC_NVS_WRITE         0x00463EE0
#define K670_ICC_NVS_WRITE         0x00464290
#define K671_ICC_NVS_WRITE         0x00464290
#define K672_ICC_NVS_WRITE         0x00464290
#define K700_ICC_NVS_WRITE         0x003488E0
#define K701_ICC_NVS_WRITE         0x003488E0
#define K702_ICC_NVS_WRITE         0x003488E0
#define K750_ICC_NVS_WRITE         0x0002F770
#define K751_ICC_NVS_WRITE         0x0002F770
#define K755_ICC_NVS_WRITE         0x0002F770
#define K800_ICC_NVS_WRITE         0x0041EC60
#define K801_ICC_NVS_WRITE         0x0041EC60
#define K803_ICC_NVS_WRITE         0x0041EC60
#define K850_ICC_NVS_WRITE         0x00393B20
#define K852_ICC_NVS_WRITE         0x00393B20
#define K900_ICC_NVS_WRITE         0x0010B150

#define K300_NPDRM_OPEN            0x0
#define K310_NPDRM_OPEN            0x0
#define K311_NPDRM_OPEN            0x0
#define K315_NPDRM_OPEN            0x0
#define K350_NPDRM_OPEN            0x0
#define K355_NPDRM_OPEN            0x0
#define K370_NPDRM_OPEN            0x0
#define K400_NPDRM_OPEN            0x0
#define K401_NPDRM_OPEN            0x0
#define K405_NPDRM_OPEN            0x0
#define K406_NPDRM_OPEN            0x0
#define K407_NPDRM_OPEN            0x0
#define K450_NPDRM_OPEN            0x0
#define K455_NPDRM_OPEN            0x0
#define K470_NPDRM_OPEN            0x0
#define K471_NPDRM_OPEN            0x0
#define K472_NPDRM_OPEN            0x0
#define K473_NPDRM_OPEN            0x0
#define K474_NPDRM_OPEN            0x0
#define K500_NPDRM_OPEN            0x0064D420
#define K501_NPDRM_OPEN            0x0064D420
#define K503_NPDRM_OPEN            0x0064D7C0
#define K505_NPDRM_OPEN            0x0064D800
#define K507_NPDRM_OPEN            0x0064D800
#define K550_NPDRM_OPEN            0x00664DE0
#define K553_NPDRM_OPEN            0x00664CE0
#define K555_NPDRM_OPEN            0x00665220
#define K556_NPDRM_OPEN            0x00665220
#define K600_NPDRM_OPEN            0x00669220
#define K602_NPDRM_OPEN            0x00669220
#define K620_NPDRM_OPEN            0x006696E0
#define K650_NPDRM_OPEN            0x00669020
#define K651_NPDRM_OPEN            0x00669020
#define K670_NPDRM_OPEN            0x0066A630
#define K671_NPDRM_OPEN            0x0066A630
#define K672_NPDRM_OPEN            0x0066A630
#define K700_NPDRM_OPEN            0x00669B80
#define K701_NPDRM_OPEN            0x00669B80
#define K702_NPDRM_OPEN            0x00669B80
#define K750_NPDRM_OPEN            0x006678C0
#define K751_NPDRM_OPEN            0x006678C0
#define K755_NPDRM_OPEN            0x006678C0
#define K800_NPDRM_OPEN            0x0064D680
#define K801_NPDRM_OPEN            0x0064D680
#define K803_NPDRM_OPEN            0x0064D680
#define K850_NPDRM_OPEN            0x0064D3E0
#define K852_NPDRM_OPEN            0x0064D3E0
#define K900_NPDRM_OPEN            0x0064F160

#define K300_NPDRM_CLOSE           0x0
#define K310_NPDRM_CLOSE           0x0
#define K311_NPDRM_CLOSE           0x0
#define K315_NPDRM_CLOSE           0x0
#define K350_NPDRM_CLOSE           0x0
#define K355_NPDRM_CLOSE           0x0
#define K370_NPDRM_CLOSE           0x0
#define K400_NPDRM_CLOSE           0x0
#define K401_NPDRM_CLOSE           0x0
#define K405_NPDRM_CLOSE           0x0
#define K406_NPDRM_CLOSE           0x0
#define K407_NPDRM_CLOSE           0x0
#define K450_NPDRM_CLOSE           0x0
#define K455_NPDRM_CLOSE           0x0
#define K470_NPDRM_CLOSE           0x0
#define K471_NPDRM_CLOSE           0x0
#define K472_NPDRM_CLOSE           0x0
#define K473_NPDRM_CLOSE           0x0
#define K474_NPDRM_CLOSE           0x0
#define K500_NPDRM_CLOSE           0x0064D440
#define K501_NPDRM_CLOSE           0x0064D440
#define K503_NPDRM_CLOSE           0x0064D7E0
#define K505_NPDRM_CLOSE           0x0064D820
#define K507_NPDRM_CLOSE           0x0064D820
#define K550_NPDRM_CLOSE           0x00664E00
#define K553_NPDRM_CLOSE           0x00664D00
#define K555_NPDRM_CLOSE           0x00665240
#define K556_NPDRM_CLOSE           0x00665240
#define K600_NPDRM_CLOSE           0x00669240
#define K602_NPDRM_CLOSE           0x00669240
#define K620_NPDRM_CLOSE           0x00669700
#define K650_NPDRM_CLOSE           0x00669040
#define K651_NPDRM_CLOSE           0x00669040
#define K670_NPDRM_CLOSE           0x0066A650
#define K671_NPDRM_CLOSE           0x0066A650
#define K672_NPDRM_CLOSE           0x0066A650
#define K700_NPDRM_CLOSE           0x00669BA0
#define K701_NPDRM_CLOSE           0x00669BA0
#define K702_NPDRM_CLOSE           0x00669BA0
#define K750_NPDRM_CLOSE           0x006678E0
#define K751_NPDRM_CLOSE           0x006678E0
#define K755_NPDRM_CLOSE           0x006678E0
#define K800_NPDRM_CLOSE           0x0064D6A0
#define K801_NPDRM_CLOSE           0x0064D6A0
#define K803_NPDRM_CLOSE           0x0064D6A0
#define K850_NPDRM_CLOSE           0x0064D400
#define K852_NPDRM_CLOSE           0x0064D400
#define K900_NPDRM_CLOSE           0x0064F180

#define K300_NPDRM_IOCTL           0x0
#define K310_NPDRM_IOCTL           0x0
#define K311_NPDRM_IOCTL           0x0
#define K315_NPDRM_IOCTL           0x0
#define K350_NPDRM_IOCTL           0x0
#define K355_NPDRM_IOCTL           0x0
#define K370_NPDRM_IOCTL           0x0
#define K400_NPDRM_IOCTL           0x0
#define K401_NPDRM_IOCTL           0x0
#define K405_NPDRM_IOCTL           0x0
#define K406_NPDRM_IOCTL           0x0
#define K407_NPDRM_IOCTL           0x0
#define K450_NPDRM_IOCTL           0x0
#define K455_NPDRM_IOCTL           0x0
#define K470_NPDRM_IOCTL           0x0
#define K471_NPDRM_IOCTL           0x0
#define K472_NPDRM_IOCTL           0x0
#define K473_NPDRM_IOCTL           0x0
#define K474_NPDRM_IOCTL           0x0
#define K500_NPDRM_IOCTL           0x0064D497
#define K501_NPDRM_IOCTL           0x0064D497
#define K503_NPDRM_IOCTL           0x0064D837
#define K505_NPDRM_IOCTL           0x0064D877
#define K507_NPDRM_IOCTL           0x0064D877
#define K550_NPDRM_IOCTL           0x00664E57
#define K553_NPDRM_IOCTL           0x00664D57
#define K555_NPDRM_IOCTL           0x00665297
#define K556_NPDRM_IOCTL           0x00665297
#define K600_NPDRM_IOCTL           0x00669297
#define K602_NPDRM_IOCTL           0x00669297
#define K620_NPDRM_IOCTL           0x00669757
#define K650_NPDRM_IOCTL           0x00669097
#define K651_NPDRM_IOCTL           0x00669097
#define K670_NPDRM_IOCTL           0x0066A6A7
#define K671_NPDRM_IOCTL           0x0066A6A7
#define K672_NPDRM_IOCTL           0x0066A6A7
#define K700_NPDRM_IOCTL           0x00669BF7
#define K701_NPDRM_IOCTL           0x00669BF7
#define K702_NPDRM_IOCTL           0x00669BF7
#define K750_NPDRM_IOCTL           0x00667937
#define K751_NPDRM_IOCTL           0x00667937
#define K755_NPDRM_IOCTL           0x00667937
#define K800_NPDRM_IOCTL           0x0064D6F7
#define K801_NPDRM_IOCTL           0x0064D6F7
#define K803_NPDRM_IOCTL           0x0064D6F7
#define K850_NPDRM_IOCTL           0x0064D457
#define K852_NPDRM_IOCTL           0x0064D457
#define K900_NPDRM_IOCTL           0x0064F1D7

// clang-format on

#endif
