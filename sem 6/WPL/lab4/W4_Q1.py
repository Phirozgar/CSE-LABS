with open("input.txt") as f1, open("output.txt","w") as f2:
    for line in f1:
        f2.write(line[::-1])