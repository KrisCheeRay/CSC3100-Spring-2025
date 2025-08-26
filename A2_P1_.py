def get_matrix():
    n, m = map(int, input().split())
    input_matrix = list()
    for k in range(n):
        row_input = list(map(int, input().split()))
        c = row_input[0]
        row = dict()
        for i in range(c):
            j = row_input[2 * i + 1]
            a = row_input[2 * i + 2]
            row[j] = a
        input_matrix.append(row)
    return input_matrix, n, m
def main():
    A, n, m = get_matrix()
    input()
    B, _, _ = get_matrix()
    C = list()
    for i in range(n):
        row_A = A[i]
        row_B = B[i]
        row_C = dict()
        keys_A = list(row_A.keys())
        keys_B = list(row_B.keys())
        i = j = 0
        while i < len(keys_A) or j < len(keys_B):
            if j >= len(keys_B) or (i < len(keys_A) and keys_A[i] < keys_B[j]):
                val = row_A[keys_A[i]]
                if val != 0:
                    row_C[keys_A[i]] = val
                i += 1
            elif i >= len(keys_A) or (j < len(keys_B) and keys_B[j] < keys_A[i]):
                val = row_B[keys_B[j]]
                if val != 0:
                    row_C[keys_B[j]] = val
                j += 1
            else:
                val = row_A[keys_A[i]] + row_B[keys_B[j]]
                if val != 0:
                    row_C[keys_A[i]] = val
                i += 1
                j += 1
        C.append(row_C)
    print(f"{n} {m}")
    for row in C:
        if not row:
            print("0")
        else:
            items = sorted(row.items())
            c = len(items)
            output = [str(c)]
            for j, val in items:
                output.append(str(j))
                output.append(str(val))
            print(" ".join(output))
if __name__ == "__main__":
    main()