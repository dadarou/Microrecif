import subprocess
import difflib
import os

def run_test(prog_name, input_file, output_file):
    try:
        # Run the program with input_file as input and capture the output
        result = subprocess.check_output(["./" + prog_name], stdin=open(input_file), text=True, stderr=subprocess.STDOUT)
        
        # Read the expected output from the file
        with open(output_file, 'r') as f:
            expected_output = f.read()

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
            print("Difference:")
            d = difflib.Differ()
            diff = d.compare(result.splitlines(), expected_output.splitlines())
            print('\n'.join(diff))
            
            return False
    except subprocess.CalledProcessError as e:
        print(f"Test {input_file}: FAILED (Program exited with code {e.returncode})")
        return False

def run_tests(tests_location, prog_name, start, stop):
    passed_tests = 0
    for i in range(start, stop):
        input_file = os.path.join(tests_location, f"t{i:02d}.txt")
        output_file = os.path.join(tests_location, f"out{i:02d}.txt")
        if run_test(prog_name, input_file, output_file):
            passed_tests += 1
        print()

    print(f"\n{passed_tests}/{stop - start} Tests passed.")

if __name__ == "__main__":
    tests_location = "public"
    prog_name = "../Code/projet"  # Change this to the actual name of your program
    start = 0
    stop = 15    # Change this to the number of tests you have

    run_tests(tests_location, prog_name, start, stop)
