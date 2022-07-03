import os

for i in range(1, 26):
    print(f"salaries {i}:")
    os.system(f"time ./salaries < test-cases/salaries/input{i}.txt")
    os.system(f"cat test-cases/salaries/output{i}.txt")
    print()
