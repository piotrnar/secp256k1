#include <stdio.h>
#include "secp256k1_dll.h"

static unsigned char hasz[] = {0x33,0x82,0x21,0x95,0x55,0xdd,0xbb,0x5b,0x00,0xe0,0x09,0x0f,0x46,0x9e,0x59,0x0b,0xa1,0xea,0xe0,0x3c,0x7f,0x28,0xab,0x93,0x7d,0xe3,0x30,0xaa,0x60,0x29,0x4e,0xd6};
static unsigned char pkey[] = {0x04,0x0e,0xae,0xbc,0xd1,0xdf,0x2d,0xf8,0x53,0xd6,0x6c,0xe0,0xe1,0xb0,0xfd,0xa0,0x7f,0x67,0xd1,0xca,0xbe,0xfd,0xe9,0x85,0x14,0xaa,0xd7,0x95,0xb8,0x6a,0x6e,0xa6,0x6d,0xbe,0xb2,0x6b,0x67,0xd7,0xa0,0x0e,0x24,0x47,0xba,0xec,0xcc,0x8a,0x4c,0xef,0x7c,0xd3,0xca,0xd6,0x73,0x76,0xac,0x1c,0x57,0x85,0xae,0xeb,0xb4,0xf6,0x44,0x1c,0x16};
static unsigned char sign[] = {0x30,0x45,0x02,0x21,0x00,0xfe,0x00,0xe0,0x13,0xc2,0x44,0x06,0x28,0x47,0x04,0x5a,0xe7,0xeb,0x73,0xb0,0x3f,0xca,0x58,0x3e,0x9a,0xa5,0xdb,0xd0,0x30,0xa8,0xfd,0x1c,0x6d,0xfc,0xf1,0x1b,0x10,0x02,0x20,0x7d,0x0d,0x04,0xfe,0xd8,0xfa,0x1e,0x93,0x00,0x74,0x68,0xd5,0xa9,0xe1,0x34,0xb0,0xa7,0x02,0x3b,0x6d,0x31,0xdb,0x4e,0x50,0x94,0x2d,0x43,0xa2,0x50,0xf4,0xd0,0x7c,0x01};

int main()
{
	int res;

	printf("Testing EC_Verify...\n");
	res = EC_Verify(hasz, sizeof hasz, sign, sizeof sign, pkey, sizeof pkey);
	if (res!=1) {
		printf("Verify not failed while it should\n");
	}

	hasz[0]++;
	res = EC_Verify(hasz, sizeof hasz, sign, sizeof sign, pkey, sizeof pkey);
	if (res!=0) {
		printf("Verify not failed while it should\n");
	}

	res = EC_Verify(hasz, sizeof hasz, sign, sizeof sign, pkey+1, sizeof pkey - 1);
	if (res>=0) {
		printf("Negative result expected - %d got\n", res);
	}

	res = EC_Verify(hasz, sizeof hasz, sign+1, sizeof sign - 1, pkey, sizeof pkey);
	if (res>=0) {
		printf("Yet negative result expected - %d got\n", res);
	}

	res = EC_Verify(hasz+1, sizeof hasz - 1, sign, sizeof sign, pkey, sizeof pkey);
	if (res!=0) {
		printf("Zero expected - %d got\n", res);
	}

	printf("Done\n");

	return 0;
}
