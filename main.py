def print_matrix(high, arr):
    for index_print in range(high):
        print(arr[index_print])
    print()
    return


def ref_matrix(high, len, arr):
    for index_x in range(high):
        for index_y in range(len):
            if arr[index_x][index_y] == ".":
                arr[index_x][index_y] = int(0)
            elif arr[index_x][index_y] == "#":
                arr[index_x][index_y] = int(-1)
            else:
                stupid_warning()
    return


def stupid_warning():
    print("ERROR")
    print("Ah shit, here we go again!")
    print("Are U dumb, stupid or dumb, huh! ©6IX9INE")
    exit(1)
    return


def undo_matrix(high, len, arr):
    for index_x in range(high):
        for index_y in range(len):
            if arr[index_x][index_y] == -1:
                arr[index_x][index_y] = "#"
            if arr[index_x][index_y] == -2:
                arr[index_x][index_y] = "*"
    return


def show_your_way(ix, iy, arr):
    prime = arr[ix - 1][iy - 1]
    arr[ix - 1][iy - 1] = -2
    i = 1
    j = 1
    arr[ix - i][iy - j] = -2
    while prime != 1:
        if ix - i - 1 >= 0 and arr[ix - i - 1][iy - j] == prime - 1:
            arr[ix - i - 1][iy - j] = -2
            i += 1
        elif ix - i + 1 < ix and arr[ix - i + 1][iy - j] == prime - 1:
            arr[ix - i + 1][iy - j] = -2
            i -= 1
        elif iy - j + 1 < iy and arr[ix - i][iy - j + 1] == prime - 1:
            arr[ix - i][iy - j + 1] = -2
            j -=1
        elif iy - j - 1 >= 0 and arr[ix - i][iy - j - 1] == prime - 1:
            arr[ix - i][iy - j - 1] = -2
            j += 1
        prime -= 1

    for il in range(ix):
        for ip in range(iy):
            if arr[il][ip] > 0:
                arr[il][ip] = "."
    undo_matrix(x, y, matrix)
    print_matrix(x, matrix)
    return


def search_way(arr, high, len):
    arr[0][0] = 1
    for step in range(1, high * len):
        for ix in range(high):
            for iy in range(len):
                if arr[ix][iy] == step:
                    if ix - 1 >= 0 and arr[ix - 1][iy] == 0:
                        arr[ix - 1][iy] = step + 1
                    if ix + 1 < high and arr[ix + 1][iy] == 0:
                        arr[ix + 1][iy] = step + 1
                    if iy + 1 < len and arr[ix][iy + 1] == 0:
                        arr[ix][iy + 1] = step + 1
                    if iy - 1 >= 0 and arr[ix][iy - 1] == 0:
                        arr[ix][iy - 1] = step + 1
    print_matrix(high, arr)
    check_way(x, y, matrix)
    return


def check_way(ix, iy, arr):
    if arr[ix - 1][iy - 1] > 0:
        print("Easy-peasy, lemon squeezy!")
        print("Shortest way takes: ", arr[ix - 1][iy - 1])
        print()
    else:
        print("ERROR")
        print("Ah shit, here we go again!")
        print("No way!!! Dude... No way!!!")
        exit(1)
    return


with open("task1.txt", "r") as f:
    x, y = next(f).split()
    x = int(x)
    y = int(y)
    print(x, y)
    print()
    matrix = []
    for i in range(x):
        matrix.append([-9] * y)
    for index, line in enumerate(f):
        if y != len(line.rstrip('\r\n')):
            print("Incorrect matrix")
            stupid_warning()
        matrix[index] = list(line.rstrip('\r\n'))
    print_matrix(x, matrix)
    ref_matrix(x, y, matrix)
    print_matrix(x, matrix)
    search_way(matrix, x, y)
    show_your_way(x, y, matrix)

