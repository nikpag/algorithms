import os

for i in range(0, 34):
    print(f"Teleports with input{i}:")
    os.system(f"time ./teleports_binary < test-cases/teleports/input{i}.txt")

    print("Correct:")
    os.system(f"cat test-cases/teleports/output{i}.txt")
    print()
