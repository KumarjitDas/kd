/**
 * @file kdGenMemOpsCopyBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCopyBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCopyBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static bool
kdi_BytesEqual(const byte *a, const byte *b, usize sz)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (a[i] != b[i])
        {
            return RESULT_FAILURE;
        }
    }

    return RESULT_SUCCESS;
}


static void
kdi_FillSeq(byte *dst, usize sz, byte start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (byte)(start + (byte)i);
    }
}


static void
kdi_FillVal(byte *dst, usize sz, byte val)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = val;
    }
}


void
BasicArguments(void)
{
    /*
     * Test NULL pointer validation, zero-size parameters, and out-of-bounds indices.
     * All failure cases should set copied_sz to 0 (if pointer valid)
     * and leave destination unchanged.
     */
    byte  dst[64];
    byte  src[64];
    byte  dst_orig[64];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(dst, USIZE_C(64), U8_C(0xAA));
    kdi_FillVal(dst_orig, USIZE_C(64), U8_C(0xAA));
    kdi_FillSeq(src, USIZE_C(64), U8_C(0x10));

    /* copied_sz pointer is null */
    result = GenMemOpsCopyBound(dst, USIZE_C(64), null, src, USIZE_C(64), USIZE_C(0), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_base is null */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(null, USIZE_C(64), &copied_sz, src, USIZE_C(64), USIZE_C(0), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));

    /* src_base is null */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(64), &copied_sz, null, USIZE_C(64), USIZE_C(0), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_idx out of bounds (equals dst_base_sz) */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(64), &copied_sz, src, USIZE_C(64), USIZE_C(64), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_idx out of bounds (greater than dst_base_sz) */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(64), &copied_sz, src, USIZE_C(64), USIZE_C(100), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_idx out of bounds (equals src_base_sz) */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(64), &copied_sz, src, USIZE_C(64), USIZE_C(0), USIZE_C(64), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_idx out of bounds (greater than src_base_sz) */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(64), &copied_sz, src, USIZE_C(64), USIZE_C(0), USIZE_C(100), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* byte_count is zero */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(64), &copied_sz, src, USIZE_C(64), USIZE_C(0), USIZE_C(0), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactCopyWithinBounds(void)
{
    /*
     * Copy src[10..25] (16 bytes) to dst[5..20] (16 bytes).
     * Both regions fit exactly, no truncation.
     */
    byte  dst[32];
    byte  dst_orig[32];
    byte  src[40];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ExactCopyWithinBounds -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xFF));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xFF));
    kdi_FillSeq(src, USIZE_C(40), U8_C(0x00));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(32), &copied_sz, src, USIZE_C(40), USIZE_C(5), USIZE_C(10), USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(16));

    /* Head of dst (0..4) should remain unchanged */
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(5)) == RESULT_SUCCESS);

    /* Middle of dst (5..20) should contain src[10..25] */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(dst[USIZE_C(5) + i] == src[USIZE_C(10) + i]);
    }

    /* Tail of dst (21..31) should remain unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(21), dst_orig + USIZE_C(21), USIZE_C(11)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
CopyAtStartOfBothBuffers(void)
{
    /*
     * Copy src[0..15] to dst[0..15].
     * Both starting at index 0.
     */
    byte  dst[32];
    byte  dst_orig[32];
    byte  src[32];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "CopyAtStartOfBothBuffers -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xEE));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xEE));
    kdi_FillSeq(src, USIZE_C(32), U8_C(0x20));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(32), &copied_sz, src, USIZE_C(32), USIZE_C(0), USIZE_C(0), USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(16));

    /* First 16 bytes should be copied */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(dst[i] == src[i]);
    }

    /* Remaining bytes should be unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(16), dst_orig + USIZE_C(16), USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
TruncationDueToDstSpace(void)
{
    /*
     * Request to copy 20 bytes starting at dst_idx=50 into dst of size 60.
     * Only 10 bytes available, so copied_sz should be 10.
     */
    byte  dst[60];
    byte  src[40];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToDstSpace -> ");

    kdi_FillVal(dst, USIZE_C(60), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(40), U8_C(0x40));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(60), &copied_sz, src, USIZE_C(40), USIZE_C(50), USIZE_C(0), USIZE_C(20));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(10));

    /* dst[50..59] should contain src[0..9] */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(dst[USIZE_C(50) + i] == src[i]);
    }

    printf("PASSED\n");
}


void
TruncationDueToSrcSpace(void)
{
    /*
     * Request to copy 20 bytes starting at src_idx=25 from src of size 30.
     * Only 5 bytes available in src, so copied_sz should be 5.
     */
    byte  dst[40];
    byte  src[30];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToSrcSpace -> ");

    kdi_FillVal(dst, USIZE_C(40), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(30), U8_C(0x50));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(40), &copied_sz, src, USIZE_C(30), USIZE_C(0), USIZE_C(25), USIZE_C(20));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(5));

    /* dst[0..4] should contain src[25..29] */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(dst[i] == src[USIZE_C(25) + i]);
    }

    printf("PASSED\n");
}


void
TruncationDueToBothLimits(void)
{
    /*
     * Request 30 bytes, but dst has 10 available and src has 15 available.
     * Should copy min(30, 10, 15) = 10 bytes.
     */
    byte  dst[25];
    byte  src[35];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToBothLimits -> ");

    kdi_FillVal(dst, USIZE_C(25), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(35), U8_C(0x60));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(25), &copied_sz, src, USIZE_C(35), USIZE_C(15), USIZE_C(20), USIZE_C(30));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(10));

    /* dst[15..24] should contain src[20..29] */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(dst[USIZE_C(15) + i] == src[USIZE_C(20) + i]);
    }

    printf("PASSED\n");
}


