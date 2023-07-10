from typing import Any, Dict, List

from data_structs import Config, Point


class Solution:

    def __init__(self,
                 id_num: int,
                 config: Config
                 ) -> None:

        """
        Непосредственно тест, со всеми данными для воспроизведения.

        :param id_num: Уникальный идентификатор, используется в имени файла .json
        :param x: Ограничитель по оси X
        :param y: Ограничительн по оси Y
        :param n_targets: Количество целей в тесте
        """

        self.__id = id_num

        self.x_axis = config.x_axis
        self.y_axis = config.y_axis

        self.x_epsilon = config.epsilons["x"]
        self.y_epsilon = config.epsilons["y"]

        self.number_of_targets = config.n_targets
        self.number_of_points = config.n_points

        self.targets: List[List[Point]] = []

    @classmethod
    def create_from_json(cls, solution_id: int, json_data: Dict[str, Any]) -> "Solution":

        """
        Создание объекта Solution из данных, считанных из json-файла.

        :param solution_id: Идентификатор теста
        :param json_data:   непосредственно данные
        :return:            объект Solution
        """

        targets = json_data.pop("targets")

        instance = cls(
                solution_id,
                Config.create(json_data)
        )

        instance.targets = targets

        return instance

    def __len__(self) -> int:
        return len(self.targets)

    def __getitem__(self, item: int) -> List[Point]:

        return self.targets[item]

    def get_id(self) -> int:
        """
        Возвращаем идентификатор теста.
        """

        return self.__id

    def to_dict(self) -> Dict[str, Any]:

        """
        Сохранение в .json
        """

        return {
            "x_axis": self.x_axis,
            "y_axis": self.y_axis,
            "epsilons": {"x": self.x_epsilon, "y": self.y_epsilon},
            "n_targets": self.number_of_targets,
            "n_points": self.number_of_points,
            "targets": [
                [p.to_dict() for p in target] for target in self.targets
            ]
        }


class SolutionFactory:

    """
    Класс для сериализации тестов (в виде объектов Solution)
    """

    __current_id = 0

    @staticmethod
    def update_id(value: int) -> None:

        """
        Нужен в случае, если уже существует n тестов в папке.

        :param value: максимальный идентификатор теста в папке.
        :return:      None
        """

        SolutionFactory.__current_id = value

    @staticmethod
    def make_solution(config: Config) -> Solution:

        SolutionFactory.__current_id += 1

        return Solution(
            SolutionFactory.__current_id,
            config
        )
