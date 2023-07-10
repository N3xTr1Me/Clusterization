from data_structs import AxisInterval, Epsilon, Config, Point
from .solution import SolutionFactory, Solution

from random import choice
from typing import List


class Generator:

    def __init__(self) -> None:

        """
        Класс генерации тестов. Определяется сдвигами по осям и количеством точек в цели.
        """

    @staticmethod
    def change_numeration(start_number: int) -> None:

        """
        Изменение начала нумерации сгенерированных тестов. Используется в случае, если в папке уже существуют тесты.

        :param start_number: Новое начало отсчета.
        :return:             None.
        """

        SolutionFactory.update_id(start_number)

    def make_target(self,
                    x_constraint: AxisInterval,
                    y_constraint: AxisInterval,
                    x_epsilon: Epsilon,
                    y_epsilon: Epsilon,
                    number_of_points: List[int]
                    ) -> List[Point]:

        """
        Сборка цели: выбирается случайная точка и итеративно производятся случайные сдвиги по индексам.

        :param x_constraint:        Ограничение значений по X.
        :param y_constraint:        Ограничение значений по Y.
        :param x_epsilon:           Ограничение сдвига по X.
        :param y_epsilon:           Ограничение сдвига по Y.
        :param number_of_points:    Кол-во точек в цели.
        :return:                    Список точек aka цель
        """

        x_index, x_value = x_constraint.random()
        y_index, y_value = y_constraint.random()

        target = [
            Point(
                x_index,
                x_value,
                y_index,
                y_value
            )
        ]

        for i in range(1, choice(number_of_points)):
            x_shift = x_epsilon()
            y_shift = y_epsilon()

            x_index = target[i - 1].x_index + x_shift
            y_index = target[i - 1].y_index + y_shift

            if x_index > len(x_constraint) - 1:
                x_shift = -x_shift
                x_index += 2 * x_shift

            if y_index > len(y_constraint) - 1:
                y_shift = -y_shift
                y_index += 2 * y_shift

            target.append(
                Point(
                    x_index,
                    x_constraint[x_index],
                    y_index,
                    y_constraint[y_index]
                )
            )

        return target

    def generate(self, config: Config) -> Solution:

        """
        Создание теста в заданной конфигурации.

        :param config: Конфигурация
        :return:       объект Solution
        """

        solution = SolutionFactory.make_solution(config)
        x = AxisInterval(*config.x_axis.values())
        y = AxisInterval(*config.y_axis.values())

        x_epsilon = Epsilon(*config.epsilons["x"])
        y_epsilon = Epsilon(*config.epsilons["y"])

        for _ in range(config.n_targets):
            solution.targets.append(
                self.make_target(
                    x, y, x_epsilon, y_epsilon, config.n_points
                )
            )

        return solution
