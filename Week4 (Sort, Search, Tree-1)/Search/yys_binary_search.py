'''
어떤 정렬된 "배열"에서 "어떤 것"을 찾는다.
1. "어떤 것"을 정의해야 한다.
2. 조건에 따라 찾는 범위를 줄여 나간다.
3. 처음에는 양쪽 끝에서 시작, 그리고 그 어떤 것은 찾는 범위 내에서 가장 중간에서 시작.
4. 조건에 따라 찾는 범위를 반으로 줄여 나간다.

time complexity : O(logN)
'''

def binary_search(L: list, v: any) -> int:
    # 찾는 것 : 정렬된 배열 내 v 값.

    start, end = 0, len(L)-1

    while (start <= end): #서로 교차되기 직전까지.
        mid = (start + end) // 2

        if L[mid] ==v : 
            return mid
        
        elif L[mid] <v: #오른쪽에서 찾기
            start = mid +1

        else: # 왼쪽에서 찾기
            end = mid-1
    
    #탈출 시 못찾음.
    return -1


def main():
    # 테스트 케이스 1: 일반적인 경우, 값이 리스트에 있음
    L1 = [1, 3, 5, 7, 9, 11, 13, 15]
    assert binary_search(L1, 7) == 3
    assert binary_search(L1, 1) == 0
    assert binary_search(L1, 15) == 7

    # 테스트 케이스 2: 값이 리스트에 없음
    L2 = [2, 4, 6, 8, 10, 12, 14, 16]
    assert binary_search(L2, 5) == -1
    assert binary_search(L2, 0) == -1
    assert binary_search(L2, 20) == -1

    # 테스트 케이스 3: 빈 리스트
    L3 = []
    assert binary_search(L3, 5) == -1

    # 테스트 케이스 4: 리스트에 하나의 요소만 있음
    L4 = [42]
    assert binary_search(L4, 42) == 0
    assert binary_search(L4, 21) == -1

    # 테스트 케이스 5: 중복된 값이 있는 리스트
    L5 = [1, 2, 2, 2, 3, 4, 5]
    assert binary_search(L5, 2) in [1, 2, 3]  # 여러 인덱스 중 하나면 됨
    assert binary_search(L5, 3) == 4
    assert binary_search(L5, 5) == 6

    print("모든 테스트 케이스 통과!")

if __name__ == "__main__":
    main()