import os
import subprocess
import time
import glob
import statistics

# Change to the script's directory to ensure paths are handled correctly
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Number of runs for each test file
NUMBER_OF_RUNS = 3


def run_subprocess(command, cwd=None):
    """Execute a subprocess command via the shell, using the command as a string."""
    env = {
        'OMP_CANCELLATION': 'true'
    }

    start_time = time.time()
    par_or_ser = "par" if "Parallel" in command else "ser"
    test_file_path = command.split()[2]
    test_file_name = os.path.basename(test_file_path)
    test_num = test_file_name.split(".")[0]
    process = subprocess.run(
        command +
        f" 2> build/{test_num}.{par_or_ser}.err > build/{test_num}.{par_or_ser}.std",
        shell=True,
        cwd=cwd,
        env=env,
    )
    end_time = time.time()
    if process.returncode != 0:
        print(f"Running command: {command}")
        print(f"Working directory: {cwd}")
        print(
            f"Command '{command}' failed with return code {process.returncode}")
        print(f"Error output:\n{process.stderr.decode()}")

    return end_time - start_time, process.returncode


def compile_project():
    """Compile the project."""
    build_dir = os.path.join("build")
    os.makedirs(build_dir, exist_ok=True)

    compile_commands = ["cmake -DCMAKE_BUILD_TYPE=Release ..", "make -j"]
    for cmd in compile_commands:
        process = subprocess.run(
            cmd, shell=True, stderr=subprocess.PIPE, cwd=build_dir)
        if process.returncode != 0:
            print(
                f"Compilation failed for Ultimate Tic Tac Toe with error:\n{process.stderr.decode()}")
            return False
    return True


def execute_and_compare(test_files, agent, num_threads):
    """Execute serial and parallel versions of the program, compare their outputs, and take the median of multiple runs."""
    build_dir = "build"
    successful_compilation_and_output = True

    test_files.sort()  # Ensure alphabetical order

    for test_file in test_files:
        base_name = os.path.splitext(os.path.basename(test_file))[0]
        parallel_command = f"{build_dir}/ParallelUltimateTicTacToe -a {os.path.abspath(test_file)} -x {agent} -o {agent} -t {num_threads}"
        serial_command = f"{build_dir}/SerialUltimateTicTacToe -a {os.path.abspath(test_file)} -x {agent} -o {agent} -t {num_threads}"

        parallel_scores = []
        parallel_times = []
        serial_scores = []
        serial_times = []

        for i in range(NUMBER_OF_RUNS):
            print(f"Run {i+1} of {NUMBER_OF_RUNS} for {test_file}")
            _, parallel_return_code = run_subprocess(parallel_command)
            _, serial_return_code = run_subprocess(serial_command)

            if parallel_return_code != 0 or serial_return_code != 0:
                successful_compilation_and_output = False
                break

            # get scores from {test_num}.{ser/par}.std
            with open(f"{build_dir}/{base_name}.ser.std") as f:
                serial_score = float(f.read())

            with open(f"{build_dir}/{base_name}.par.std") as f:
                parallel_score = float(f.read())

            # get times from {test_num}.{ser/par}.err
            with open(f"{build_dir}/{base_name}.ser.err") as f:
                serial_time = float(f.read())

            with open(f"{build_dir}/{base_name}.par.err") as f:
                parallel_time = float(f.read())

            parallel_scores.append(parallel_score)
            serial_scores.append(serial_score)
            parallel_times.append(parallel_time)
            serial_times.append(serial_time)

        if not successful_compilation_and_output:
            continue

        median_parallel_time = statistics.median(parallel_times)
        median_parallel_score = statistics.median(parallel_scores)
        median_serial_time = statistics.median(serial_times)
        median_serial_score = statistics.median(serial_scores)

        speedup = median_serial_time / median_parallel_time if median_parallel_time > 0 else 0
        print(f"Test {base_name}: Median Speedup = {speedup:.2f}x | Median Serial Score = {median_serial_score} | Median Parallel Score = {median_parallel_score}")


def main():
    if compile_project():
        test_files = glob.glob(os.path.join("tests", "*.in"))
        for agent in ["mcts", "minimax"]:
            for num_threads in [2, 4, 8, 16]:
                print(f"Running {agent} agent with {num_threads} threads...")
                execute_and_compare(test_files, agent, num_threads)
            print("-------------------------------------------")
    else:
        print("Skipping due to compilation failure.")


if __name__ == "__main__":
    main()
