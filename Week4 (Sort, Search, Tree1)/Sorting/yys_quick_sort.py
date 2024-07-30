'''
quick sort
1. 임의의 하나의 요소를 pivot으로 삼는다.
2. 피벗보다 작은 값은 왼쪽, 큰 값은 오른쪽에 배치
3. 나뉜 두 배열에서 각각 새로운 피벗을 만들어서 두개의 배열을 다시 쪼개고, 정렬 -> recursively
4. 더 이상 쪼갤 수 없을 때까지 진행
5. 이후 결합해서 큰 전체 문제를 해결한다.
6. 평균 O(N*logN): 피벗 설정이 매번 정확하게 근사하게, 중간 값을 잡을 때.
7. 최악 O(N^2) : 피벗을 잘못하고 제일 작은 값으로 햇을 때

피벗 설정 방법 : 
1. 첫번째 혹은 맨 마지막 값
2. 중간값(중간에 위치한 값) - 보통 가장 좋은 피벗
3. 무작위 값
'''


def partition(L, p, r):
    pivot = L[p] ## pivot

    ## pivot이 가장 왼쪽인 경우를 설정하고 풀기.

    low = p+1 # pivot 다음 위치부터
    high = r ## high는 전달된 끝지점.

    while(low <= high):
        while(L[low] < pivot): #low가 pivot보다 큰 지점에서 stop
            low+=1
        while(pivot < L[high]): #high가 pivot보다 작은 지점에서 stop
            high -=1

        #둘다 iteration이 멈췄다? 역전이 안되었다? switch
        if (low <= high):
            L[low] , L[high] = L[high], L[low]

    #역전이 되었다면 pivot과 자리교체
    L[p], L[high] = L[high], L[p]
    return high



def quick_sort(L, left, right):
    if (left<right): # 교차하지 않을 때,
        pivot = partition(L, left, right) 
        '''
        pivot위치를 찾아가며 sorting(즉, low가 가리키는 것은  pivot보다 작은 것, high가 가리키는 것은 pivot보다 큰 것.)
        '''
        
        quick_sort(L, left, pivot) #왼쪽 pivoting and sorting
        quick_sort(L, pivot + 1, right) # 오른쪽 pivoting and sorting


    #교차된다면 return

def main():
    L = [3,2,1,5,6,10,0]

    quick_sort(L, 0, len(L) -1)

    print(L)

if __name__ == "__main__":
    main()