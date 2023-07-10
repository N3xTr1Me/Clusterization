from copy import deepcopy

from typing import Any, Dict, List, Set


class Config:

    """
    Конфигурация сессии генерации тестов. Содержит общую информацию для всех тестов.
    """

    __requirements = {
        "axis": {"min_value", "max_value", "step_size"},
        "epsilons": {"x", "y"}
    }

    def __init__(self) -> None:

        """
        Конкретно, ограничения значений по осям и количество целей в тесте.
        """

        self.x_axis = {
            "min_value": 1,
            "max_value": 4000,
            "step_size": 1
        }

        self.y_axis = {
            "min_value": 1,
            "max_value": 36,
            "step_size": 1
        }

        self.epsilons = {
            "x": [1, 2],
            "y": [1, 2]
        }

        self.n_points: List[int] = [4, 5, 6, 7, 8]
        self.n_targets: int = 4

    @classmethod
    def create(cls, data: Dict[str, Any]) -> "Config":
        base = Config()

        return base.clone(**data)

    def get_requirements(self) -> Dict[str, Set]:

        """
        Вспомогательный метод, помогающий проверить,
        что при клонировании конфига мы не потеряли атрибуты ограничителей.

        :return: Словарь с требованиями к аргументам ограничителей.
        """

        return self.__requirements

    def _check_requirements(self, key: str, value: Dict[str, float | int] | int) -> bool:

        """
        Непосредственно проверка атрибутов на соответствие требованиям.

        :param key:     Название атрибута.
        :param value:   его значение.
        :return:        Результат проверки.
        """

        for requirement in self.__requirements:

            if key.find(requirement):

                if set(value.keys()) == self.__requirements[requirement]:
                    return True

                return False

        return True

    def __setitem__(self, key: str, value: Dict[str, float | int] | int) -> None:

        """
        Служебный метод задания атрибута.

        :param key:     Имя атрибута
        :param value:   Его значение
        :return:        None
        """

        if not self._check_requirements(key, value):
            raise ValueError("Minimal requirements were not met!")

        self.__dict__[key] = value

    def clone(self, **kwargs: Dict[str, float | int] | int) -> "Config":

        """
        Метод для копирования конфигурации с изменениями.

        :param kwargs: Новые значения атрибутов
        :return:       объект Config
        """

        new_config = deepcopy(self)

        for arg in kwargs:
            new_config[arg] = kwargs[arg]

        return new_config
