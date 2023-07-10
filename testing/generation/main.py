from data_structs import Config
from generation import Generator
from input_output import IO

from typing import Optional


def create_tests(number: int = 1, config: Optional[Config] = None) -> None:

    """
    Генерирует заданное количество тестов со стандартным генератором.

    :param number: Кол-во тестов.
    :param config: произвольная конфигурация, если ее нет, то дефолтная создастся автоматически.
    :return:       None.
    """

    data_handler = IO()

    if not config:
        config = Config()

    generator = Generator()
    generator.change_numeration(data_handler.probe())

    for i in range(number):
        solution = generator.generate(config)

        data_handler.graphic(solution)
        data_handler.to_json(solution)


def main():

    create_tests(5)



if __name__ == '__main__':
    main()

