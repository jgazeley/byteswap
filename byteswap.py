wfin = open("save.sra", "rb")
fout = open("output.bin", "wb")
data_in = fin.read()
fsize = len(data_in)
fin.close()

if fsize % 4 != 0:
    print("Invalid file size!")
    fout.close()

else:
    fin = open("save.sra", "rb")

    for x in range(1, (fsize // 4) + 1):
        data_in = [fin.read(1), fin.read(1), fin.read(1), fin.read(1)]
        data_out = data_in[3] + data_in[2] + data_in[1] + data_in[0]
        fout.write(data_out)