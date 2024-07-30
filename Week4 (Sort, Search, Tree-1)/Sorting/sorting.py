#selection sort
#뒤에서 하나 선택해서 갖고오기
#O(N^2)
def find_min(L:list, start_idx: int) -> int:
    smallest = start_idx
    for i in range(start_idx+1, len(L)):
        if L[i] < L[smallest]:
            smallest = i
    return smallest

def selection_sort(L:list) -> None:
    for i in range(len(L)):
        smallest = i
        for j in range(i+1, len(L)):
            if L[j] < L[smallest]:
                smallest = j
        L[i], L[smallest] = L[smallest], L[i]


#insertion sort
#O(N^2)
#근데 거의 sorting되어있다면 O(kN)
def insertion_sort(L:list) -> None:
    for i in range(1, len(L)):
        for j in range(i, 0, -1):
            if L[j-1] > L[j]:
                L[j-1], L[j] = L[j], L[j-1]
            else:
                break



#merge sort
#O(NlogN)
def merge(L:list, first:int, mid:int, last:int) -> None:
    k = first
    sub1 = L[first:mid+1]
    sub2 = L[mid+1:last+1]
    i = j = 0
    while i < len(sub1) and j < len(sub2):
        if sub1[i] <= sub2[j]:
            L[k] = sub1[i]
            i = i+1
        else:
            L[k] = sub2[j]
            j = j+1
        k = k+1

    if i<len(sub1):
        L[k:last+1] = sub1[i:]
    elif j < len(sub2):
        L[k:last+1] = sub2[j:]

def mergeSortHelp(L:list, first:int, last:int) -> None:
    if first == last:
        return
    else:
        mid = first + (last-first)//2
        mergeSortHelp(L, first, mid)
        mergeSortHelp(L, mid+1, last)
        merge(L, first, mid, last)

def mergeSort(L:list) -> None:
    mergeSortHelp(L, 0, len(L)-1)



#quick sort
#pivot 값 정해서 그걸 기준으로 분할하고 swap하기
#O(NlogN)
def quick_sort(L:list, start:int, end:int) -> None:
    if start >= end:
        return
    #pivot 초기값은 첫 번째 요소
    pivot = start
    left = start+1
    right = end

    while left<=right:
        #pivot보다 큰 데이터를 찾을때까지 반복
        while left <= end and L[left] <=L[pivot]:
            left+=1
        
        #pivot보다 작은 데이터를 찾을때까지 반복
        while right>start and L[right] >= L[pivot]:
            right -=1
   
        if left>right: #엇갈렸다면 작은 right -=1 데이터와 피봇을 교체 
            L[right], L[pivot] = L[pivot], L[right]
        else: #엇갈리지 않았다면 작은 데이터와 큰 데이터 교체
            L[left], L[right] = L[right], L[left]
    
    #분할 이후 왼쪽 부분과 오른쪽 부분에서 각각 정렬 수행
    quick_sort(L, start, right-1)
    quick_sort(L, right+1, end)

#quick_sort(L, 0, len(L)-1)
