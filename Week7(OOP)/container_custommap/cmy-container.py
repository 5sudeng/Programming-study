class Container:
    def __init__(self, size):
        self._size = size
        self.capacity = 0
        self.container_type = ""
        self.capacity_code = ""

    def get_size(self):
        return self._size
    def set_capacity(self):
        pass
    def get_capacity(self):
        return self.capacity
    def set_container_code(self):
        if self.capacity < 100:
            self.capacity_code = "1"
        elif self.capacity < 200:
            self.capacity_code = "2"
        else:
            self.capacity_code = "3"
        self.container_code = self.container_type + self.capacity_code
    def get_container_code(self):
        return self.container_code

class Box(Container):
    def __init__(self, size):
        super().__init__(size)
    def set_capacity(self):
        self.capacity = self._size * 1

class PaperBox(Box):
    def __init__(self, size):
        super().__init__(size)
        self.container_type = "PaB"
    def set_capacity(self):
        self.capacity = self._size * 1.3

class PlasticBox(Box):
    def __init__(self, size):
        super().__init__(size)
        self.container_type = "PlB"
    def set_capacity(self):
        self.capacity = self._size * 1.1

class Bag(Container):
    def __init__(self, size):
        super().__init__(size)
        self.container_type = "B"
    def set_capacity(self):
        self.capacity = self._size * 3

class Carrier(Container):
    def __init__(self, size):
        super().__init__(size)
        self.container_type = "C"
        self.aux1 = None
        self.aux2 = None
    def set_capacity(self):
        self.capacity = self._size * 5
    def add_aux(self, aux):
        if not self.aux1:
            self.aux1 = aux
            self.capacity += aux.get_capacity() * 1.1
        elif not self.aux2:
            self.aux2 = aux
            self.capacity += aux.get_capacity() * 1.1
        else:
            pass
    def get_aux(self, n):
        if n==1 and self.aux1:
            return self.aux1
        elif n==2 and self.aux2:
            return self.aux2
        else:
            return None


def Episode1():
    print("Episode 1:")
    alloc_weight = 0

    carrier1 = Carrier(100)
    carrier1.set_capacity()

    carrier_size = carrier1.get_size()

    bag1 = Bag(50)
    bag1.set_capacity()

    box1 = Box(10)

    pap_box1 = PaperBox(10)
    pap_box1.set_capacity()
    pap_box2 = PaperBox(10)
    pap_box2.set_capacity()

    plas_box1 = PlasticBox(10)
    plas_box1.set_capacity()
    plas_box2 = PlasticBox(10)
    plas_box2.set_capacity()

    carrier1.add_aux(plas_box1)
    carrier1.add_aux(plas_box2)

    aux_box = carrier1.get_aux(1)

    alloc_weight += carrier1.get_capacity()
    alloc_weight += bag1.get_capacity()
    alloc_weight += pap_box1.get_capacity()
    alloc_weight += pap_box2.get_capacity()

    carrier1.set_container_code()
    bag1.set_container_code()
    pap_box1.set_container_code()
    plas_box1.set_container_code()

    code = carrier1.get_container_code()

    print(f"Total capacity: {alloc_weight}")
    del carrier1  # Equivalent to delete in C++


def Episode2():
    print("Episode 2:")
    alloc_weight = 0

    carrier1 = Carrier(150)
    carrier1.set_capacity()

    carrier_size = carrier1.get_size()

    bag1 = Bag(30)
    bag1.set_capacity()
    box1 = Box(10)

    pap_box1 = PaperBox(20)
    pap_box1.set_capacity()
    pap_box2 = PaperBox(20)
    pap_box2.set_capacity()
    plas_box1 = PlasticBox(10)
    plas_box1.set_capacity()

    carrier1.add_aux(plas_box1)

    alloc_weight += carrier1.get_capacity()
    alloc_weight += bag1.get_capacity()
    alloc_weight += pap_box1.get_capacity()
    alloc_weight += pap_box2.get_capacity()

    carrier1.set_container_code()
    bag1.set_container_code()
    pap_box1.set_container_code()
    plas_box1.set_container_code()

    code = carrier1.get_container_code()

    print(f"Total capacity: {alloc_weight}")
    del carrier1  # Equivalent to delete in C++


def main():
    Episode1()
    print()
    Episode2()


if __name__ == "__main__":
    main()