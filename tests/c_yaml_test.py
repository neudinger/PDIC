import unittest
import yaml
import pdic

class LevelTest(unittest.TestCase):
    def test_level1(self):
        pdi_yml_description: dict = yaml.load(pdic.files_to_pdi(["examples/level_1.c"]), Loader=yaml.FullLoader)
        with open("examples/expected/level_1.yml") as file:
            pdi_yml_description_expected: dict = yaml.load(file.read(),  Loader=yaml.FullLoader)
            file.close()        
        self.assertEqual(pdi_yml_description, pdi_yml_description_expected)


if __name__ == '__main__':
    unittest.main()
