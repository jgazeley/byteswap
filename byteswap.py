from sys import argv
from ntpath import exists, getsize, realpath
from shutil import copy2

def byteswap(file):

    copy = realpath(file) + '.bak'
    existing = exists(copy)
    while existing:
        copy += '.bak'
        existing = exists(copy)
    copy2(file, copy)

    #input file, output file, file size
    f = open(file, "r+b")
    fsize = getsize(file)

    #check that file size is divisible by 4
    if fsize % 4 != 0:
        print("Invalid file size!")

    #read 4 bytes at a time from the file, then rewrite the 4 bytes in reverse
    else:
        x = 0
        while x < fsize:
            f.seek(x)
            data = [int.from_bytes(f.read(1), "big"), int.from_bytes(f.read(1), "big"), int.from_bytes(f.read(1), "big"), int.from_bytes(f.read(1), "big")]
            data = data[::-1]
            f.seek(x)
            f.write(bytes(data))
            x += 4

    f.close()

byteswap(argv[1])
