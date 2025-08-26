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
def multiply_matrices(A, B, n_A, m_A, n_B, m_B):
    C = list()  
    B_col = [set(row.keys()) for row in B]  
    for i in range(n_A):
        row_C = dict()  
        for k in A[i].keys():
            for j in B_col[k]:
                sum_of_matrix = A[i][k] * B[k][j]  
                if j not in row_C:
                    row_C[j] = sum_of_matrix
                else:
                    row_C[j] += sum_of_matrix
        row_C = {k: v for k, v in row_C.items() if v != 0}
        C.append(row_C)
    return C
def print_matrix(C, n, m):
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
def main():
    A, n_A, m_A = get_matrix()
    input()
    B, n_B, m_B = get_matrix()
    C = multiply_matrices(A, B, n_A, m_B, n_B, m_B)
    print_matrix(C, n_A, m_B)
if __name__ == "__main__":
    main()