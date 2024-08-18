class Container:
    # Abstract base class (pure virtual in C++)
    
    def __init__(self, size: float):
        self._size = size
        self._capacity = 0
        self.container_code = ""
        self.capacity_code = ""

    def get_size(self) -> float:
        return self._size

    def get_capacity(self) -> float:
        return self._capacity

    def set_container_code(self):
        if self._capacity < 100:
            self.capacity_code = "1"
        elif 100 <= self._capacity < 200:
            self.capacity_code = "2"
        else:
            self.capacity_code = "3"

        # Update container code (e.g., "B3", "C3")
        self.container_code += self.capacity_code

    def get_container_code(self) -> str:
        return self.container_code

    # Abstract method (pure virtual function)
    def set_capacity(self):
        raise NotImplementedError("Must be implemented by subclass")
        #  해당 method에서 반드시 구현하도록 강제


class Box(Container): ## 클래스 상속
    def __init__(self, size: float):
        super().__init__(size)

    def set_capacity(self):
        self._capacity = self._size * 1


class PaperBox(Box):
    def __init__(self, size: float):
        super().__init__(size)
        self.container_code = "PaB"

    def set_capacity(self):
        self._capacity = self._size * 1.3


class PlasticBox(Box):
    def __init__(self, size: float):
        super().__init__(size)
        self.container_code = "PlB"

    def set_capacity(self):
        self._capacity = self._size * 1.1


class Bag(Container):
    def __init__(self, size: float):
        super().__init__(size)
        self.container_code = "B"

    def set_capacity(self):
        self._capacity = self._size * 3


class Carrier(Container):
    def __init__(self, size: float):
        super().__init__(size)
        self.container_code = "C"
        self.aux_vec = []

    def set_capacity(self):
        self._capacity = self._size * 5

    def add_aux(self, aux: Box):
        if len(self.aux_vec) == 2:
            # Auxiliary container is full
            return

        self.aux_vec.append(aux)
        self._capacity += 1.1 * aux.get_capacity()

    def get_aux(self, n: int) -> Box:
        if n > len(self.aux_vec):
            return None
        return self.aux_vec[n - 1]
