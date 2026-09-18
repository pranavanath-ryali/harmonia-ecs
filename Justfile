build_dir := "build"

default: build

debug:
    cmake -B {{build_dir}} -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    bear -- cmake --build {{build_dir}}
    ln -sf {{build_dir}}/compile_commands.json compile_commands.json

release:
    cmake -B {{build_dir}} -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    bear -- cmake --build {{build_dir}}
    ln -sf {{build_dir}}/compile_commands.json compile_commands.json

# Build the library and all test binaries
build:
    cmake --build {{build_dir}}

# List available test binaries in build/bin/
test-list: build
    @ls -1 {{build_dir}}/bin

# Run a specific test binary (e.g. `just test test_physics`)
test name: build
    ./{{build_dir}}/bin/{{name}}

clean:
    rm -rf {{build_dir}} compile_commands.json
