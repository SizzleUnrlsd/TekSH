import multiprocessing
import subprocess
import difflib
import time
import sys
import os


class Diff:
    IGNORE              = 0
    REQUIREMENT_LVL_0   = 1


class TriStateBoolean:
    def __init__(self, value=None):
        if value is None:
            self.value = None
        else:
            self.value = bool(value)

    def __repr__(self):
        if self.value is None:
            return "None"
        elif self.value:
            return "True"
        else:
            return "False"


class Formatter:
    BOLD     = "\033[1m"
    RED      = "\033[91m"
    GREEN    = "\033[92m"
    GREY     = "\033[90m"
    RESET    = "\033[0m"

    @classmethod
    def bold(cls, text):
        return f"{cls.BOLD}{text}{cls.RESET}"

    @classmethod
    def red(cls, text):
        return f"{cls.RED}{text}{cls.RESET}"

    @classmethod
    def bold_red(cls, text):
        return f"{cls.BOLD}{cls.RED}{text}{cls.RESET}"

    @classmethod
    def bold_green(cls, text):
        return f"{cls.BOLD}{cls.GREEN}{text}{cls.RESET}"

    @classmethod
    def bold_grey(cls, text):
        return f"{cls.BOLD}{cls.GREY}{text}{cls.RESET}"


class TekshFrameworkTest:
    def __init__(self):
        self.formatter = Formatter()
        self.value = 0


    def index_increment(self) -> None:
        self.value += 1


    def get_value_index(self) -> int:
        return self.value


    def run(self, command, *args, input_data=None) -> any:
        cmd_path = os.path.join(command)
        cmd = [cmd_path]
        
        result = subprocess.run(
            cmd, 
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, 
            input=input_data, 
            text=True,
            timeout=10.0
        )
        return result


    def current_command(self, command, queue, *args, input_data: str=None, verbosity: bool=False) -> None:
        try:
            result = self.run(command, *args, input_data=input_data)
        except subprocess.TimeoutExpired:
            print("Time out")
            return

        if verbosity:
            print(f"Command : {' '.join(result.args)}")
            print(f"STDOUT:\n{result.stdout}")
            print(f"STDERR:\n{result.stderr}")
            print(f"Return code: {result.returncode}")
        queue.put(result.stdout + result.stderr)
        return


    def comparison(self, s1:str, s2:str) -> str:
        lines1  : list = s1.splitlines()
        lines2  : list = s2.splitlines()
        result  : list = []
        diff    : list = list(difflib.ndiff(lines1, lines2))

        for line in diff:
            if line.startswith('- ') or line.startswith('+ '):
                result.append(line)

        if len(result) == 0:
            return self.formatter.bold("OK")

        return self.formatter.bold_red("\n".join(result) + '\nKO')


    def requirement_check(self, diff:str, requirement: Diff) -> TriStateBoolean:
        if requirement is not Diff.IGNORE and (diff != self.formatter.bold("OK")):
            return TriStateBoolean(False)
        if requirement is Diff.IGNORE:
            return TriStateBoolean(None)
        return TriStateBoolean(True)


def test_instance(tester: TekshFrameworkTest, command: str, *args, verbosity: bool=False, requirement: Diff=Diff.IGNORE, expected: str=None) -> TriStateBoolean():
    queue = multiprocessing.Queue()
    output          : str = ""
    expected_output : str = ""
    passed          : TriStateBoolean = None

    print("Test", Formatter.bold(tester.get_value_index()), Formatter.bold_green((">", command)))

    process1 = multiprocessing.Process(target=tester.current_command,
                                       args=("../teksh", queue,),
                                       kwargs={
                                                'input_data':command,
                                                'verbosity':verbosity
                                            })

    process2 = multiprocessing.Process(target=tester.current_command,
                                       args=("tcsh", queue,),
                                       kwargs={
                                            'input_data':command,
                                            'verbosity':verbosity
                                        })

    process1.start()
    process2.start()

    process1.join()
    process2.join()

    if queue.qsize() == 2:
        output          = queue.get()
        expected_output = queue.get()
    else:
        print("Error incoming")

    if expected is not None:
        expected_output = expected

    diff = tester.comparison(output, expected_output)
    passed = tester.requirement_check(diff, requirement)

    tester.index_increment()

    print(diff)
    return passed

if __name__ == '__main__':
    tester = TekshFrameworkTest()
    tests_results : list = []

    tests_cases = [
        "ls -a",
        "ls -alt",
        "ls -l",
        "ls -l -a -t",
        "ls -l -a -t  | cat",
        "         ls -l -a -t    |   cat       |       cat         ",
        "dvsvdfbdf",
        "",
        "ls\n",
        "ls\nls",
        "\n",
        "\t",
        "echo",
        "ls | ls && ls -a",
        "ls || ls -a && ls -alt",
        "ls | rev > toto ; cat toto ; rm toto ; ls -alt | | cat | cat | cat > toto ; cat toto ; rm toto",
        "cd azerto",
        " rm toto && ls ",
        " ls -a | cat > toto ; cat toto "
    ]

    ignore_cases = [
        "\nls",
        "rm toto || ls ",
        "cd - ; cd - ; ls",
        "ls;ls -a     ;ls -alt > toto; cat toto; rm toto"
    ]

    test_specific_output = [
        ["alias", "alias ls ls --color=auto"],
    ]

    tests_results.extend([test_instance(tester, command, verbosity=False, requirement=Diff.REQUIREMENT_LVL_0) for command in tests_cases])
    tests_results.extend([test_instance(tester, command, verbosity=False, requirement=Diff.IGNORE) for command in ignore_cases])
    tests_results.extend([test_instance(tester,  command[0], verbosity=False, requirement=Diff.REQUIREMENT_LVL_0, expected=command[1]) for command in test_specific_output])

    true_count = sum(1 for item in tests_results if str(item) == "True")
    false_count = sum(1 for item in tests_results if str(item) == "False")
    ignore_count = sum(1 for item in tests_results if str(item) == "None")

    print(Formatter.bold("\nRESUME: All tests :"))
    print(Formatter.bold_green(f"Successful tests : {true_count}"))
    print(Formatter.bold_grey(f"Ignore tests : {ignore_count}"))
    print(Formatter.bold_red(f"unsuccessful tests : {false_count}"))
