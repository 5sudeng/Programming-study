'''
def main():
    rbt = RBT()
    
    # 노드 삽입 테스트
    elements = [20, 15, 25, 10, 5, 1, 30, 35, 40]
    for el in elements:
        rbt.insert(el)

    print("Red-Black Tree 구조 (삽입 후):")
    rbt.print_tree()

    # 노드 삭제 테스트
    node_to_delete = rbt.search(rbt.root, 15)
    if node_to_delete != rbt.Tnil:
        rbt.delete(node_to_delete)
        print("\nRed-Black Tree 구조 (노드 15 삭제 후):")
        rbt.print_tree()
    else:
        print("노드 15를 찾을 수 없음.")

if __name__ == "__main__":
    main()
'''