import os

for i in range(1, 26):
    print(f"Shops2 with input{i}:")
    os.system(f"time ./shops2 < test-cases/shops2/input{i}.txt")

    print("Correct:")
    os.system(f"cat test-cases/shops2/output{i}.txt")
    print()