void
SingleByteCopy(void)
{
    /*
     * Minimal case: copy 1 byte from specific offset to specific offset.
     */
    byte  dst[10];
    byte  src[10];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SingleByteCopy -> ");

    kdi_FillVal(dst, USIZE_C(10), U8_C(0xFF));
    kdi_FillSeq(src, USIZE_C(10), U8_C(0x70));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(10), &copied_sz, src, USIZE_C(10), USIZE_C(5), USIZE_C(3), USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(1));
    assert(dst[5] == src[3]);

    printf("PASSED\n");
}


void
CopyToEndOfDst(void)
{
    /*
     * Copy to the very last byte(s) of destination.
     */
    byte  dst[20];
    byte  src[20];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "CopyToEndOfDst -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(20), U8_C(0x80));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(20), &copied_sz, src, USIZE_C(20), USIZE_C(15), USIZE_C(0), USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(5));

    /* dst[15..19] should contain src[0..4] */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(dst[USIZE_C(15) + i] == src[i]);
    }

    printf("PASSED\n");
}


void
CopyFromEndOfSrc(void)
{
    /*
     * Copy from the very last byte(s) of source.
     */
    byte  dst[20];
    byte  src[20];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "CopyFromEndOfSrc -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(20), U8_C(0x90));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(20), &copied_sz, src, USIZE_C(20), USIZE_C(0), USIZE_C(15), USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(5));

    /* dst[0..4] should contain src[15..19] */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(dst[i] == src[USIZE_C(15) + i]);
    }

    printf("PASSED\n");
}


void
LargeBuffersWithOffsets(void)
{
    /*
     * Large buffers with various offsets.
     */
    byte  dst[256];
    byte  src[256];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffersWithOffsets -> ");

    kdi_FillVal(dst, USIZE_C(256), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(256), U8_C(0x00));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(256), &copied_sz, src, USIZE_C(256), USIZE_C(50), USIZE_C(100), USIZE_C(80));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(80));

    /* dst[50..129] should contain src[100..179] */
    for (i = USIZE_C(0); i < USIZE_C(80); ++i)
    {
        assert(dst[USIZE_C(50) + i] == src[USIZE_C(100) + i]);
    }

    printf("PASSED\n");
}


void
DstOnlyOneByteAvailable(void)
{
    /*
     * Destination has only 1 byte available from dst_idx.
     * Request more, but should copy only 1.
     */
    byte  dst[16];
    byte  src[16];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstOnlyOneByteAvailable -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0xCC));
    kdi_FillSeq(src, USIZE_C(16), U8_C(0xA0));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(16), &copied_sz, src, USIZE_C(16), USIZE_C(15), USIZE_C(0), USIZE_C(10));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(1));
    assert(dst[15] == src[0]);

    printf("PASSED\n");
}


void
SrcOnlyOneByteAvailable(void)
{
    /*
     * Source has only 1 byte available from src_idx.
     * Request more, but should copy only 1.
     */
    byte  dst[16];
    byte  src[16];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SrcOnlyOneByteAvailable -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(16), U8_C(0xB0));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(16), &copied_sz, src, USIZE_C(16), USIZE_C(0), USIZE_C(15), USIZE_C(10));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(1));
    assert(dst[0] == src[15]);

    printf("PASSED\n");
}


void
CopyMiddleToMiddle(void)
{
    /*
     * Copy from middle of source to middle of destination.
     */
    byte  dst[50];
    byte  dst_orig[50];
    byte  src[50];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "CopyMiddleToMiddle -> ");

    kdi_FillVal(dst, USIZE_C(50), U8_C(0x11));
    kdi_FillVal(dst_orig, USIZE_C(50), U8_C(0x11));
    kdi_FillSeq(src, USIZE_C(50), U8_C(0xC0));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(50), &copied_sz, src, USIZE_C(50), USIZE_C(20), USIZE_C(15), USIZE_C(12));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(12));

    /* Head should remain unchanged */
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(20)) == RESULT_SUCCESS);

    /* Middle should contain copied data */
    for (i = USIZE_C(0); i < USIZE_C(12); ++i)
    {
        assert(dst[USIZE_C(20) + i] == src[USIZE_C(15) + i]);
    }

    /* Tail should remain unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(32), dst_orig + USIZE_C(32), USIZE_C(18)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExcessiveByteCountRequest(void)
{
    /*
     * Request very large byte_count that exceeds both dst and src availability.
     * Should copy only what's possible.
     */
    byte  dst[20];
    byte  src[20];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ExcessiveByteCountRequest -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(20), U8_C(0xD0));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyBound(dst, USIZE_C(20), &copied_sz, src, USIZE_C(20), USIZE_C(10), USIZE_C(5), USIZE_C(1000));

    assert(result == RESULT_SUCCESS);
    /* dst has 10 bytes available (20-10), src has 15 bytes available (20-5) */
    /* Should copy min(1000, 10, 15) = 10 */
    assert(copied_sz == USIZE_C(10));

    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(dst[USIZE_C(10) + i] == src[USIZE_C(5) + i]);
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ExactCopyWithinBounds();
    CopyAtStartOfBothBuffers();
    TruncationDueToDstSpace();
    TruncationDueToSrcSpace();
    TruncationDueToBothLimits();
    SingleByteCopy();
    CopyToEndOfDst();
    CopyFromEndOfSrc();
    LargeBuffersWithOffsets();
    DstOnlyOneByteAvailable();
    SrcOnlyOneByteAvailable();
    CopyMiddleToMiddle();
    ExcessiveByteCountRequest();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}