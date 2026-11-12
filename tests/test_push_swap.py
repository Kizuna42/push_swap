#!/usr/bin/env python3
"""push_swap の簡易テスト。

- 不正入力で stderr に "Error" を出し、stdout に何も出さないこと
- 正常入力で出力された命令列を適用するとスタック a が昇順になり b が空になること

使い方: python3 tests/test_push_swap.py ./push_swap
"""
import itertools
import random
import subprocess
import sys

OPS = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"}


def run(binary, args):
    return subprocess.run([binary] + args, capture_output=True, text=True,
                          timeout=60)


def apply_ops(nums, ops):
    a, b = list(nums), []
    for op in ops:
        if op not in OPS:
            raise ValueError(f"unknown instruction: {op!r}")
        if op in ("sa", "ss") and len(a) > 1:
            a[0], a[1] = a[1], a[0]
        if op in ("sb", "ss") and len(b) > 1:
            b[0], b[1] = b[1], b[0]
        if op == "pa" and b:
            a.insert(0, b.pop(0))
        if op == "pb" and a:
            b.insert(0, a.pop(0))
        if op in ("ra", "rr") and a:
            a.append(a.pop(0))
        if op in ("rb", "rr") and b:
            b.append(b.pop(0))
        if op in ("rra", "rrr") and a:
            a.insert(0, a.pop())
        if op in ("rrb", "rrr") and b:
            b.insert(0, b.pop())
    return a, b


def check_sort(binary, nums, as_single_arg=False):
    args = [" ".join(map(str, nums))] if as_single_arg else list(map(str, nums))
    res = run(binary, args)
    if res.returncode != 0 or res.stderr:
        return False, f"rc={res.returncode} stderr={res.stderr!r}"
    ops = res.stdout.split()
    try:
        a, b = apply_ops(nums, ops)
    except ValueError as e:
        return False, str(e)
    if a != sorted(nums) or b:
        return False, "not sorted"
    return True, len(ops)


ERROR_CASES = [
    ["1", "2", "a"],
    ["1", "1"],
    ["1", "2", "3", "2"],
    ["0", "-0"],
    ["2147483648"],
    ["-2147483649", "1"],
    ["99999999999"],
    ["-"],
    ["+"],
    ["--1"],
    ["1", ""],
    ["1 2 2"],
    ["1 x 3"],
]

NO_OUTPUT_CASES = [
    [],
    ["42"],
    ["1", "2", "3"],
    ["1 2 3"],
    ["-2147483648", "0", "2147483647"],
]


def main():
    binary = sys.argv[1] if len(sys.argv) > 1 else "./push_swap"
    failures = 0

    for args in ERROR_CASES:
        res = run(binary, args)
        if res.stderr != "Error\n" or res.stdout:
            failures += 1
            print(f"FAIL error case {args}: stdout={res.stdout!r} "
                  f"stderr={res.stderr!r}")

    for args in NO_OUTPUT_CASES:
        res = run(binary, args)
        if res.stdout or res.stderr:
            failures += 1
            print(f"FAIL no-output case {args}: stdout={res.stdout!r} "
                  f"stderr={res.stderr!r}")

    # 3 要素以下は全順列を確認し、3 要素は 3 手以内であること
    for n in (2, 3):
        for perm in itertools.permutations(range(n)):
            ok, info = check_sort(binary, list(perm))
            if not ok or info > 3:
                failures += 1
                print(f"FAIL permutation {perm}: {info}")

    # 4・5 要素は全順列を確認し、課題要件の 12 手以内であること
    for n in (4, 5):
        for perm in itertools.permutations(range(n)):
            ok, info = check_sort(binary, list(perm))
            if not ok or info > 12:
                failures += 1
                print(f"FAIL permutation {perm}: {info}")

    rng = random.Random(42)
    for size, rounds in ((6, 20), (10, 20), (100, 10), (500, 3)):
        worst = 0
        for i in range(rounds):
            nums = rng.sample(range(-2**31, 2**31), size)
            ok, info = check_sort(binary, nums, as_single_arg=(i % 2 == 1))
            if not ok:
                failures += 1
                print(f"FAIL random size={size}: {info}")
            else:
                worst = max(worst, info)
        print(f"size {size:>3}: max {worst} instructions")

    if failures:
        print(f"{failures} test(s) failed")
        return 1
    print("all tests passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
