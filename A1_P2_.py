#A1_P2_123090007
def handle_level(blocks, a):

    blocks = [str(block) for block in blocks]

    a_block = blocks[a]
    remaining_blocks = blocks[:a] + blocks[a+1:]
    remaining_blocks.sort(reverse = True, key = lambda x: (x * 14)[:14])

    result = a_block + ''.join(remaining_blocks)

    return result

def main():
    k, t = map(int, input().split())
    results = list()

    for _ in range(0,t):
        n_and_blocks = input().split()
        n = int(n_and_blocks[0])
        blocks = n_and_blocks[1:n+1]
        a = int(n_and_blocks[n+1]) - 1

        result = handle_level(blocks, a)
        results.append(result)
    
    for result in results:
        print(result)

if __name__ == "__main__":
    main()








