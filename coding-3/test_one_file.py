import os
import sys
import filecmp

file_name = sys.argv[1]
file_name_no_ext = file_name[0:-2] if file_name[-1] == "c" else file_name[0:-4]

(file_range, folder_name) = (range(1, 21), "roadtrip") if file_name[0:len("roadtrip")] == "roadtrip" else (range(0, 21), "traintrips")

right = 0
wrong = 0

for i in file_range:
    input_file = f"test-cases/{folder_name}/input{i}.txt"
    output_file = "dummy.txt"
    correct_output = f"test-cases/{folder_name}/output{i}.txt"
    os.system(f"time ./{file_name_no_ext} < {input_file} > {output_file}")

    if filecmp.cmp(output_file, correct_output):
        right += 1
    else:
        wrong += 1

print(f"{right} right, {wrong} wrong")
