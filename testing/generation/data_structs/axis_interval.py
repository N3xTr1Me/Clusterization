from typing import Any, Dict, Tuple

from numpy import random as rng
import numpy as np


class AxisInterval:

    def __init__(self,
                 min_value: float | int,
                 max_value: float | int,
                 step_size: float | int
                 ) -> None:

        """
        Отрезок значений в пределах которых может изменяться координата на соответствующей координатной прямой.

        :param min_value: Минимальное значение координат, чаще всего будет 0, но мало ли.
        :param max_value: Максимум по оси.
        :param step_size: Шаг с на который должны отличаться значения в интервале.
        """

        # Шаг может быть и с плавающей точкой (для оси X)
        self._step_size = step_size

        # Буквально массив значений от минимального до максимального с заданным шагом.
        self._interval = np.arange(min_value,
                                   max_value + step_size - 1,
                                   step=step_size,
                                  )

        # Впоследствии нужно будет искать индекс по элементу, что не поддерживается numpy.array
        # Поэтому сохраняем местный enumerate от массива значений интервала.
        self._indices = list(
            map(lambda x: x[0], enumerate(self._interval))
        )

    def __getitem__(self, item: int) -> float | int:

        return self._interval[item]

    def __len__(self) -> int:
        """
        Местный std::size()

        :return: Размер интервала значений.
        """
        return len(self._interval)

    def random_index(self) -> int:
        """
        Выбираем случайный индекс элемента в интервале.
        """
        return rng.choice(self._indices)

    def random(self) -> Tuple[int, float | int]:
        """
        Получив случайны индекс, возвращаем кортеж из него и значения по индексу.
        """
        index = self.random_index()

        # инициализация кортежа не нужна, питон делает это автоматически
        return index, self._interval[index]

    def get_step(self) -> float | int:

        """
        Возвращаем размер щага на интервале.
        """

        return self._step_size

    def to_dict(self) -> Dict[str, Any]:

        """
        Нужен для сохранения в .json

        :return: Представление объекта в виде словаря (хеш-мапы)
        """

        return {
            "min_value": float(self._interval[0]),
            "max_value": float(self._interval[-1]),
            "step_size": float(self._step_size)
        }
