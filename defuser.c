#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count) {
    size_t used = 0;
    for (size_t i = 0; i < count; ++i) {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used) return 1;
        used += (size_t)size;
    }
    return count == 0;
}

int solve_phase_1(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_01 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    uint32_t lo  = (uint32_t)challenge;
    uint32_t hi  = (uint32_t)(challenge >> 32);
    uint32_t mid = (uint32_t)(challenge >> 16);

    uint32_t s0 = (hi + 0xf39b) ^ lo;   // step0
    uint32_t s1 =  (mid ^ 0x5727) + hi * 8;   // step1
    uint32_t s2 =  (s1 - lo) * 5  + 0x55d1;   // step2

    values[0] = s2 ^ s0;
    count = 1;
    return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 6;
    (void)challenge;
    values[0] = (uint32_t)((challenge >> 42) & 0xFFu) + 8u;
    for (uint32_t i = 1; i < 6; ++i) {
    uint32_t part = (uint32_t)((challenge >> (i + 4)) & 0xFu);
    part = part ^ (i + 10);
    values[i] = part + 5u * values[i - 1];
    }
    // TODO: 根据 phase_02 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 2;
    uint32_t index = (uint32_t)challenge & 7u;

    uint32_t x = (uint32_t)(challenge >> 32)^ (uint32_t)(challenge >> 3);

    values[0] = index;
    (void)challenge;
    switch (index) {
    case 0:   // p3_case_2
        values[1] = 3u * x + 0xF344u;
        break;

    case 1:   // p3_case_6
        values[1] = (x ^ 0xCDF3u) + (x >> 1);
        break;

    case 2:   // p3_case_1
        values[1] = 5u * x + 0x49FD4u;
        break;

    case 3:   // p3_case_7
        values[1] = 3u * x + 0x932Eu;
        break;

    case 4:   // p3_case_3
        values[1] = (2u * x) ^ 0x7519u;
        break;

    case 5:   // p3_case_5
        values[1] = 5u * x + 0x4D25Bu;
        break;

    case 6:   // p3_case_0
        values[1] = (x ^ 0x40B5u) + (x >> 2);
        break;

    case 7:   // p3_case_4
        values[1] = (4u * x) ^ 0xEC2Bu;
        break;
}
    // TODO: 根据 phase_03 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}
static uint32_t walk_phase4(uint32_t target,
                           uint32_t low,
                           uint32_t high,
                           uint32_t key) {
    uint32_t mid = low + ((high - low) >> 1);

    if (target == mid) {
        return (mid + 0xB2u) ^ key;
    }

    if (target < mid) {
        uint32_t r = walk_phase4(target, low, mid - 1u, key);
        return (5u * r) ^ (mid + key) ^ 0x1Cu;
    } else {
        uint32_t r = walk_phase4(target, mid + 1u, high, key);
        return (5u * r) ^ (mid + key) ^ 0x03u;
    }
}
int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 1;
    (void)challenge;
uint32_t target = (uint32_t)challenge & 0x7Fu;

    uint32_t key = (uint32_t)(challenge >> 7)
                 ^ (uint32_t)(challenge >> 32);

    values[0] = walk_phase4(target, 0u, 127u, key);

   
    // TODO: 根据 phase_04 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_05 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_06 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap) {
    (void)challenge;
    (void)context;
    (void)out;
    (void)cap;
    // TODO（选做）: 根据 secret_gate、secret_copy 和 secret_phase 的汇编构造完整的第七行，写入 out 后返回 0。
    // 第七行不一定只有整数，可以直接用 snprintf 写入；还没完成时保持返回 1，测试会显示 not attempted。
    return 1;
}
