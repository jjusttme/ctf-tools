/*
 * bcrypt cracker patch for JtR, common code. 2014 by JimF
 * This file takes replicated but common code, shared between the CPU
 * and the GPU formats, and places it into one common location
 */
#if !defined (BF_common_h__)
#define BF_common_h__

#include "arch.h"
#include "formats.h"

extern struct fmt_tests BF_common_tests[];

#define CIPHERTEXT_LENGTH		60
/* Number of Blowfish rounds, this is also hardcoded into a few places */
#define BF_ROUNDS			16

typedef ARCH_WORD_32 BF_word;

/*
 * Binary salt type, also keeps the number of rounds and hash sub-type.
 */
typedef struct {
	BF_word salt[4];
	unsigned char rounds;
	char subtype;
} BF_salt;

/*
 * P-box and S-box tables initialized with digits of Pi.
 */
typedef BF_word BF_key[BF_ROUNDS + 2];
struct BF_ctx {
	BF_word S[4][0x100];
	BF_key P;
};

/*
 * Binary ciphertext type.
 */
typedef BF_word BF_binary[6];

/*
 * Magic IV for 64 Blowfish encryptions that we do at the end.
 * The string is "OrpheanBeholderScryDoubt" on big-endian.
 */
extern BF_word BF_magic_w[6];

/*
 * P-box and S-box tables initialized with digits of Pi.
 */
extern struct BF_ctx BF_init_state;

int BF_common_valid(char *ciphertext, struct fmt_main *self);
void *BF_common_get_binary(char *ciphertext);
void *BF_common_get_salt(char *ciphertext);

#if FMT_MAIN_VERSION > 11
unsigned int BF_common_iteration_count(void *salt);
#endif

#if ARCH_LITTLE_ENDIAN
void BF_swap(BF_word *x, int count);
#else
#define BF_swap(x, count)
#endif

#endif // BF_common_h__
