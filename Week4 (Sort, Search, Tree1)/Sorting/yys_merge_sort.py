'''
Merge Sort

1. recursion method
2. time complexity : O(N*logN)
3. 항상 반을 나누고 -> LogN, 합치는 순간 정렬한다. ->N
    3-1. 항상 recursively 끝까지 반을 나누다가 나중에 합치기.
4. "이미 정렬된 두 부분집합"을 합친다.

'''


def merge(L, first, mid, last): # 합치면서 정렬
    k = first

    #mid 나뉜 포인트 -> 이제부터 L로 다시 합치면서 정렬할 것임.
    sub1 = L[first:mid +1]
    sub2 = L[mid+1 : last+1]


    i =j =0 #sub array의 처음부터 검사.

    # 두 인덱스를 모두 순회하면서 어느 하나가 끝나기 전까지 순회하면서, 정렬
    while(i<len(sub1) and j< len(sub2)):
        if sub1[i] <=sub2[j]:
            L[k] = sub1[i]
            i+=1

        else:
            L[k] = sub2[j]
            j+=1

        k+=1
    
    #둘 중 남은 부분 처리하기
    if(i<len(sub1)):
        L[k:last+1] = sub1[i:]

    if(j<len(sub2)):
        L[k : last+1] = sub2[j:]


def Mergesort(L, first, last):
    '''
    L: 정렬할 대상
    first: 정렬할 대상의 정렬할 곳의 시작
    last: 정렬할 대상의 정렬할 곳의 마지막
    '''

    if first == last:
        return
    
    else:
        mid = first + ((last -first)//2) ##  mid = (first + last) // 2도 가능하지만 오버플로우를 방지하기 위함.

        #계속 오른쪽 왼쪽 나눠가면서, 작은쪽이 크기가 1에 달할때까지 나누고  그 뒤로 왼쪽부터 merge해 나간다.
        #다 끝나면 오른쪽의 subarray들을 merge
        Mergesort(L, first, mid)
        Mergesort(L, mid+1, last)

        merge(L, first, mid, last)

    
def main():
    L = [2,5,6,8,2,10]

    Mergesort(L, first = 0, last = len(L)-1)
    print(L)

if __name__ == "__main__":
    main()