import subprocess
import pytest
import os
# Get the path to the directory containing this script
script_dir = os.path.dirname(os.path.abspath(__file__))
cpp_executable_path = os.path.join(script_dir, '/mnt/c/Users/parti/Cryptography/main/cryptography')

@pytest.mark.parametrize("input_value, expected_output", [
    ("What the fuck I need more than two inputs q", '25'),
    ("Hello brudder I am here q", '9'),
    ("Hello man q otherwise this doesn't work q", '0'),
    ("Hello man I have worlds q", '100'),
])
def test_basic_merkle_proof(input_value, expected_output):
    # Run the C++ program with the given input and capture the output
    command = f'echo "{input_value}" | {cpp_executable_path}'
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, text=True)


    # Assert that the output is as expected
    assert result.stdout.strip() == expected_output
def test_insersion():
    return False

if __name__ == '__main__':
    pytest.main()