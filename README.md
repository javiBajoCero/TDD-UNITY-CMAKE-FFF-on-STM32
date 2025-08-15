# TDD-UNITY-CMAKE-FFF-on-STM32

A code pool for my learnings about unit testing C code on target for STM32 using VSCode, CMake, Unity, FFF, and GitHub Actions.      
Both production and test builds (.elf) are automated (GithubActions) on every push to `main` and could be found stored as artifacts.

## Folder Structure
- `Core/Src/` — Main application source code
- `tests/Core/` — Unit tests and test runner
- `tests/Core/unity/` — Unity test framework (submodule, patched)
- `tests/Core/fff/` — FFF mocking framework (submodule)

## Unit Testing
- Test files are in `tests/Core/`.
- Tests use CubeMX and HAL libraries.
- To run tests: use the `Unity (ARM) build` task, then flash and debug with `Debug UNITTESt`.

## Production Code
- Main code is in `Core/Src/`.
- To build and run: use the `FW (ARM) build` task, then flash and debug with `Debug Fw`.

## Adding Tests
CubeMX can regenerate code safely; `tests/Core/main.c` must be updated manually for new tests.
1. Add a test file in `tests/Core/` (e.g., `test_<feature>.c`).
2. Write test cases using Unity_fixture.
3. Update `tests/CMakeLists.txt` to include your test file.
4. Modify `tests/Core/main.c` to reference the new test.
5. Build and run tests to verify.

