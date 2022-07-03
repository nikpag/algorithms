import os

filename = "bazaar"
for i in range(0, 20):
    os.system(f"./{filename} < test-cases/bazaar/input{i}.txt")
    os.system(f"cat test-cases/bazaar/output{i}.txt")
    print()
