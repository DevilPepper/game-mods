import sys
import yaml

# https://stackoverflow.com/a/9101562
def hexint_presenter(dumper, data):
    return dumper.represent_int(hex(data))

yaml.add_representer(int, hexint_presenter)

merged = {
  "basePointers": {},
  "functions": {}
}
for f in sys.argv[1:]:
  with open(f) as file:
    data = yaml.safe_load(file)
    merged["basePointers"].update(data.get("basePointers", {}))
    merged["functions"].update(data.get("functions", {}))

print(yaml.dump(merged), end = '')
