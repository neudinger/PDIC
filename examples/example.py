import os
import pathlib
import yaml
import pdic

here = pathlib.Path(__file__).parent.resolve()
# pip show -f pdic
if __name__ == "__main__":
    pdi_yml_description: str = pdic.files_to_pdi([os.path.join(here, "level_1.c"),
                                                  os.path.join(here, "level_2.c")])
    print(pdi_yml_description)
    print(yaml.dump(yaml.load(pdi_yml_description)))
