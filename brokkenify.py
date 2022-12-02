import re
import sys
import os

checks = {
    "BAK":  r"(?:for|while)\(",
    "C":    r"#define|malloc|calloc|realloc|typedef|struct|<.+\.h>",
    #       "BABO": r"(?<! )[-+*/^><=]" Does not work, but no priority anyway
    "LTL":  r".{78,}(?=\n)",
    "PP":   r"[a-zA-z_][a-zA-z0-9_]*(?:(?:\+\+)|(?:\-\-))",
    "SLV":  r"(?<= )[a-zA-Z](?=[ =;])",
    "TABS": "\t",

    "BS++": r"\"(?:\S|\\n|\\t|\\|\\'|\\\")\"",  # match single char that is used as string.
}


def print_dashes():
    print("-"*80)


def check_style(code, abbreviation, regex):
    match = re.findall(regex, code)
    if match:
        count = len(set(match))
        print(f"{count} {abbreviation}s detected:")
        print(set(match))
    else:
        count = 0
    return count


def get_dirs_files(dir_name):
    contents = os.scandir(dir_name)

    dirs = []
    files = []

    for content in contents:
        if content.is_dir():
            dirs.append(content.name)
        elif content.is_file():
            files.append(content.name)

    return dirs, files


def parse_file(path):
    print_dashes()
    print(f"Parsing {path}...")
    test_file = open(path)

    code = test_file.read()

    count = 0

    for key in checks:
        count += check_style(code, key, checks[key])

    print(f"{count} 'mistakes' found in {path}")
    return count


def check_exercise_dir(dir_name):
    count = 0
    dirs, files = get_dirs_files(dir_name)

    print_dashes()
    print(f"Checking folder structure of {dir_name}...")

    if "order.txt" not in files:
        print(f"Warning: order.txt does not exist in {dir_name}!")
        count += 1

    if len(dirs) > 0:
        print(f"Warning: nested directories in {dir_name} are not allowed!")
        count += 1

    for file in files:
        if re.match(r".*\.(?:cc|cpp|h|hh|ih)", file):  # check only c++ files
            count += parse_file(os.path.join(dir_name, file))

    return count


def check_set(dir_name):
    count = 0

    dirs, files = get_dirs_files(dir_name)

    print_dashes()
    print(f"Checking folder structure of {dir_name}...")

    if "metadata.txt" not in files:
        print("Warning: metadata.txt does not exist!")
        count += 1

    if len(files) > 1:
        print("Root dir should only have metadata.txt and subfolders!")
        count += 1

    for sub_dir in dirs:
        count += check_exercise_dir(os.path.join(dir_name, sub_dir))

    print_dashes()
    print(f"{count} 'mistakes' found in total.")


def main():
    if len(sys.argv) == 0:
        folder_name = "./bad_example"
    else:
        folder_name = sys.argv[1]

    check_set(folder_name)


if __name__ == "__main__":
    main()
