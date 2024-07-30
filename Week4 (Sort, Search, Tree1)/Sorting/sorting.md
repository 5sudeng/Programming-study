# Sorting

## Selection sort
- $O(N^2)$
- 최솟값 찾아서 맨 앞 애랑 바꾸기
    - 전체가 정렬될 때까지 정렬되지 않은 애들에 대해 반복

``` C
# define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )

void selection_sort(int list[], int n){
  int i, j, least, temp;

  // 마지막 숫자는 자동으로 정렬되므로 (숫자 개수-1) 만큼 반복
  for(i=0; i < n-1; i++){
    least = i;

    // 최솟값 탐색
    for(j = i+1; j < n; j++){
      if(list[j] < list[least])
        least = j;
    }

    // 최솟값과 맨 앞 애 바꾸기
    if(i != least){
        SWAP(list[i], list[least], temp);
    }
  }
}
```

## Bubble sort
- $O(N^2)$
- 왼쪽부터 두 개씩 비교해서 정렬이 안 되어 있으면 바꾸기 &rarr; 쭉 해서 가장 큰 애가 맨 뒤로 가도록
    - 전체가 정렬될 때까지 정렬되지 않은 애들에 대해 반복

``` C
void bubble_sort(int list[], int n){
  int i, j, temp;

  for(i = n-1; i > 0; i--){
    for(j = 0; j < i; j++){
      // j번째와 j+1번째의 요소가 크기 순이 아니면 교환
      if(list[j]<list[j+1]){
        temp = list[j];
        list[j] = list[j+1];
        list[j+1] = temp;
      }
    }
  }
}
```

## Insertion sort
- $O(N^2)$
- 왼쪽부터 쭉 하나씩, 정렬된 애들 사이에 넣어야 할 곳 찾아서 집어넣기
- Selection sort보다 살짝 느림
- 이미 거의 정렬된 애들에 대해서 할 때 좋음 &rarr; $O(N)$

``` C
void insertion_sort(int list[], int n){
  int i, j, key;

  for(i = 1; i < n; i++){
    key = list[i]; // 현재 삽입될 숫자인 i번째 정수를 key 변수로 복사

    // 현재 정렬된 배열은 i-1까지이므로 i-1번째부터 역순으로 조사
    // 음수가 아닌 j 중에서, key보다 큰 애들을 뒤로 이동
    for(j = i-1; j >= 0 && list[j] > key; j--){
      list[j+1] = list[j];
    }

    list[j+1] = key;
  }
}
```

## Merge sort
- $O(NlogN)$
- 반으로 쪼개서 정렬한 다음에 merge하는 것을 recursively 반복
- Memory complexity: $O(N)$

``` C
# include <stdio.h>
# define MAX_SIZE 8
int sorted[MAX_SIZE] // 추가적인 공간 필요

void merge(int list[], int left, int mid, int right){
  int i, j, k, l;
  i = left; // 정렬된 왼쪽 리스트에 대한 인덱스
  j = mid + 1; // 정렬된 오른쪽 리스트에 대한 인덱스
  k = left; // 정렬될 리스트에 대한 인덱스

  // 분할 정렬된 애들을 합병
  while (i <= mid && j <= right) {
    if(list[i]<=list[j])
      sorted[k++] = list[i++];
    else
      sorted[k++] = list[j++];
  }

  // 남아 있는 값들을 일괄 복사
  if (i > mid) {
    for (l = j; l <= right; l++)
      sorted[k++] = list[l];
  } else {
    for (l = i; l <= mid; l++)
      sorted[k++] = list[l];
  }

  // sorted[](임시 배열)에 있는 애들을 list[]로 옮겨주기
  for (l = left; l <= right; l++) {
    list[l] = sorted[l];
  }
}

void merge_sort(int list[], int left, int right){
  int mid;
  if (left < right) {
    mid = (left+right)/2 // 중간 위치를 계산하여 리스트를 균등 분할 - 분할(Divide)
    merge_sort(list, left, mid); // 앞쪽 부분 리스트 정렬 - 정복(Conquer)
    merge_sort(list, mid+1, right); // 뒤쪽 부분 리스트 정렬 - 정복(Conquer)
    merge(list, left, mid, right); // 정렬된 2개의 부분 배열을 합병 - 결합(Combine)
  }
}
```

## Quick sort
- 평균 $O(NlogN)$, 최악의 경우 $O(N^2)$
- Divide(분할) - Conquer(정복) - Combine(결합) 알고리즘
    - Divide: 하나의 pivot을 기준으로 두 개의 비균등 부분 배열(작은 애들 vs. 큰 애들)로 나누기
    - Conquer: 부분 배열을 정렬 (필요한 경우, Divide - Conquer을 반복)
    - Combine: 정렬된 부분 배열들을 하나의 배열로 합병
- Memory complexity: $O(logN)$

``` C
# include <stdio.h>
# define SWAP(x, y, temp) ( (temp)=(x), (x)=(y), (y)=(temp) )

int partition(int list[], int left, int right){
  int pivot, temp;
  int low, high;

  low = left;
  high = right + 1;
  pivot = list[left]; // 정렬할 리스트의 가장 왼쪽 데이터를 피벗으로 선택 

  // low와 high가 교차할 때까지 반복 (low < high)
  do {
    do {
      low++; // list[low]가 피벗보다 작으면 low를 증가
    } while (low <= right && list[low] < pivot);

    do {
      high--; // list[high]가 피벗보다 크면 high를 감소
    } while (high >= left && list[high] > pivot);

    // 만약 low와 high가 교차하지 않았으면 list[low]를 list[high] 교환
    if (low < high){
      SWAP(list[low], list[high], temp);
    }
  } while (low < high);

  // low와 high가 교차했으면 반복문을 빠져나와 list[left]와 list[high] 교환
  SWAP(list[left], list[high], temp);

  return high; // 피벗의 위치인 high를 반환
}

void quick_sort(int list[], int left, int right){
  // 리스트의 크기가 0이나 1이 아니면
  if (left < right){
    int q = partition(list, left, right); // q: 피벗의 위치 - 분할(Divide)

    quick_sort(list, left, q-1); // (left ~ 피벗 바로 앞) 앞쪽 부분 리스트 정렬 - 정복(Conquer)
    quick_sort(list, q+1, right); // (피벗 바로 뒤 ~ right) 뒤쪽 부분 리스트 정렬 - 정복(Conquer)
  }
}
```

## References
- [text](https://gmlwjd9405.github.io/2018/05/06/algorithm-selection-sort.html)
- [text](https://gmlwjd9405.github.io/2018/05/06/algorithm-bubble-sort.html)
- [text](https://gmlwjd9405.github.io/2018/05/06/algorithm-insertion-sort.html)
- [text](https://gmlwjd9405.github.io/2018/05/08/algorithm-merge-sort.html)
- [text](https://gmlwjd9405.github.io/2018/05/10/algorithm-quick-sort.html)