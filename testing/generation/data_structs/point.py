from dataclasses import dataclass

from typing import Any, Dict, Tuple

@dataclass(repr=True)
class Point:

    """
    Представление точки. Подразумевается, что это и есть сигнал
    """

    x_index: int            # индексы нужен для генерации последующих соседних точек
    x_value: float | int    # Непосредственно значение координаты по оси X т.е. расстояни

    y_index: int
    y_value: int            # Значение координаты по оси Y, т.е. номер измерения.

    def __getitem__(self, item: str) -> float | int:
        """
        Местный operator[]

        :param item: имя поля объекта
        :return: значение соответствующего поля
        """
        return self.__dict__[item]

    def to_dict(self) -> Dict[str, float| int]:
        """
        Необходим для сохранения тестов в .json

        :return: Репрезентация объекта в виде словаря
        """
        return {
            "x_index": int(self.x_index),
            "x_value": float(self.x_value),
            "y_index": int(self.y_index),
            "y_value": float(self.y_value)
        }


def make_point(x: Tuple[int, float | int],
               y: Tuple[int, int],
               **kwargs: Any
                ) -> Point:

    """
    Функция-фабрика для создания точек

    :param x: Пара из индекса и значения x
    :param y: Пара из индекса и значения y
    :param kwargs: Любые другие именованные аргументы
    :return:
    """

    return Point(x[0], x[1], y[0], y[1])
