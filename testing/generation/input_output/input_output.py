import matplotlib.pyplot as plt
from numpy import random as rng
from typing import List
from pathlib import Path
import numpy as np
import re
import json

from generation import Solution


class IO:

    def __init__(self, test_dir: str = "tests") -> None:

        """
        Класс, отвечающий за работу с данными (ввод и вывод).

        :param test_dir:    Директория для сохранения/чтения тестов.
        """

        self._save_path = Path(test_dir).absolute()
        self._name = "test"

    def probe(self) -> int:

        """
        Проверка на существование каких-либо тестов в директории. Если хотя бы один существует,
        то возвращается максимальный номер (идентификатор).

        :return: Номер с которого начать нумерацию сгенерированных тестов.
        """

        if not self._save_path.exists():
            return 0

        files = list(self._save_path.glob(f"{self._name}_*.json"))

        if len(files) == 0:
            return 0

        return max(int(re.search(r'\d+', file.stem).group(0)) for file in files)

    def to_json(self, solution: Solution) -> None:

        """
        Запись теста в json-файл.

        :param solution: все данные о тесте.
        :return:         None.
        """

        if not self._save_path.exists():
            self._save_path.mkdir(parents=True, exist_ok=True)

        file_path = self._save_path.joinpath(f"{self._name}_{solution.get_id()}.json")

        data = solution.to_dict()
        data["domain"] = IO.generate_domain(solution)

        with open(file_path, "w") as file:
            json.dump(data, file, ensure_ascii=False, indent=4)

    def from_json(self, test_id: int) -> Solution:

        """
        Чтение теста из json-файла.

        :param test_id: Идентификатор теста.
        :return:        объект Solution.
        """

        file_path = self._save_path.joinpath(f"{self._name}_{test_id}.json")

        if not file_path.exists():
            raise ValueError(f"| {file_path} | does not exist!")

        with open(file_path, "r") as file:
            data = json.load(file)

        new_test = Solution.create_from_json(test_id, data)
        new_test.targets = data["targets"]

        return new_test

    @staticmethod
    def graphic(solution: Solution) -> None:

        """
        Графическое представление теста.

        :param solution: все данные о тесте.
        :return:         None.
        """

        x = []
        y = []

        colorcoder = rng.RandomState(0)
        sample_colors = colorcoder.rand(len(solution))
        colors = []

        for i in range(len(solution)):
            for dot in solution[i]:
                x.append(dot.x_value)
                y.append(dot.y_value)

            colors.extend([sample_colors[i] for _ in range(len(solution[i]))])

        plt.title(f"Test #{solution.get_id()}")
        plt.scatter(x, y, c=colors)
        # pyplot.savefig(os.path.join(directory, f"test_{solution.id}.png"))
        plt.show()

    @staticmethod
    def generate_domain(solution: Solution) -> List[List[int]]:

        domain = np.zeros((solution.x_axis["max_value"], solution.y_axis["max_value"]), dtype=int)

        target_id = 1

        for target in solution.targets:
            for point in target:
                domain[int(point.x_value)][int(point.y_value)] = target_id

            target_id += 1

        return domain.tolist()

    @staticmethod
    def read_test(test_id) -> None:

        path = "./tests/test"
        file = f"{path}_{test_id}.json"

        with open(file, "r") as src:
            data = json.load(src)

        x_target = []
        y_target = []

        for x in range(len(data["domain"])):
            for y in range(len(data["domain"][0])):

                if data["domain"][x][y] > 0:
                    x_target.append(x)
                    y_target.append(y)

        plt.title(f"Test #{test_id} (json)")
        plt.scatter(x_target, y_target)
        plt.show()
