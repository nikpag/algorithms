import os

files = ["roadtrip.cpp", "traintrips.cpp"]

for file in files:
    print(F"TESTING {file}")
    os.system(f"python3 test_one_file.py {file}")
