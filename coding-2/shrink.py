#!/usr/bin/env python3

import random
import subprocess

corr_name = "outputter.py"
wrong_name = "salaries"


def shrink(source, target):
    with open(source, "rt") as f:
        N, K = map(int, f.readline().split())
        print(f"N = {N}, K = {K}")
        A = list(map(int, f.readline().split()))
        print(f"A = {A}")

    def save(B):
        with open(target, "wt") as f:
            print(len(B), K, file=f)
            print(*B, file=f)

    def correct(B):
        # print("Inside correct")
        save(B)
        # print("Finished save")
        # print(f"source = {source}")
        expected = int(subprocess.check_output([f"./{corr_name}", source]))
        # print("Got expected")
        stdin = open(source, "rb")
        given = int(subprocess.check_output([f"./{wrong_name}"], stdin=stdin))
        # print("Got given")
        return expected == given
    print("Starting from N =", N)
    more = True

    def test(B):
        # print("Inside test")
        nonlocal A, more
        if correct(B):
            return False
        print("... down to N =", len(B))
        A = B
        more = True
        return True

    # i = 1
    while more:
        # print(f"i = {i}")
        # i += 1
        more = False
        # j = 1
        for k in range(1, len(A)):
            # print(f"j = {j}")
            # j += 1
            B = random.sample(A, k)
            print(f"B = {B}")
            if test(B):
                break
    save(A)


if __name__ == "__main__":
    import sys
    shrink(sys.argv[1], sys.argv[2])
