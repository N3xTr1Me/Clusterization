from numpy import random as rng
import numpy as np

from typing import Dict


class Epsilon:

    """
    Ограничения для свдига точек вдоль координатных осей (шаги по индексу элемента).
    """

    def __init__(self, min_step: int = 1, max_step: int = 2) -> None:

        """
        Задается минимальным и максимлальным размером шага
        """

        if min_step == 0:
            min_step = 1

        # Задается интервал от значения обратного максимальному до максимального с шагом между значениями
        # равному минимальному размеру шага.
        self._interval = np.arange(
            -max_step,
            max_step + min_step,
            step=min_step
        )

    def to_dict(self) -> Dict[str, int]:
        return {
            "min_step": self._interval[0],
            "max_step": self._interval[-1]
        }

    def __call__(self) -> int:
        """
        operator() из C++

        :return: Случайное значение из интервала шагов
        """

        return rng.choice(self._interval)
