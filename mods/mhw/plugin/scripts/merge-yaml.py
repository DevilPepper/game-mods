import sys
import yaml

# https://stackoverflow.com/a/9101562
def hexint_presenter(dumper, data):
    return dumper.represent_int(hex(data))

yaml.add_representer(int, hexint_presenter)

merged = {}
for f in sys.argv[1:]:
  with open(f) as file:
    data = yaml.safe_load(file)
    merged.update(data)

print(yaml.dump(merged))
