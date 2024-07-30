'''
selection sorting

- unsorted list에서 최소값을 찾아서, 정렬되지 않은 array에서 가장 왼쪽과 위치를 바꾼다.
- find minimum
- swap

time complexity : O(N^2)

'''

def find_min(L: list, start_idx: int)-> int: ## index 반환

    smallest_idx = start_idx
    
    for i in range(start_idx, len(L)):
        if L[i] < L[smallest_idx]:
            smallest_idx = i

    return smallest_idx


def selection_sort(L: list) -> None:

    for i in range(len(L)):
        smallest_idx = find_min(L, i)

        L[i], L[smallest_idx] = L[smallest_idx], L[i] ## swap



def main():
    # 테스트 케이스 1: 일반적인 경우
    L1 = [64, 25, 12, 22, 11]
    selection_sort(L1)
    assert L1 == [11, 12, 22, 25, 64]

    # 테스트 케이스 2: 이미 정렬된 리스트
    L2 = [1, 2, 3, 4, 5]
    selection_sort(L2)
    assert L2 == [1, 2, 3, 4, 5]

    # 테스트 케이스 3: 역순으로 정렬된 리스트
    L3 = [5, 4, 3, 2, 1]
    selection_sort(L3)
    assert L3 == [1, 2, 3, 4, 5]

    # 테스트 케이스 4: 중복된 값이 있는 리스트
    L4 = [3, 1, 2, 3, 1, 2]
    selection_sort(L4)
    assert L4 == [1, 1, 2, 2, 3, 3]

    # 테스트 케이스 5: 빈 리스트
    L5 = []
    selection_sort(L5)
    assert L5 == []

    # 테스트 케이스 6: 하나의 요소만 있는 리스트
    L6 = [42]
    selection_sort(L6)
    assert L6 == [42]

    print("모든 테스트 케이스 통과!")

if __name__ == "__main__":
    main()