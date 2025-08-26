#A1_P1_123090007.py

def is_match(org_seq, dna_seq):
    if len(org_seq) != len(dna_seq):
        return "NO"
    
    num_to_char = dict()
    char_to_num = dict()

    for i in range(0,len(org_seq)):
        num = org_seq[i]
        char = dna_seq[i]

        if num in num_to_char:
            if num_to_char[num] != char:
                return "NO"
        else:
            num_to_char[num] = char
        
        if char in char_to_num:
            if char_to_num[char] != num:
                return "NO"
        else:
            char_to_num[char] = num
    
    return "YES"

def main():
    test_cases = int(input())

    for j in range(0,test_cases):
        org_seq_len = int(input())

        org_seq = list(map(int, input().split()))

        total_dna_seq = int(input())

        for k in range(0,total_dna_seq):
            dna_seq = input().strip()

            result = is_match(org_seq, dna_seq)
            print(result)

if __name__ == "__main__":
    main()  







        

