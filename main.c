#include <stdio.h>
#include <stdint.h>

#define ROR(x, r) ((x >> r) | (x << (32 - r)))
#define ROL(x, r) ((x << r) | (x >> (32 - r)))
#define  R(x, y, k) (x = ROR(x, 7), x += y, x ^= k, y = ROL(y, 2), y ^= x)
#define RR(x, y, k) (y ^= x, y = ROR(y, 2), x ^= k, x -= y, x = ROL(x, 7))
#define ROUNDS 16

void speck_encrypt(uint32_t cypher[2], uint32_t const plain[2], uint32_t const key[2])
{
   uint32_t y = plain[0], x = plain[1], b = key[0], a = key[1];

   R(x, y, b);
   for (int i = 0; i < ROUNDS - 1; i++)
   {
      R(a, b, i);
      R(x, y, b);
   }

   cypher[0] = y;
   cypher[1] = x;
}

void speck_decrypt(uint32_t const cypher[2], uint32_t plain[2], uint32_t const key[2])
{
   uint32_t y = cypher[0], x = cypher[1], b = key[0], a = key[1];

   for (int i = 0; i < ROUNDS - 1; i++) R(a, b, i);   // get current key

   RR(x, y, b);
   for (int i = ROUNDS-2; i>=0; i--)
   {
      RR(a, b, i);
      RR(x, y, b);
   }

   plain[0] = y;
   plain[1] = x;
}

int main(int argc , char *argv[])
{
    uint32_t plain[] = {0x01234567, 0x89ABCDEF};
    uint32_t cypher[] = {0x00, 0x00};
    uint32_t key[] = {0xAAAAAAAA, 0x55555555};
    speck_encrypt(cypher, plain, key);
    printf("%04x %04x \n", cypher[0], cypher[1]);
    speck_decrypt(cypher, plain, key);
    printf("%04x %04x \n", plain[0], plain[1]);
	return 0;
}