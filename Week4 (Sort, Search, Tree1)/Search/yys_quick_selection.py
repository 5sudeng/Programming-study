'''
Quick Selection
**
1. 리스트를 정렬하지 않고, K번째 작은 수를 알고 싶을 때 사용.
2. pivot하나 골라서 값을 비교 -> 작은 리스트와 큰 리스트로 나눈다.
3. K번째 숫자가 속해있는 리스트만 가지고 다시 재귀적으로 반복
4. median 값을 찾을 때도 활용 가능. 


quick sort은 index를 순환하면서 "정렬"을 위해 switching을 하지만
여기서는 작고 큰 것들을 따로 보관한다.

**kth element : 오름차순 정렬일 때, k번째 수(1-indexed)
'''


def quick_selection(arr, kth):
    if len(arr) ==1:
        return arr[0] # 재귀 종료 시점.

    pivot = arr[len(arr)//2] ## pivot 위치 mid로 설정

    left, mid, right = [], [], []

    for i in range(len(arr)): # 전체를 순환하면서 pitvot기준으로 왼쪽 오른쪽 나누기.
        
        if arr[i] < pivot:
            left.append(arr[i]) # 작은 쪽에 합류
        
        elif arr[i] > pivot:
            right.append(arr[i]) # 큰 쪽에 합류
        else: 
            mid.append(arr[i]) # 같은 경우

    if kth <=len(left): # 찾아야 하는 K번째 작은 값이 있을 만한 곳에서 한번 더
        return quick_selection(left, kth)
    
    elif kth<=len(left) + len(mid):
        
        # len(left) < kth < len(left) +len(mid)인 경우, mid안에는 무조건 같은 숫자들만 들어가 있어서 아무거나 가져온다.
        return mid[0]
    else: 
        #kth >= len(left) + len(mid)
        #큰쪽에서 다시 찾기
        # 이때는 kth - len(left) -len(mid) 만큼의 순위만 찾으면 됨.
        return quick_selection(right, kth - len(left) -len(mid) )

'''
여기서 만약 k번째 수가 "kth largest라면"
즉 내림차순일 때 kth
혹은 오름차수일 때 뒤에서 kth
'''

def quick_selection_reverse(arr, kth):
    if len(arr) ==1:
        return arr[0] # 재귀 종료 시점.

    pivot = arr[len(arr)//2] ## pivot 위치 mid로 설정

    left, mid, right = [], [], []

    for i in range(len(arr)): # 전체를 순환하면서 pitvot기준으로 왼쪽 오른쪽 나누기.
        
        if arr[i] < pivot:
            left.append(arr[i]) # 작은 쪽에 합류
        
        elif arr[i] > pivot:
            right.append(arr[i]) # 큰 쪽에 합류
        else: 
            mid.append(arr[i]) # 같은 경우


    '''
    kth largest 라면 적은 k는 큰 쪽에서 먼저 개수 체크
    '''
    if kth <=len(right): 
        return quick_selection_reverse(right, kth)
    
    elif kth<=len(right) + len(mid):

        return mid[0]
    else: 
        #kth >= len(left) + len(mid)
       
        return quick_selection_reverse(left, kth - len(right) -len(mid))







def main():
    arr = [3, 1, 4, 1, 5, 9, 2, 6, 5]
    print("arr : ", arr)
    sorted_arry = sorted(arr)
    print("sorted arr : ", sorted_arry)
    ans = quick_selection(arr, 4)
    print("Ans : ", ans)  #3

    ans2 = quick_selection_reverse(arr, 4)
    print("Ans2 : ", ans2)




if __name__ == "__main__":
    main()
    

        

        