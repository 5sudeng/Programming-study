'''
insertion sort

insert the leftmost item of the unsorted list to the proper location of the sorted list

왼쪽 : 정렬된 배열
오른쪽 : 정렬되지 않은 배열
오른쪽의 가장 왼쪽 값을 왼쪽에서 적절한 곳으로 insert한다.

time complexity : O(N^2)
거의 모두 다 sorted 되어 있다면, 불필요한 순회가 있는 selection sort보다는 빠르다.

'''

def insert(L: list, last_idx : int)-> None:

    #last idx : 정렬되지 않은 곳에서 가져온 leftmost 값
    for i in range(last_idx, 0, -1): # 왼쪽으로 순회, 0이전까지
        if L[i-1] > L[i] :
            #swap
            L[i-1], L[i] = L[i] , L[i-1]

        else:
            break # 이미 앞부분은 정렬이 되어 있으므로, if문에 걸리지 않았다면 제자리를 찾은 것.


def insert_sort(L:list) -> None:
    for i in range(1, len(L)):
        ## 0번째는 이미 sorted 된 것이라고 생각하는 것. 시작점임.

        insert(L, i)




def main():
    # 테스트 케이스 1: 일반적인 경우
    L1 = [64, 25, 12, 22, 11]
    insert_sort(L1)
    assert L1 == [11, 12, 22, 25, 64]

    # 테스트 케이스 2: 이미 정렬된 리스트
    L2 = [1, 2, 3, 4, 5]
    insert_sort(L2)
    assert L2 == [1, 2, 3, 4, 5]

    # 테스트 케이스 3: 역순으로 정렬된 리스트
    L3 = [5, 4, 3, 2, 1]
    insert_sort(L3)
    assert L3 == [1, 2, 3, 4, 5]

    # 테스트 케이스 4: 중복된 값이 있는 리스트
    L4 = [3, 1, 2, 3, 1, 2]
    insert_sort(L4)
    assert L4 == [1, 1, 2, 2, 3, 3]

    # 테스트 케이스 5: 빈 리스트
    L5 = []
    insert_sort(L5)
    assert L5 == []

    # 테스트 케이스 6: 하나의 요소만 있는 리스트
    L6 = [42]
    insert_sort(L6)
    assert L6 == [42]

    print("모든 테스트 케이스 통과!")





if __name__ == "__main__":
    main()