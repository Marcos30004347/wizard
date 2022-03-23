all:
	if [ ! -d "./build" ]; then mkdir build; fi
	cd build && \
	cmake .. -DCMAKE_BUILD_TYPE=$(build_type) -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DBUILD_TESTS=ON
	if [ -f "./compile_commands.json" ]; then rm -rf ./compile_commands.json; fi
	if [ -f "./build/compile_commands.json" ]; then ln ./build/compile_commands.json .; fi
