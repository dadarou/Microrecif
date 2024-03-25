import subprocess
import difflib
import os

def run_test(prog_name, input_file, output_file):
    # Read the expected output from the file
    with open(output_file, 'r') as f:
        expected_output = f.read()

    # Run the program with input_file as input and capture the output
    result = subprocess.run(["./" + prog_name, input_file], text=True, 
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout    

    # Compare the result and the expected output
    if result == expected_output:
        print(f"Test {input_file}: PASSED")
        return True
    else:
        print(f"Test {input_file}: FAILED")
        # print("Program output:")
        # print(result)
        # print("Expected output:")
        # print(expected_output)
        
        # Show the difference between the two outputs
        # print("Difference:")
        # d = difflib.Differ()
        # diff = d.compare(result.splitlines(), expected_output.splitlines())
        # print('\n'.join(diff))
        return False

def run_tests(tests_location, prog_name):
    tests = 0
    passed_tests = 0
    test_files = sorted(os.listdir(tests_location))
    for test_file in test_files:
        if test_file.startswith("t") and test_file.endswith(".txt"):
            tests += 1
            test_number = test_file[1:3]
            input_file = os.path.join(tests_location, test_file)
            output_file = os.path.join(tests_location, f"out{test_number}.txt")
            if run_test(prog_name, input_file, output_file):
                passed_tests += 1

    print(f"\n{passed_tests}/{tests} tests of {tests_location} passed.")

if __name__ == "__main__":
    prog_name = "Code/project"  # Change this to the actual name of your program

    run_tests("Tests/public", prog_name)
    run_tests("Tests/private", prog_name)
