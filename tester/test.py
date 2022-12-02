import re


def check_x(code, abbreviation, regex):
    match = re.findall(regex, code)
    if match:
        count = len(set(match))
        print(f"{count} {abbreviation}s detected:")
        print(set(match))
    else:
        count = 0
    return count


def main():
    checks = {
        "SLV":  r"(?<= )[a-zA-Z](?=[ =;])",
        "BAK":  r"(?:for|while)\(",
#       "BABO": r"(?<! )[-+*/^><=]" Does not work, but no priority anyway
        "LTL":   r".{75,}(?=\n)",
        "PP":   r"[a-zA-z_][a-zA-z0-9_]*(?:(?:\+\+)|(?:\-\-))",
        "TABS": "\t",


        "BS++": r"\"(?:\S|\\n|\\t|\\|\\'|\\\")\"",  # match single char that is used as string.
    }

    test_file = open("./tester/bad.cc")

    code = test_file.read()

    count = 0

    for key in checks:
        count += check_x(code, key, checks[key])

    print(f"{count} 'mistakes' found in total")


if __name__ == "__main__":
    main()
